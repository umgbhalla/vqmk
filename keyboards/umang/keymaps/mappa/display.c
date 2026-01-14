#include "display.h"
#include <string.h>
#include "quantum.h"
#include "qp.h"
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include "ui/ui.h"

painter_device_t qp_st7735_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);

// Global display device
painter_device_t display;

bool display_init_kb(void) {
    wait_ms(50);

    display = qp_st7735_make_spi_device(128, 160, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 0);
    qp_set_viewport_offsets(display, 0, 0);

    if (!qp_init(display, QP_ROTATION_180)) {
        return false;
    }

    // Clear the display
    qp_clear(display);
    qp_flush(display);

    keyboard_post_init_user();
    ui_init();

    return true;
}

// Housekeeping task for UI updates (volume overlay timer, etc.)
void display_housekeeping_task(void) {
    ui_housekeeping();
}
