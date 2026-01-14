#include <stdint.h>
#include <stdbool.h>

enum {
    HID_TEXT_LINE  = 0xD0,
    HID_TEXT_CLEAR = 0xD1,
};

#define DISPLAY_TEXT_MAX_BYTES 29
#define DISPLAY_MAX_LINES 20

void display_process_raw_hid_data(uint8_t *data, uint8_t length);
void ui_init(void);
