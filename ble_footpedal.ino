#include <bluefruit.h>
#include "touchpad.h"

BLEDis bledis;
BLEHidTouchpad touchpad;

bool finger_down = false;
int finger_offset = 0;
float finger_y = 32767 / 2;
int16_t last_scan_time = 0;

int pot_pin = A1;
float pot_min = 524;
float pot_max = 676;
float pot_middle = (pot_min + pot_max) / 2;
float dead_enter = 5;
float dead_exit = 10;

float pot_smoothed = pot_middle;
float max_speed = 20;//2;
float min_speed = .2;//.02;

void setup() 
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  // HID Device can have a min connection interval of 9*1.25 = 11.25 ms
  Bluefruit.Periph.setConnInterval(9, 16); // min = 9*1.25=11.25 ms, max = 16*1.25=20ms
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  Bluefruit.setName("Bluetooth Footpedal");

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();

  // BLE HID
  touchpad.begin();

  // Set up and start advertising
  startAdv();
}

void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
//  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_MOUSE);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(touchpad);

  // There is enough room for 'Name' in the advertising packet
  Bluefruit.Advertising.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(false);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void loop() 
{
  int16_t scan_time = micros() / 100;

  pot_smoothed = 0;
  for (int i = 0; i < 10; i++){
    pot_smoothed += (float) analogRead(pot_pin);
  }
  pot_smoothed = pot_smoothed / 10;
  boolean in_dead_enter = pot_smoothed > (pot_middle - dead_enter) && pot_smoothed < (pot_middle + dead_enter);
  boolean in_dead_exit = pot_smoothed > (pot_middle - dead_exit) && pot_smoothed < (pot_middle + dead_exit);
  
  if ((in_dead_enter && finger_down)) {
    finger_down = false;
    touchpad.send_report(false, 0 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
    touchpad.send_report(false, 1 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
  } else if (!in_dead_exit && !finger_down) {
    finger_down = true;
    touchpad.send_report(true, 0 + finger_offset, 0, (int16_t) finger_y, scan_time, 2);
    touchpad.send_report(true, 1 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
  } else if (finger_down && pot_smoothed < (pot_middle - dead_enter)) {
    // moving up
    float proportion = ((pot_middle - dead_exit) - pot_smoothed) / ((pot_middle - dead_exit) - pot_min);
    proportion = max(0, min(proportion, 1));
    proportion = pow(proportion, 2);
    float new_finger_y = finger_y + proportion * max_speed + min_speed;
    
    if (new_finger_y > 32767) {
      touchpad.send_report(false, 0 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
      touchpad.send_report(false, 1 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
      finger_y = new_finger_y - 32767;
      finger_offset = (finger_offset + 2) % 5;
    } else {
      finger_y = new_finger_y;
    }
    touchpad.send_report(true, 0 + finger_offset, 0, (int16_t) finger_y, scan_time, 2);
    touchpad.send_report(true, 1 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
  } else if (finger_down && pot_smoothed > (pot_middle + dead_enter)) {
    // moving down
    float proportion = (pot_smoothed - (pot_middle + dead_exit)) / (pot_max - (pot_middle + dead_exit));
    proportion = max(0, min(proportion, 1));
    proportion = pow(proportion, 2);
    float new_finger_y = finger_y - (proportion * max_speed + min_speed);

    if (new_finger_y < 0) {
      touchpad.send_report(false, 0 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
      touchpad.send_report(false, 1 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
      finger_y = new_finger_y + 32767;
      finger_offset = (finger_offset + 2) % 5;
    } else {
      finger_y = new_finger_y;
    }
    touchpad.send_report(true, 0 + finger_offset, 0, (int16_t) finger_y, scan_time, 2);
    touchpad.send_report(true, 1 + finger_offset, 0, (int16_t) finger_y, scan_time, 0);
  }
}
