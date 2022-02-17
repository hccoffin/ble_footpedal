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

    // --- Finger Collection 1 ---          
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
    0x26, 0xff, 0x7f,                   //       LOGICAL_MAXIMUM (32767)         
    0x75, 0x10,                         //       REPORT_SIZE (16)             
    0x55, 0x0e,                         //       UNIT_EXPONENT (-2)           
    0x65, 0x13,                         //       UNIT(Inch,EngLinear)                  
    0x09, 0x30,                         //       USAGE (X)                    
    0x35, 0x00,                         //       PHYSICAL_MINIMUM (0)         
    0x46, 0x80, 0x0C,                   //       PHYSICAL_MAXIMUM (3200)
    0x95, 0x01,                         //       REPORT_COUNT (1)         
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
    // input: y (1 x 2 bytes)
    0x46, 0x98, 0x08,                   //       PHYSICAL_MAXIMUM (2200)
    0x09, 0x31,                         //       USAGE (Y)                    
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
    0xc0,                               //    END_COLLECTION

    // --- Finger Collection 2 ---
    0x05, 0x0d,                         //   USAGE_PAGE (Digitizers)
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
    0x26, 0xff, 0x7f,                   //       LOGICAL_MAXIMUM (32767)         
    0x75, 0x10,                         //       REPORT_SIZE (16)             
    0x55, 0x0e,                         //       UNIT_EXPONENT (-2)           
    0x65, 0x13,                         //       UNIT(Inch,EngLinear)                  
    0x09, 0x30,                         //       USAGE (X)                    
    0x35, 0x00,                         //       PHYSICAL_MINIMUM (0)         
    0x46, 0x80, 0x0C,                   //       PHYSICAL_MAXIMUM (3200)
    0x95, 0x01,                         //       REPORT_COUNT (1)         
    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
    // input: y (1 x 2 bytes)
    0x46, 0x98, 0x08,                   //       PHYSICAL_MAXIMUM (2200)
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
    
    // ---------- Config ----------
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
    0x05, 0x01,                         //     USAGE_PAGE (Generic Desktop) 
    0x09, 0x30,                         //     USAGE (X)                    
    0x09, 0x31,                         //     USAGE (Y)                    
    0x75, 0x10,                         //     REPORT_SIZE (16)             
    0x95, 0x02,                         //     REPORT_COUNT (2)             
    0x25, 0x0a,                          //    LOGICAL_MAXIMUM (10)      
    0x81, 0x06,                         //     INPUT (Data,Var,Rel)

    0xc0,                               //   END_COLLECTION                 
    0xc0,                               // END_COLLECTION
};

// 256 byte default certification from https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/windows-precision-touchpad-required-hid-top-level-collections
uint8_t const certification[] =
{
    0xfc, 0x28, 0xfe, 0x84, 0x40, 0xcb, 0x9a, 0x87, 0x0d, 0xbe, 0x57, 0x3c, 0xb6, 0x70, 0x09, 0x88, 
    0x07, 0x97, 0x2d, 0x2b, 0xe3, 0x38, 0x34, 0xb6, 0x6c, 0xed, 0xb0, 0xf7, 0xe5, 0x9c, 0xf6, 0xc2, 
    0x2e, 0x84, 0x1b, 0xe8, 0xb4, 0x51, 0x78, 0x43, 0x1f, 0x28, 0x4b, 0x7c, 0x2d, 0x53, 0xaf, 0xfc, 
    0x47, 0x70, 0x1b, 0x59, 0x6f, 0x74, 0x43, 0xc4, 0xf3, 0x47, 0x18, 0x53, 0x1a, 0xa2, 0xa1, 0x71, 
    0xc7, 0x95, 0x0e, 0x31, 0x55, 0x21, 0xd3, 0xb5, 0x1e, 0xe9, 0x0c, 0xba, 0xec, 0xb8, 0x89, 0x19, 
    0x3e, 0xb3, 0xaf, 0x75, 0x81, 0x9d, 0x53, 0xb9, 0x41, 0x57, 0xf4, 0x6d, 0x39, 0x25, 0x29, 0x7c, 
    0x87, 0xd9, 0xb4, 0x98, 0x45, 0x7d, 0xa7, 0x26, 0x9c, 0x65, 0x3b, 0x85, 0x68, 0x89, 0xd7, 0x3b, 
    0xbd, 0xff, 0x14, 0x67, 0xf2, 0x2b, 0xf0, 0x2a, 0x41, 0x54, 0xf0, 0xfd, 0x2c, 0x66, 0x7c, 0xf8, 
    0xc0, 0x8f, 0x33, 0x13, 0x03, 0xf1, 0xd3, 0xc1, 0x0b, 0x89, 0xd9, 0x1b, 0x62, 0xcd, 0x51, 0xb7, 
    0x80, 0xb8, 0xaf, 0x3a, 0x10, 0xc1, 0x8a, 0x5b, 0xe8, 0x8a, 0x56, 0xf0, 0x8c, 0xaa, 0xfa, 0x35, 
    0xe9, 0x42, 0xc4, 0xd8, 0x55, 0xc3, 0x38, 0xcc, 0x2b, 0x53, 0x5c, 0x69, 0x52, 0xd5, 0xc8, 0x73, 
    0x02, 0x38, 0x7c, 0x73, 0xb6, 0x41, 0xe7, 0xff, 0x05, 0xd8, 0x2b, 0x79, 0x9a, 0xe2, 0x34, 0x60, 
    0x8f, 0xa3, 0x32, 0x1f, 0x09, 0x78, 0x62, 0xbc, 0x80, 0xe3, 0x0f, 0xbd, 0x65, 0x20, 0x08, 0x13, 
    0xc1, 0xe2, 0xee, 0x53, 0x2d, 0x86, 0x7e, 0xa7, 0x5a, 0xc5, 0xd3, 0x7d, 0x98, 0xbe, 0x31, 0x48, 
    0x1f, 0xfb, 0xda, 0xaf, 0xa2, 0xa8, 0x6a, 0x89, 0xd6, 0xbf, 0xf2, 0xd3, 0x32, 0x2a, 0x9a, 0xe4, 
    0xcf, 0x17, 0xb7, 0xb8, 0xf4, 0xe1, 0x33, 0x08, 0x24, 0x8b, 0xc4, 0x43, 0xa5, 0xe5, 0x24, 0xc2
};

