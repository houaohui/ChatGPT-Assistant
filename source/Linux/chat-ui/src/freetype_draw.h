#ifndef FREETYPE_DRAW_H
#define FREETYPE_DRAW_H

#if defined (__cplusplus) || defined (c_plusplus)
extern "C" {
#endif

#include "typedef.h"
#include <math.h>

#include <wchar.h>

void freetype_test_init();
void freetype_test_draw();
void freetype_test_close();
void freetype_clean_screen();
void freetype_clean_screen_block(int x, int y, int width, int height);

void lcd_draw_character(int x, int y, const wchar_t *str, unsigned int color);
void lcd_draw_character_cache(int x, int y, const wchar_t *str, unsigned int color);
void freetype_show_cpu_usage(float usage);

void freetype_fill_screen();
void freetype_draw_one_char(const wchar_t *str, unsigned int color, s16 x, s16 y, s16 win_start_x, s16 win_start_y, s16 win_end_x, s16 win_end_y);

void freetype_draw_one_char_cache(const wchar_t *str, unsigned int color, s16 x, s16 y, s16 win_start_x, s16 win_start_y, s16 win_end_x, s16 win_end_y);

#if defined (__cplusplus) || defined (c_plusplus)
}
#endif

#endif
