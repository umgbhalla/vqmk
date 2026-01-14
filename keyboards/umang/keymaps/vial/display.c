#include "display.h"
#include "quantum.h"
#include "qp.h"
#include "ui/ui.h"

painter_device_t qp_st7735_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);

painter_device_t display;

bool display_init_kb(void) {
    wait_ms(50);

    display = qp_st7735_make_spi_device(128, 160, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 0);
    qp_set_viewport_offsets(display, 0, 0);

    if (!qp_init(display, QP_ROTATION_180)) {
        return false;
    }

    if (!qp_power(display, true)) {
        return false;
    }

    // Clear to black
    qp_rect(display, 0, 0, 127, 159, 0, 0, 0, true);
    qp_flush(display);

    keyboard_post_init_user();
    ui_init();

    return true;
}

void display_housekeeping_task(void) {
    // Nothing - no animations
}
