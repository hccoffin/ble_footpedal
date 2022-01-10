#include <bluefruit.h>
#include "touchpad.h"

BLEDis bledis;
BLEHidTouchpad touchpad;

bool finger_down = false;
int16_t finger_x1 = 2000;
int16_t finger_y1 = 2000;
int16_t last_scan_time = 0;

void setup() 
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("Bluefruit52 HID Mouse Example");
  Serial.println("-----------------------------\n");
  Serial.println("Go to your phone's Bluetooth settings to pair your device");
  Serial.println("then open an application that accepts mouse input");
  Serial.println();

  Serial.println("Enter following characters");
  Serial.println("- 'WASD'  to move mouse (up, left, down, right)");
  Serial.println("- 'LRMBF' to press mouse button(s) (left, right, middle, backward, forward)");
  Serial.println("- 'X'     to release mouse button(s)");

  Bluefruit.begin();
  // HID Device can have a min connection interval of 9*1.25 = 11.25 ms
  Bluefruit.Periph.setConnInterval(9, 16); // min = 9*1.25=11.25 ms, max = 16*1.25=20ms
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values

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
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void loop() 
{
  int16_t scan_time = micros() / 100;
  if (Serial.available())
  {
    char ch = (char) Serial.read();

    // convert to upper case
    ch = (char) toupper(ch);
    
    // echo
    Serial.println(ch);
  
    switch(ch)
    {
      case '[':
        finger_down = true;
        last_scan_time = scan_time;
        Serial.println("Finger down");
      break;

      case ']':
        touchpad.send_report(false, 0, finger_x1, finger_y1, scan_time, 1);
        finger_down = false;
        finger_x1 = 0;
        finger_y1 = 0;
        Serial.println("Finger up");
      break;

      // WASD to move the mouse
      case 'W':
        finger_y1 = finger_y1 + 10;
      break;

      case 'A':
        finger_x1 = finger_x1 - 10;
      break;

      case 'S':
        finger_y1  = finger_y1 - 10;
      break;

      case 'D':
        finger_x1 = finger_x1 + 10;
      break;

      case 'M':
        touchpad.sendMouseReport(0, finger_x1, finger_y1);
      break;

      default: break;
    }
  }
    
  if (finger_down) {
    bool info = touchpad.send_report(true, 0, finger_x1, finger_y1, scan_time - last_scan_time, 1);
//    bool info = touchpad.send_report(true, 0, finger_x1, finger_y1, scan_time, 1);
    Serial.println(info);
    last_scan_time = scan_time;
  }
  delay(100);
}
