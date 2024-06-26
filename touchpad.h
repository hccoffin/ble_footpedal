#include "services/BLEHidGeneric.h"

class BLEHidTouchpad : public BLEHidGeneric
{
  public:
    boolean touchpad;

    BLEHidTouchpad();
    virtual err_t begin();
    bool send_report(
      bool tip_switch1, uint8_t contact_id1, int16_t x1, int16_t y1,
      bool tip_switch2, uint8_t contact_id2, int16_t x2, int16_t y2, 
      int16_t scan_time, int8_t contact_count, bool button=false
    );
    bool sendMouseReport(uint8_t button, int8_t x, int8_t y);
    bool put_down_fingers(int8_t n_fingers);

  protected:
    BLECharacteristic* chr_touchpad;
    BLECharacteristic* chr_max_count;
    BLECharacteristic* chr_certification;
    BLECharacteristic* chr_input_mode;
    BLECharacteristic* chr_selective_reporting;
    BLECharacteristic* chr_mouse;

    static void max_count_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_read_t* request);
    static void certification_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_read_t* request);
    static void certification_write_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_write_t* request);
    static void input_mode_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_write_t* request);
    static void selective_reporting_callback(uint16_t conn_hdl, BLECharacteristic* chr, ble_gatts_evt_write_t* request);
};
