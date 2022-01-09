#include "bluefruit.h"
#include "touchpad.h"
#include <stdint.h>

#define REPORTID_TOUCHPAD 0x01
#define REPORTID_MAX_COUNT 0x02
#define REPORTID_CERTIFICATION 0x03
#define REPORTID_INPUT_MODE 0x04
#define REPORTI_ID_SELECTIVE_REPORTING 0x05
#define REPORTID_MOUSE 0x06

// descriptor from https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/windows-precision-touchpad-sample-report-descriptors
uint8_t const hid_report_descriptor[] =
{
    // ---------- Touchpad ----------
    0x05, 0x0d,                         // USAGE_PAGE (Digitizers)          
    0x09, 0x05,                         // USAGE (Touch Pad)             
    0xa1, 0x01,                         // COLLECTION (Application)         
    0x85, REPORTID_TOUCHPAD,            //   REPORT_ID (Touch pad)              
    0x09, 0x22,                         //   USAGE (Finger)                 
    0xa1, 0x02,                         //   COLLECTION (Logical)
    // input: confidence and tip switch (2 x 1 bits)
    0x15, 0x00,                         //       LOGICAL_MINIMUM (0)
    0x25, 0x01,                         //       LOGICAL_MAXIMUM (1)
    0x09, 0x47,                         //       USAGE (Confidence) 
    0x09, 0x42,                         //       USAGE (Tip switch)
    0x95, 0x02,                         //       REPORT_COUNT (2)
    0x75, 0x01,                         //       REPORT_SIZE (1)
    // input: contact id (1 x 2 bits)
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
    0x95, 0x01,                         //       REPORT_COUNT (1)
    0x75, 0x02,                         //       REPORT_SIZE (2)
    0x25, 0x02,                         //       LOGICAL_MAXIMUM (2)
    0x09, 0x51,                         //       USAGE (Contact Identifier)
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
    // constants to pad (4 bits)
    0x75, 0x01,                         //       REPORT_SIZE (1)
    0x95, 0x04,                         //       REPORT_COUNT (4)             
    0x81, 0x03,                         //       INPUT (Cnst,Var,Abs)
    // input: x (1 x 2 bytes)
    0x05, 0x01,                         //       USAGE_PAGE (Generic Desk..
    0x15, 0x00,                         //       LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x0f,                   //       LOGICAL_MAXIMUM (4095)         
    0x75, 0x10,                         //       REPORT_SIZE (16)             
    0x55, 0x0e,                         //       UNIT_EXPONENT (-2)           
    0x65, 0x13,                         //       UNIT(Inch,EngLinear)                  
    0x09, 0x30,                         //       USAGE (X)                    
    0x35, 0x00,                         //       PHYSICAL_MINIMUM (0)         
    0x46, 0x90, 0x01,                   //       PHYSICAL_MAXIMUM (400)
    0x95, 0x01,                         //       REPORT_COUNT (1)         
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
    // input: y (1 x 2 bytes)
    0x46, 0x13, 0x01,                   //       PHYSICAL_MAXIMUM (275)
    0x09, 0x31,                         //       USAGE (Y)                    
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)

    0xc0,                               //    END_COLLECTION
    // input: scan time (1 x 2 bytes)
    0x55, 0x0C,                         //    UNIT_EXPONENT (-4)           
    0x66, 0x01, 0x10,                   //    UNIT (Seconds)        
    0x47, 0xff, 0xff, 0x00, 0x00,      //     PHYSICAL_MAXIMUM (65535)
    0x27, 0xff, 0xff, 0x00, 0x00,         //  LOGICAL_MAXIMUM (65535) 
    0x75, 0x10,                           //  REPORT_SIZE (16)             
    0x95, 0x01,                           //  REPORT_COUNT (1) 
    0x05, 0x0d,                         //    USAGE_PAGE (Digitizers)
    0x09, 0x56,                         //    USAGE (Scan Time)    
    0x81, 0x02,                           //  INPUT (Data,Var,Abs)
    // input: contact count (1 x 1 byte)
    0x09, 0x54,                         //    USAGE (Contact count)
    0x25, 0x7f,                           //  LOGICAL_MAXIMUM (127) 
    0x95, 0x01,                         //    REPORT_COUNT (1)
    0x75, 0x08,                         //    REPORT_SIZE (8)    
    0x81, 0x02,                         //    INPUT (Data,Var,Abs)
    // input: button (1 x 1 bit)
    0x05, 0x09,                         //    USAGE_PAGE (Button)         
    0x09, 0x01,                         //    USAGE_(Button 1)     
    0x25, 0x01,                         //    LOGICAL_MAXIMUM (1)          
    0x75, 0x01,                         //    REPORT_SIZE (1)              
    0x95, 0x01,                         //    REPORT_COUNT (1)             
    0x81, 0x02,                         //    INPUT (Data,Var,Abs)
    // input: constants to pad (7 bits)
    0x95, 0x07,                          //   REPORT_COUNT (7)                 
    0x81, 0x03,                         //    INPUT (Cnst,Var,Abs)
    // feature: contact count max / pad type (2 x 4 bits)
    0x05, 0x0d,                         //    USAGE_PAGE (Digitizer)
    0x85, REPORTID_MAX_COUNT,            //   REPORT_ID (Feature)              
    0x09, 0x55,                         //    USAGE (Contact Count Maximum)
    0x09, 0x59,                         //    USAGE (Pad TYpe)
    0x75, 0x04,                         //    REPORT_SIZE (4) 
    0x95, 0x02,                         //    REPORT_COUNT (2)
    0x25, 0x0f,                         //    LOGICAL_MAXIMUM (15)
    0xb1, 0x02,                         //    FEATURE (Data,Var,Abs)

    // feature: certification status (256 byte constant above)
    0x06, 0x00, 0xff,                   //    USAGE_PAGE (Vendor Defined)
    0x85, REPORTID_CERTIFICATION,       //    REPORT_ID (PTPHQA)  
    0x09, 0xC5,                         //    USAGE (Vendor Usage 0xC5)    
    0x15, 0x00,                         //    LOGICAL_MINIMUM (0)          
    0x26, 0xff, 0x00,                   //    LOGICAL_MAXIMUM (0xff) 
    0x75, 0x08,                         //    REPORT_SIZE (8)             
    0x96, 0x00, 0x01,                   //    REPORT_COUNT (0x100 (256))             
    0xb1, 0x02,                         //    FEATURE (Data,Var,Abs)
    0xc0,                               // END_COLLECTION
    
    // ---------- CONFIG TLC ----------
    0x05, 0x0d,                         // USAGE_PAGE (Digitizer)
    0x09, 0x0E,                         // USAGE (Configuration)
    0xa1, 0x01,                         // COLLECTION (Application)
    0x85, REPORTID_INPUT_MODE,          //   REPORT_ID (Feature)              
    0x09, 0x22,                         //   USAGE (Finger)              
    0xa1, 0x02,                         //   COLLECTION (logical)
    // feature: input mode (1 x 1 byte)
    0x09, 0x52,                         //    USAGE (Input Mode)         
    0x15, 0x00,                         //    LOGICAL_MINIMUM (0)      
    0x25, 0x0a,                         //    LOGICAL_MAXIMUM (10)
    0x75, 0x08,                         //    REPORT_SIZE (8)         
    0x95, 0x01,                         //    REPORT_COUNT (1)         
    0xb1, 0x02,                         //    FEATURE (Data,Var,Abs  

    0xc0,                               //   END_COLLECTION
    0x09, 0x22,                         //   USAGE (Finger)              
    0xa1, 0x00,                         //   COLLECTION (physical)    
    0x85, REPORTI_ID_SELECTIVE_REPORTING,     //     REPORT_ID (Feature)
    // feature: surface switch and button switch (2 x 1 bit)
    0x09, 0x57,                         //     USAGE(Surface switch)
    0x09, 0x58,                         //     USAGE(Button switch)
    0x75, 0x01,                         //     REPORT_SIZE (1)
    0x95, 0x02,                         //     REPORT_COUNT (2)
    0x25, 0x01,                         //     LOGICAL_MAXIMUM (1)
    0xb1, 0x02,                         //     FEATURE (Data,Var,Abs)
    // feature: constants to pad (6 bits)
    0x95, 0x06,                         //     REPORT_COUNT (6)             
    0xb1, 0x03,                         //     FEATURE (Cnst,Var,Abs)
    0xc0,                               //   END_COLLECTION
    0xc0,                               // END_COLLECTION

    // ---------- Mouse ----------
    0x05, 0x01,                         // USAGE_PAGE (Generic Desktop)     
    0x09, 0x02,                         // USAGE (Mouse)                    
    0xa1, 0x01,                         // COLLECTION (Application)        
    0x85, REPORTID_MOUSE,               //   REPORT_ID (Mouse)              
    0x09, 0x01,                         //   USAGE (Pointer)                
    0xa1, 0x00,                         //   COLLECTION (Physical)
    // input: button (2 x 1 bits)
    0x05, 0x09,                         //     USAGE_PAGE (Button)          
    0x19, 0x01,                         //     USAGE_MINIMUM (Button 1)     
    0x29, 0x02,                         //     USAGE_MAXIMUM (Button 2)     
    0x25, 0x01,                         //     LOGICAL_MAXIMUM (1)          
    0x75, 0x01,                         //     REPORT_SIZE (1)              
    0x95, 0x02,                         //     REPORT_COUNT (2)             
    0x81, 0x02,                         //     INPUT (Data,Var,Abs)
    // input: constants to pad (6 bits)
    0x95, 0x06,                         //     REPORT_COUNT (6)             
    0x81, 0x03,                         //     INPUT (Cnst,Var,Abs)
    // input: x and y (2 x 2 bytes)
    0x05, 0x01,                         //     USAGE_PAGE (Generic Desktop) 
    0x09, 0x30,                         //     USAGE (X)                    
    0x09, 0x31,                         //     USAGE (Y)                    
    0x75, 0x10,                         //     REPORT_SIZE (16)             
    0x95, 0x02,                         //     REPORT_COUNT (2)             
    0x25, 0x0a,                         //     LOGICAL_MAXIMUM (10)      
    0x81, 0x06,                         //     INPUT (Data,Var,Rel)

    0xc0,                               //   END_COLLECTION                 
    0xc0,                               // END_COLLECTION
};

