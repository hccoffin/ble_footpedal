#include "services/BLEHidGeneric.h"

class BLEHidTouchpad : public BLEHidGeneric
{
  public:
    BLEHidTouchpad();
    virtual err_t begin();
    bool send_report(bool tip_switch, uint8_t contact_id, int16_t x, int16_t y, int16_t scan_time, int8_t contact_count=0, bool button=false, bool confidence=false);
    bool put_down_fingers(int8_t n_fingers);
  protected:

};
