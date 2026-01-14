

#pragma once

#include_next <lv_conf.h>

#define QP_LVGL_TASK_PERIOD 30
#define LV_USE_THEME_DEFAULT 1
/* change default font */
#undef LV_FONT_MONTSERRAT_12
#define LV_FONT_MONTSERRAT_12 1
#undef LV_FONT_MONTSERRAT_24
#define LV_FONT_MONTSERRAT_24 1
#undef LV_FONT_MONTSERRAT_40
#define LV_FONT_MONTSERRAT_40 1
#undef LV_FONT_DEFAULT
#define LV_FONT_DEFAULT &lv_font_montserrat_12


