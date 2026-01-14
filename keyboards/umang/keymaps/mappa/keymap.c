
#include QMK_KEYBOARD_H
#include "layers.h"
#include "display.h"
#include "quantum.h"
#include "raw_hid.h"
#include "ui/ui.h"
#include "qp.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
         
  MO(_NUMPAD),   KC_1,   QK_BOOT,  
  KC_3,   KC_4,   KC_5, 
  KC_6,   KC_7,   KC_8, 
  KC_9,   KC_0,   KC_W,KC_X
  
),

[_NUMPAD] = LAYOUT(
    KC_GRV, KC_1,   KC_2,  
    KC_3,   KC_4,   KC_5, 
    KC_6,   KC_7,   KC_8, 
    KC_9,   KC_0,   KC_W,KC_X
),


[_SYMBOL] = LAYOUT(
    KC_GRV,   KC_1,   KC_2,  
    KC_3,   KC_4,   KC_5, 
    KC_6,   KC_7,   KC_8, 
    KC_9,   KC_0,   KC_W,KC_X
),
[_MAGIC] = LAYOUT(
    KC_GRV,   KC_1,   KC_2,  
    KC_3,   KC_4,   KC_5, 
    KC_6,   KC_7,   KC_8, 
    KC_9,   KC_0,   KC_W,KC_X
)
};


void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    display_process_raw_hid_data(data, length);
}
