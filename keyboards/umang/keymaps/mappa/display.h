#pragma once
#include "qp.h"
#include <stdint.h>
#include <stdbool.h>

// Global display device declaration
extern painter_device_t display;
bool display_init_kb(void);
void display_housekeeping_task(void);



