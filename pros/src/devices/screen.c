/**
 * \file screen.c
 *
 * \brief Brain screen display and touch functions.
 *
 * Contains user calls to the v5 screen for touching and displaying graphics.
 *
 * \copyright (c) 2017-2023, Purdue University ACM SIGBots.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "pros/screen.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "kapi.h"
#include "pros/apix.h"
#include "v5_api.h"  // vexDisplay* 

/******************************************************************************/
/**                  Screen Graphical Display Functions                      **/
/**                                                                          **/
/**   These functions allow programmers to display shapes on the v5 screen   **/
/******************************************************************************/

extern mutex_t screen_mutex;


typedef struct touch_event_position_data_s {
	int16_t x;
	int16_t y;
} touch_event_position_data_s_t;

uint32_t screen_set_pen(uint32_t color){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayForegroundColor(color);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_set_eraser(uint32_t color){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayBackgroundColor(color);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_get_pen(void){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	uint32_t color = vexDisplayForegroundColorGet();
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	}
	return color;
}

uint32_t screen_get_eraser(void){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	uint32_t color = vexDisplayBackgroundColorGet();
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	}
	return color;
}

uint32_t screen_erase(void){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayErase();
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_scroll(int16_t start_line, int16_t lines){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayScroll(start_line, lines);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_scroll_area(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lines){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayScrollRect(x0, y0, x1, y1, lines);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_copy_area(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t* buf, int32_t stride){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayCopyRect(x0, y0, x1, y1, buf, stride);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_draw_pixel(int16_t x, int16_t y){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayPixelSet(x, y);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_erase_pixel(int16_t x, int16_t y){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayPixelClear(x, y);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayLineDraw(x0, y0, x1, y1);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_erase_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayLineClear(x0, y0, x1, y1);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_draw_rect(int16_t x0, int16_t y0, int16_t x1, int16_t y1){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayRectDraw(x0, y0, x1, y1);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_erase_rect(int16_t x0, int16_t y0, int16_t x1, int16_t y1){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayRectClear(x0, y0, x1, y1);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_fill_rect(int16_t x0, int16_t y0, int16_t x1, int16_t y1){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayRectFill(x0, y0, x1, y1);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_draw_circle(int16_t x, int16_t y, int16_t radius){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayCircleDraw(x, y, radius);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_erase_circle(int16_t x, int16_t y, int16_t radius){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayCircleClear(x, y, radius);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_fill_circle(int16_t x, int16_t y, int16_t radius){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	vexDisplayCircleFill(x, y, radius);
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

/******************************************************************************/
/**                       Screen Text Display Functions                      **/
/**                                                                          **/
/**     These functions allow programmers to display text on the v5 screen   **/
/******************************************************************************/

uint32_t screen_print(text_format_e_t txt_fmt, const int16_t line, const char* text, ...){
    va_list args;
    va_start(args, text);
    if (screen_vprintf(txt_fmt, line, text, args) == PROS_ERR) {
		return PROS_ERR;
	}
    va_end(args);
	return 1;
}

uint32_t screen_print_at(text_format_e_t txt_fmt, int16_t x, int16_t y, const char* text, ...){
    va_list args;
    va_start(args, text);
    if (screen_vprintf_at(txt_fmt, x, y, text, args) == PROS_ERR) {
		return PROS_ERR;
	}
    va_end(args);
	return 1;
}

uint32_t screen_vprintf(text_format_e_t txt_fmt, const int16_t line, const char* text, va_list args){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	char* out;
	vasprintf(&out, text, args);
	va_list empty;
	switch(txt_fmt){
	case E_TEXT_SMALL:
	case E_TEXT_MEDIUM:
		{
            vexDisplayVString(line, out, empty);
            break;
        }
    case E_TEXT_LARGE:
		{
            vexDisplayVBigString(line, out, empty);
            break;
        }
    case E_TEXT_MEDIUM_CENTER:
		{
            vexDisplayVCenteredString(line, out, empty);
            break;
        }
    case E_TEXT_LARGE_CENTER:
        {
            vexDisplayVBigCenteredString(line, out, empty);
            break;
        }
    default:
        {
            vexDisplayVString(line, out, empty);
            break;
        }
    }
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}

uint32_t screen_vprintf_at(text_format_e_t txt_fmt, const int16_t x, const int16_t y, const char* text, va_list args){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_ERR;
	}
	char* out;
	vasprintf(&out, text, args);
	va_list empty;
	switch(txt_fmt){
    case E_TEXT_SMALL:
		{
            vexDisplayVSmallStringAt(x, y, out, empty);
            break;
        }
    case E_TEXT_MEDIUM:
    case E_TEXT_MEDIUM_CENTER:
		{
            vexDisplayVStringAt(x, y, out, empty);
            break;
        }
    case E_TEXT_LARGE:
    case E_TEXT_LARGE_CENTER:
		{
            vexDisplayVBigStringAt(x, y, out, empty);
            break;
        }
    default:
        {
            vexDisplayVStringAt(x, y, out, empty);
            break;
        }
    }
	if (!mutex_give(screen_mutex)) {
		return PROS_ERR;
	} else {
		return 1;
	}
}
/******************************************************************************/
/**                         Screen Touch Functions                           **/
/**                                                                          **/
/**               These functions allow programmers to access                **/
/**                    information about screen touches                      **/
/******************************************************************************/

static const screen_touch_status_s_t PROS_SCREEN_ERR = {.touch_status = E_TOUCH_ERROR, .x = -1, .y = -1, .press_count = -1, .release_count = -1};

screen_touch_status_s_t screen_touch_status(void){
	if (!mutex_take(screen_mutex, TIMEOUT_MAX)) {
		errno = EACCES;
		return PROS_SCREEN_ERR;
	}
	V5_TouchStatus v5_touch_status;
	screen_touch_status_s_t rtv;
	vexTouchDataGet(&v5_touch_status);
	rtv.touch_status = (last_touch_e_t)v5_touch_status.lastEvent;
	rtv.x = v5_touch_status.lastXpos;
	rtv.y = v5_touch_status.lastYpos;
	rtv.press_count = v5_touch_status.pressCount;
	rtv.release_count = v5_touch_status.releaseCount;
	if (!mutex_give(screen_mutex)) {
		errno = EACCES;
		return PROS_SCREEN_ERR;
	} 
	return rtv;
}

// internal functions for different mechanisms

static task_t touch_handle_task;

void display_fatal_error(const char* text) {
	// in fatal error state, cannot rely on integrity of the RTOS
	char s[50];
	strncpy(s, text, 50);
	vexDisplayForegroundColor(COLOR_RED);
	vexDisplayRectFill(0, 0, 480, 19);
	vexDisplayRectFill(0, 0, 27, 240);
	vexDisplayRectFill(453, 0, 480, 240);
	vexDisplayRectFill(0, 179, 480, 240);
	vexDisplayForegroundColor(0x1A1917);
	vexDisplayRectFill(50, 190, 130, 230);
	vexDisplayRectFill(200, 190, 280, 230);
	vexDisplayRectFill(350, 190, 430, 230);
	vexDisplayCenteredString(0, s);
}

void _touch_handle_task();

void graphical_context_daemon_initialize() {
    screen_mutex = mutex_create();
	touch_handle_task =
	    task_create(_touch_handle_task, NULL, TASK_PRIORITY_MIN + 2, TASK_STACK_DEPTH_DEFAULT,
	                       "PROS Graphics Touch Handler");
}