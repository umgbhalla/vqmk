#include "ui.h"
#include "qp.h"
#include <string.h>

// Include font
#include "thintel15.qff.h"

// Display
extern painter_device_t display;
static painter_font_handle_t font = NULL;

// Console buffer - stores lines by index
static char console_buffer[DISPLAY_MAX_LINES][DISPLAY_TEXT_MAX_BYTES + 1];
static int line_count = 0;

// Track which lines have been modified
static bool line_modified[DISPLAY_MAX_LINES];

// Layout
static uint16_t display_width = 0;
static uint16_t display_height = 0;
static uint8_t font_line_height = 0;
static int max_lines = 0;

void ui_screen_init(void) {
    // Load font
    font = qp_load_font_mem(font_thintel15);

    // Get display dimensions
    display_width = qp_get_width(display);
    display_height = qp_get_height(display);

    // Get font line height
    font_line_height = ((painter_font_desc_t*)font)->line_height;

    // Use tighter spacing - overlap lines slightly for more content
    max_lines = 15;  // Force 15 lines with tight spacing

    // Clear modification flags
    memset(line_modified, 0, sizeof(line_modified));

    // Clear screen to black
    qp_rect(display, 0, 0, display_width - 1, display_height - 1, 0, 0, 0, true);
    qp_flush(display);
}

void display_process_raw_hid_data(uint8_t *data, uint8_t length) {
    if (length < 1) return;

    uint8_t type = data[0];

    if (type == HID_TEXT_CLEAR) {
        // Clear buffer
        memset(console_buffer, 0, sizeof(console_buffer));
        memset(line_modified, 0, sizeof(line_modified));
        line_count = 0;
        qp_rect(display, 0, 0, display_width - 1, display_height - 1, 0, 0, 0, true);
        qp_flush(display);
        return;
    }

    if (type == HID_TEXT_LINE && length >= 3 && font != NULL) {
        uint8_t line_index = data[1];
        uint8_t text_len = data[2];

        if (text_len > DISPLAY_TEXT_MAX_BYTES) text_len = DISPLAY_TEXT_MAX_BYTES;
        if ((3 + text_len) > length) text_len = length - 3;

        // Check if line actually changed
        bool changed = false;
        if (line_index < DISPLAY_MAX_LINES) {
            // Compare with existing
            if (text_len != strlen(console_buffer[line_index]) ||
                memcmp(console_buffer[line_index], &data[3], text_len) != 0) {
                changed = true;

                // Update buffer
                memset(console_buffer[line_index], 0, DISPLAY_TEXT_MAX_BYTES + 1);
                if (text_len > 0) {
                    memcpy(console_buffer[line_index], &data[3], text_len);
                }

                // Mark as modified
                line_modified[line_index] = true;

                // Track line count
                if (line_index >= line_count) {
                    line_count = line_index + 1;
                }
            }
        }

        // Only redraw if something changed
        if (changed) {
            // Clear and redraw ONLY modified lines
            for (int i = 0; i < DISPLAY_MAX_LINES; i++) {
                if (line_modified[i] && i < line_count) {
                    // Calculate line position
                    int y = i * 10;  // 10px spacing

                    // Clear this line area
                    qp_rect(display, 0, y, display_width - 1, y + 9, 0, 0, 0, true);

                    // Draw the line
                    if (console_buffer[i][0] != '\0') {
                        qp_drawtext(display, 1, y, font, console_buffer[i]);
                    }

                    line_modified[i] = false;
                }
            }

            qp_flush(display);
        }
    }
}
