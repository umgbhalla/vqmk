#include "ui.h"
#include "qp.h"
#include <string.h>
#include "stdio.h"

// Include a font - use thintel15 which is commonly available in QMK
#include "thintel15.qff.h"

// Display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

// Text buffer for console
static char console_buffer[DISPLAY_MAX_LINES][DISPLAY_TEXT_MAX_BYTES + 1];
static int console_line_count = 0;
static int current_y = 0;

// External display device from display.c
extern painter_device_t display;

// Font handle
static painter_font_handle_t font;

static void append_console_line(const char *text);

void ui_screen_init(void) {
    // Initialize console buffer
    memset(console_buffer, 0, sizeof(console_buffer));
    console_line_count = 0;
    current_y = 2;

    // Load the font
    font = qp_load_font_mem(font_thintel15);

    // Clear entire screen (black)
    qp_rect(display, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, 0, 0, true);
    qp_flush(display);
}

void ui_housekeeping(void) {
    // Nothing
}

static void append_console_line(const char *text) {
    // Check if we need to scroll (screen full)
    if (current_y + 12 > SCREEN_HEIGHT) {
        // Need to scroll - clear console area
        qp_rect(display, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, 0, 0, true);

        // Reset Y position and redraw all lines
        current_y = 2;
        int lines_to_show = console_line_count;
        if (lines_to_show > DISPLAY_MAX_LINES) {
            lines_to_show = DISPLAY_MAX_LINES;
        }
        int start_line = console_line_count - lines_to_show;

        for (int i = start_line; i < console_line_count; i++) {
            qp_drawtext(display, 2, current_y, font, console_buffer[i]);
            current_y += 9;
        }
    } else {
        // Just append the new line at current position
        qp_drawtext(display, 2, current_y, font, text);
        current_y += 9;
    }

    // Flush after drawing
    qp_flush(display);
}

void display_process_raw_hid_data(uint8_t *data, uint8_t length) {
    if (length < 1) {
        return;
    }
    uint8_t data_type = data[0];

    switch (data_type) {
        case HID_TEXT_LINE:
            if (length >= 3) {
                uint8_t text_len = data[2];
                if (text_len > DISPLAY_TEXT_MAX_BYTES) {
                    text_len = DISPLAY_TEXT_MAX_BYTES;
                }
                if ((uint8_t)(3 + text_len) > length) {
                    text_len = (uint8_t)(length - 3);
                }

                // Store in buffer
                if (console_line_count >= DISPLAY_MAX_LINES) {
                    // Shift lines up in buffer
                    memmove(console_buffer[0], console_buffer[1],
                            sizeof(char) * (DISPLAY_MAX_LINES - 1) * (DISPLAY_TEXT_MAX_BYTES + 1));
                    console_line_count = DISPLAY_MAX_LINES - 1;
                }

                memset(console_buffer[console_line_count], 0, DISPLAY_TEXT_MAX_BYTES + 1);
                if (text_len > 0) {
                    memcpy(console_buffer[console_line_count], &data[3], text_len);
                }

                // Append this line to display
                append_console_line(console_buffer[console_line_count]);
                console_line_count++;
            }
            break;

        case HID_TEXT_CLEAR:
            // Clear console buffer
            memset(console_buffer, 0, sizeof(console_buffer));
            console_line_count = 0;
            current_y = 2;

            // Clear screen
            qp_rect(display, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, 0, 0, true);
            qp_flush(display);
            break;

        default:
            break;
    }
}