typedef struct {
    // one report is sent with each finger which is identified by its contact id
    uint8_t contact_data; // bitmap: Confidence | Tip Switch | Contact ID (2 bits) | empty (4 bits)
        // confidence = 1 if contact is too large for a finger (should probably always be 0 for me)
        // tip switch = 1 if the contact is on the surface of the touchpad
            // when a finger is put on the touchpad the tip switch is turned on (1)
            // after the finger is lifted, the tip switch is reported as off (0) for one frame
            // then, no more reports are sent for that fingers contact
        // contact id identifies which finger we are sending the data for 
            // e.g., for two fingers we would have contact id 0 for the first report and contact id 1 for the second report
    int16_t x; // x position of finger (between 0 and 4095)
    int16_t y; // y position of finger (between 0 and 4095)
    int16_t scan_time; // in 100 microsecond units
        // seems like this should be reported at consistent intervals while at least one finger is on the touchpad
        // when more than one finger is in contact, each one of the finger's reports should have the same scan time
    int8_t contact_count; // number of fingers on the touchpad (between 0 and 3)
    uint8_t button; // whether the touchpad is pressed hard enough to click (0 or 1)
} touchpad_report_t;

typedef struct {
    uint8_t button; // bitmap: Button 1 | Button 2 | empty (6 bits)
    int16_t x; // between 0 and 10
    int16_t y; // between 0 and 10
} mouse_report_t;

