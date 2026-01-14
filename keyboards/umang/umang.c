
#include "quantum.h"
#include "print.h"
#include "display.h"
void housekeeping_task_kb(void) {
    display_housekeeping_task();
    housekeeping_task_user();
}
void keyboard_post_init_kb(void)
{
    display_init_kb();
    keyboard_post_init_user();
}
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}