uint8_t const max_count = 0x04;

typedef struct {
    // one report is sent with each finger which is identified by its contact id
    uint8_t contact_data1; // information about the finger contact for finger 1
        // bitmap: Confidence | Tip Switch | Contact ID (2 bits) | empty (4 bits)
        // confidence = 1 if contact is too large for a finger (should probably always be 0 for me)
        // tip switch = 1 if the contact is on the surface of the touchpad
            // when a finger is put on the touchpad the tip switch is turned on (1)
            // after the finger is lifted, the tip switch is reported as off (0) for one frame
            // then, no more reports are sent for that fingers contact
        // contact id identifies which finger we are sending the data for 
            // e.g., for two fingers we would have contact id 0 for the first report and contact id 1 for the second report
    int16_t x1; // x position of finger 1 (between 0 and 4095)
    int16_t y1; // y position of finger 1 (between 0 and 4095)
    uint8_t contact_data2;
    int16_t x2;
    int16_t y2;
    int16_t scan_time; // in 100 microsecond units
        // seems like this should be reported at consistent intervals while at least one finger is on the touchpad
        // when more than one finger is in contact, each one of the finger's reports should have the same scan time
    int8_t contact_count; // number of fingers on the touchpad (between 0 and 3)
    uint8_t button; // whether the touchpad is pressed hard enough to click (0 or 1)
} __attribute__((packed, aligned(1))) touchpad_report_t;

typedef struct {
    uint8_t button; // bitmap: Button 1 | Button 2 | empty (6 bits)
    int16_t x; // between 0 and 10
    int16_t y; // between 0 and 10
} __attribute__((packed, aligned(1))) mouse_report_t;

// report sizes for feature reports
#define INPUT_MODE_REPORT_SIZE 1
#define SELECTIVE_REPORTING_REPORT_SIZE 1

// report types
#define REPORT_TYPE_INPUT 1
#define REPORT_TYPE_OUTPUT 2
#define REPORT_TYPE_FEATURE 3

BLEHidTouchpad::BLEHidTouchpad()
    : BLEHidGeneric(0, 0, 0)
{ 
    touchpad = false;

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
    chr_max_count->setFixedLen(sizeof(max_count));
    chr_max_count->setReadAuthorizeCallback(max_count_callback);
    VERIFY_STATUS( chr_max_count->begin() );

    chr_certification->setUuid(UUID16_CHR_REPORT);
    chr_certification->setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
    chr_certification->setPermission(SECMODE_ENC_NO_MITM, SECMODE_ENC_NO_MITM);
    chr_certification->setReportRefDescriptor(REPORTID_CERTIFICATION, REPORT_TYPE_FEATURE);
    chr_certification->setFixedLen(sizeof(certification));
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

    return ERROR_NONE;
}