// report sizes for feature reports
#define MAX_COUNT_REPORT_SIZE 1
#define CERTIFICATION_REPORT_SIZE 256
#define INPUT_MODE_REPORT_SIZE 1
#define SELECTIVE_REPORTING_REPORT_SIZE 1

// report types
#define REPORT_TYPE_INPUT 1
#define REPORT_TYPE_OUTPUT 2
#define REPORT_TYPE_FEATURE 3


BLEHidTouchpad::BLEHidTouchpad()
    : BLEHidGeneric(0, 0, 0)
{ 
    mode = 0; // 0: mouse, 1: touchpad

    // BLE characteristics for each report id
    chr_touchpad = new BLECharacteristic();
    chr_max_count = new BLECharacteristic();
    chr_certification = new BLECharacteristic();;
    chr_input_mode = new BLECharacteristic();;
    chr_selective_reporting = new BLECharacteristic();;
    chr_mouse = new BLECharacteristic();;
}

err_t BLEHidTouchpad::begin()
{
    uint16_t input_len [] = { sizeof(touchpad_report_t) };
    setReportLen(input_len, NULL, NULL);
    enableKeyboard(false);
    enableMouse(false);
    setReportMap(hid_report_descriptor, sizeof(hid_report_descriptor));

    VERIFY_STATUS( BLEHidGeneric::begin() );

    // mouse and touchpad input report charcteristics
    chr_touchpad->setUuid(UUID16_CHR_REPORT);
    chr_touchpad->setProperties(CHR_PROPS_READ | CHR_PROPS_NOTIFY);
    chr_touchpad->setPermission(SECMODE_ENC_NO_MITM, SECMODE_NO_ACCESS);
    chr_touchpad->setReportRefDescriptor(REPORTID_TOUCHPAD, REPORT_TYPE_INPUT);
    chr_touchpad->setFixedLen(sizeof(touchpad_report_t));
    VERIFY_STATUS( chr_touchpad->begin() );

    chr_mouse->setUuid(UUID16_CHR_REPORT);
    chr_mouse->setProperties(CHR_PROPS_READ | CHR_PROPS_NOTIFY);
    chr_mouse->setPermission(SECMODE_ENC_NO_MITM, SECMODE_NO_ACCESS);
    chr_mouse->setReportRefDescriptor(REPORTID_MOUSE, REPORT_TYPE_INPUT);
    chr_mouse->setFixedLen(sizeof(mouse_report_t));
    VERIFY_STATUS( chr_mouse->begin() );


    // feature reports
    chr_max_count->setUuid(UUID16_CHR_REPORT);
    chr_max_count->setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
    chr_max_count->setPermission(SECMODE_ENC_NO_MITM, SECMODE_ENC_NO_MITM);
    chr_max_count->setReportRefDescriptor(REPORTID_MAX_COUNT, REPORT_TYPE_FEATURE);
    chr_max_count->setFixedLen(MAX_COUNT_REPORT_SIZE);
    chr_max_count->setReadAuthorizeCallback(max_count_callback);
    VERIFY_STATUS( chr_max_count->begin() );

    chr_certification->setUuid(UUID16_CHR_REPORT);
    chr_certification->setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
    chr_certification->setPermission(SECMODE_ENC_NO_MITM, SECMODE_ENC_NO_MITM);
    chr_certification->setReportRefDescriptor(REPORTID_CERTIFICATION, REPORT_TYPE_FEATURE);
    chr_certification->setFixedLen(CERTIFICATION_REPORT_SIZE);
    chr_certification->setReadAuthorizeCallback(certification_callback);
    VERIFY_STATUS( chr_certification->begin() );

    chr_input_mode->setUuid(UUID16_CHR_REPORT);
    chr_input_mode->setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
    chr_input_mode->setPermission(SECMODE_ENC_NO_MITM, SECMODE_ENC_NO_MITM);
    chr_input_mode->setReportRefDescriptor(REPORTID_INPUT_MODE, REPORT_TYPE_FEATURE);
    chr_input_mode->setFixedLen(INPUT_MODE_REPORT_SIZE);
    chr_input_mode->setWriteAuthorizeCallback(input_mode_callback);
    VERIFY_STATUS( chr_input_mode->begin() );

    chr_selective_reporting->setUuid(UUID16_CHR_REPORT);
    chr_selective_reporting->setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
    chr_selective_reporting->setPermission(SECMODE_ENC_NO_MITM, SECMODE_ENC_NO_MITM);
    chr_selective_reporting->setReportRefDescriptor(REPORTI_ID_SELECTIVE_REPORTING, REPORT_TYPE_FEATURE);
    chr_selective_reporting->setFixedLen(SELECTIVE_REPORTING_REPORT_SIZE);
    chr_selective_reporting->setWriteAuthorizeCallback(selective_reporting_callback);
    VERIFY_STATUS( chr_selective_reporting->begin() );

    Serial.print("1: ");
    Serial.println(chr_touchpad->handles().value_handle);
    Serial.print("2: ");
    Serial.println(chr_mouse->handles().value_handle);
    Serial.print("3: ");
    Serial.println(chr_max_count->handles().value_handle);
    Serial.print("4: ");
    Serial.println(chr_certification->handles().value_handle);
    Serial.print("5: ");
    Serial.println(chr_input_mode->handles().value_handle);
    Serial.print("6: ");
    Serial.println(chr_selective_reporting->handles().value_handle);

    // Attempt to change the connection interval to 11.25-15 ms when starting HID
    Bluefruit.Periph.setConnInterval(9, 12);

    return ERROR_NONE;
}

