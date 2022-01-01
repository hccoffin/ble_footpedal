#include "bluefruit.h"
#include "touchpad.h"
#include <stdint.h>

#define TOUCHPAD_REPORT_ID 0x01

uint8_t const hid_report_descriptor[] =
{
    // 0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 54
    // 0x09, 0x02,                    // USAGE (Mouse)
    // 0xa1, 0x01,                    // COLLECTION (Application)
    // 0x09, 0x01,                    //   USAGE (Pointer)
    // 0xa1, 0x00,                    //   COLLECTION (Physical)
    // 0x85, MOUSE_REPORT_ID,         //     REPORT_ID (1)
    // 0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    // 0x09, 0x30,                    //     USAGE (X)
    // 0x09, 0x31,                    //     USAGE (Y)
    // 0x09, 0x38,                    //     USAGE (Wheel)
    // 0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    // 0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    // 0x75, 0x08,                    //     REPORT_SIZE (8)
    // 0x95, 0x03,                    //     REPORT_COUNT (3)
    // 0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    // 0xc0,                          //   END_COLLECTION
    // 0xc0,                          // END_COLLECTION
    0x05, 0x0d,                         // USAGE_PAGE (Digitizers)          
    0x09, 0x05,                         // USAGE (Touch Pad)             
    0xa1, 0x01,                         // COLLECTION (Application)         
    0x85, TOUCHPAD_REPORT_ID,           //   REPORT_ID (Touch pad)              
    0x09, 0x22,                         //   USAGE (Finger)                 
    0xa1, 0x02,                         //   COLLECTION (Logical)  
    0x15, 0x00,                         //       LOGICAL_MINIMUM (0)
    0x25, 0x01,                         //       LOGICAL_MAXIMUM (1)
    0x09, 0x47,                         //       USAGE (Confidence) 
    0x09, 0x42,                         //       USAGE (Tip switch)
    0x95, 0x02,                         //       REPORT_COUNT (2)
    0x75, 0x01,                         //       REPORT_SIZE (1)
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
    0x95, 0x01,                         //       REPORT_COUNT (1)
    0x75, 0x02,                         //       REPORT_SIZE (2)
    0x25, 0x02,                         //       LOGICAL_MAXIMUM (2)
    0x09, 0x51,                         //       USAGE (Contact Identifier)
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
    0x75, 0x01,                         //       REPORT_SIZE (1)
    0x95, 0x04,                         //       REPORT_COUNT (4)             
    0x81, 0x03,                         //       INPUT (Cnst,Var,Abs)
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
    0x46, 0x13, 0x01,                   //       PHYSICAL_MAXIMUM (275)
    0x09, 0x31,                         //       USAGE (Y)                    
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)    
    0xc0,                               //    END_COLLECTION
    0x55, 0x0C,                         //    UNIT_EXPONENT (-4)           
    0x66, 0x01, 0x10,                   //    UNIT (Seconds)        
    0x47, 0xff, 0xff, 0x00, 0x00,      //     PHYSICAL_MAXIMUM (65535)
    0x27, 0xff, 0xff, 0x00, 0x00,         //  LOGICAL_MAXIMUM (65535) 
    0x75, 0x10,                           //  REPORT_SIZE (16)             
    0x95, 0x01,                           //  REPORT_COUNT (1) 
    0x05, 0x0d,                         //    USAGE_PAGE (Digitizers)
    0x09, 0x56,                         //    USAGE (Scan Time)    
    0x81, 0x02,                           //  INPUT (Data,Var,Abs)         
    0x09, 0x54,                         //    USAGE (Contact count)
    0x25, 0x7f,                           //  LOGICAL_MAXIMUM (127) 
    0x95, 0x01,                         //    REPORT_COUNT (1)
    0x75, 0x08,                         //    REPORT_SIZE (8)    
    0x81, 0x02,                         //    INPUT (Data,Var,Abs)
    0x05, 0x09,                         //    USAGE_PAGE (Button)         
    0x09, 0x01,                         //    USAGE_(Button 1)     
    0x25, 0x01,                         //    LOGICAL_MAXIMUM (1)          
    0x75, 0x01,                         //    REPORT_SIZE (1)              
    0x95, 0x01,                         //    REPORT_COUNT (1)             
    0x81, 0x02,                         //    INPUT (Data,Var,Abs)
    0x95, 0x07,                          //   REPORT_COUNT (7)                 
    0x81, 0x03,                         //    INPUT (Cnst,Var,Abs)
    0xc0,                               // END_COLLECTION
};

// typedef struct {
//     int8_t x;
//     int8_t y;
//     int8_t wheel; 
// } mouse_report_t;

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

BLEHidTouchpad::BLEHidTouchpad()
    : BLEHidGeneric(1, 0, 0)
{ }

err_t BLEHidTouchpad::begin()
{
    uint16_t input_len [] = { sizeof(touchpad_report_t) };
    setReportLen(input_len, NULL, NULL);
    enableKeyboard(false);
    enableMouse(false);
    setReportMap(hid_report_descriptor, sizeof(hid_report_descriptor));

    VERIFY_STATUS( BLEHidGeneric::begin() );

    // Attempt to change the connection interval to 11.25-15 ms when starting HID
    Bluefruit.Periph.setConnInterval(9, 12);

    return ERROR_NONE;
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
    // x and y should be between 0 and 4095
    touchpad_report_t report;
    report.contact_data = confidence + (tip_switch << 1) + (contact_id << 2);
    report.x = x;
    report.y = y;
    report.scan_time = scan_time;
    report.contact_count = contact_count;
    report.button = button;
    return inputReport(BLE_CONN_HANDLE_INVALID, TOUCHPAD_REPORT_ID, &report, sizeof(touchpad_report_t));
}