void BLEHidTouchpad::max_count_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_read_t* request)
{
    //  Serial.print("max count callback ");
    //  Serial.print(sizeof(max_count));
    //  Serial.print(" ");
    //  Serial.print(max_count);
    //  Serial.print(" ");

    ble_gatts_rw_authorize_reply_params_t reply;
    reply.type = BLE_GATTS_AUTHORIZE_TYPE_READ;
    reply.params.read = ((ble_gatts_authorize_params_t) {
        .gatt_status = BLE_GATT_STATUS_SUCCESS,
        .update      = 0,
        .offset      = request->offset,
        .len         = sizeof(max_count),
        .p_data      = &max_count
    });
    
    sd_ble_gatts_rw_authorize_reply(conn_hdl, &reply);
    // Serial.println(sd_ble_gatts_rw_authorize_reply(conn_hdl, &reply));
}

void BLEHidTouchpad::certification_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_read_t* request)
{
    //  Serial.print("certification callback ");
    //  Serial.print(request->offset);
    //  Serial.print(" ");

    ble_gatts_rw_authorize_reply_params_t reply;
    reply.type = BLE_GATTS_AUTHORIZE_TYPE_READ;
    reply.params.read = ((ble_gatts_authorize_params_t) {
        .gatt_status = BLE_GATT_STATUS_SUCCESS,
        .update      = 0,
        .offset      = request->offset,
        .len         = sizeof(certification),
        .p_data      = certification
    });

    sd_ble_gatts_rw_authorize_reply(conn_hdl, &reply);
    // Serial.println(sd_ble_gatts_rw_authorize_reply(conn_hdl, &reply));
}

void BLEHidTouchpad::input_mode_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_write_t* request)
{
    // Serial.print("input mode callback ");
    // Serial.print(request->data[0]);
    // Serial.print(" ");

    ble_gatts_rw_authorize_reply_params_t reply;
    reply.type = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
    reply.params.write = ((ble_gatts_authorize_params_t) {
        .gatt_status = BLE_GATT_STATUS_SUCCESS,
        .update      = 1,
        .offset      = request->offset,
        .len         = 0,
        .p_data      = NULL
    });

    sd_ble_gatts_rw_authorize_reply(conn_hdl, &reply);
    // Serial.println(sd_ble_gatts_rw_authorize_reply(conn_hdl, &reply));

    BLEHidTouchpad& svc = (BLEHidTouchpad&) chr->parentService();
    svc.touchpad = (request->data[0] == 3);
}

void BLEHidTouchpad::selective_reporting_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_write_t* request)
{
    // Serial.print("selective reporting callback ");
    // Serial.print(request->data[0]);
    // Serial.print(" ");

    ble_gatts_rw_authorize_reply_params_t reply;
    reply.type = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
    reply.params.write = ((ble_gatts_authorize_params_t) {
        .gatt_status = BLE_GATT_STATUS_SUCCESS,
        .update      = 1,
        .offset      = request->offset,
        .len         = 0,
        .p_data      = NULL
    });

    sd_ble_gatts_rw_authorize_reply(conn_hdl, &reply);
    // Serial.println(sd_ble_gatts_rw_authorize_reply(conn_hdl, &reply));
}


bool BLEHidTouchpad::send_report(
    bool tip_switch1, uint8_t contact_id1, int16_t x1, int16_t y1,
    bool tip_switch2, uint8_t contact_id2, int16_t x2, int16_t y2,
    int16_t scan_time, int8_t contact_count, bool button
) {

    if (!touchpad) {
      return false;
    }
    
    touchpad_report_t report;
    report.contact_data1 = tip_switch1 + (tip_switch1 << 1) + (contact_id1 << 2);
    report.x1 = x1;
    report.y1 = y1;
    report.contact_data2 = tip_switch2 + (tip_switch2 << 1) + (contact_id2 << 2);
    report.x2 = x2;
    report.y2 = y2;
    report.scan_time = scan_time;
    report.contact_count = contact_count;
    report.button = button;

    // Serial.println(sizeof(report));
    // Serial.print("data1: ");
    // Serial.print(report.contact_data1, BIN);
    // Serial.print(" x1: ");
    // Serial.print(report.x1);
    // Serial.print(" y1: ");
    // Serial.println(report.y1);
    // Serial.print("data2: ");
    // Serial.print(report.contact_data2, BIN);
    // Serial.print(" x2: ");
    // Serial.print(report.x2);
    // Serial.print(" y2: ");
    // Serial.println(report.y2);
    // Serial.print("scan time: ");
    // Serial.print(report.scan_time);
    // Serial.print(" contact count: ");
    // Serial.print(report.contact_count);
    // Serial.print(" button: ");
    // Serial.println(button);
    // Serial.println();

    return chr_touchpad->notify(BLE_CONN_HANDLE_INVALID, &report, sizeof(report));
}