void BLEHidTouchpad::max_count_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_read_t* request)
{
    Serial.println("max count callback");
}

void BLEHidTouchpad::certification_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_read_t* request)
{
    Serial.println("certification callback");
}

void BLEHidTouchpad::input_mode_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_write_t* request)
{
    Serial.print("input mode callback ");
}

void BLEHidTouchpad::selective_reporting_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_write_t* request)
{
    Serial.print("function switch callback ");
}


bool BLEHidTouchpad::send_report(bool tip_switch, uint8_t contact_id, int16_t x, int16_t y, int16_t scan_time, int8_t contact_count, bool button, bool confidence)
{
    // For each frame, one report should be sent for each finger on the pad
        // contact_id should be between 0 and 3 representing which finger is being reported
        // contact count should be reported for only the first finger and indicates how many fingers are on the pad. Subsequent figners reports should have it set to 0
        // when a finger is put on the pad, the tip switch is set to true
        // when a finger has been taken off, the tip switch is set to false for one frame with the same (x, y) coords as the last frame
            // after this frame, the finger does not need to keep being reported
            // contact count shouldn't change until the frame after the tip switch is switched to false
        // confidence is set to true when the contact is larger than a finger (indicating that it could be an unintentional contact)
        // scan time should be reported as the same for all fingers in the frame and is in 100 microsecond units (i.e., (int16_t) (micros() / 100))
    // x and y should be between -128 and 127
    Serial.print(millis());
    Serial.print(" ");
    touchpad_report_t report;
    report.contact_data = confidence + (tip_switch << 1) + (contact_id << 2);
    report.x = x;
    report.y = y;
    report.scan_time = scan_time;
    report.contact_count = contact_count;
    report.button = button;

    Serial.print(report.contact_data);
    Serial.print(" ");
    Serial.print(millis());
    Serial.print(" ");

    return inputReport(BLE_CONN_HANDLE_INVALID, REPORTID_TOUCHPAD, &report, sizeof(touchpad_report_t));
}
