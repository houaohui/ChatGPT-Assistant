/*
 *@author: HAH (BiliBili: iccery)
 */
#ifndef _TXT_VIEWER_H_
#define _TXT_VIEWER_H_

// 支持英文和中文不同宽度
#define SUPPORT_DIFFERENT_CHAR_W  1
#define SUPPORT_TABLE_WIDTH       0

#if defined (__cplusplus) || defined (c_plusplus)
extern "C" {
#endif

#include "stdbool.h"
#include "string.h"
#include "typedef.h"
#include <wchar.h>


typedef enum
{
	NORMAL,
	AUTO_BREAKLINE,
	CONSOLE_PRINT,
} p_mode_t;

typedef struct disp_controlBlock{
	//开始显示字符的索引值，也就是屏幕中第一个显示的字符在缓存中的位置
	u16 start_charIdx;
	//储存字符的索引值
	u16 store_charIdx;
	//光标位置
	u16 cursor_idx;
}disp_cb_t;

typedef struct txtViewer txtViewer_t;

struct txtViewer{
	p_mode_t process_mode;
	//为了方便键盘输入，当使用键盘模式时，数据是一个一个字符输入进去的，遇到换行会立即换行显示，普通模式如果换行符后面没有任何字符是不会显示出来空白的
	u8 keyboard_mode;
	u8 cmd_mode;
	u8 filterOut_char;
	s16 txt_ofsetX;
	s16 txt_ofsetY;
	u8 cursor_enable;
	u8 scroll_anim;
	u8 scroll_enable;
	// 用于形成行动画，记录每行处理过的字符个数
	u16 processd_cnt;
	// 同processd_cnt类似，用于记录处理过的字符的像素值，为了适应不同字体的宽度不同
	int processd_pixel;
	//光标的坐标
	u16 cursor_lineY;
	u16 cursor_lineX;
	u8 win_boundary;
	wchar_t getchar;
	u8 input_updata;
	u8 loop_show;
	s16 scroll_pixel;
	s16 window_x;
	s16 window_y;
	s16 window_h;
	s16 window_w;
	u8 char_h;
	u8 char_w;
	wchar_t *data_buf;
	u16 buf_size;
	disp_cb_t disp_cb;
	void (*process)(txtViewer_t *viewer);
	void (*run)(txtViewer_t *viewer);
	//在末尾打印
	void (*printf)(txtViewer_t *viewer, wchar_t *fmt, ...);
};

extern txtViewer_t txtViewer;

void txt_test_open(void);

void txtViewer_init(txtViewer_t *viewer, int size, s16 win_x, s16 win_y, p_mode_t p_mode);
void txtViewer_getChar(txtViewer_t *viewer, wchar_t data);
void txtViewer_setWindow(txtViewer_t *viewer, s16 h, s16 w);
//切换字符源
void txtViewer_changeSource(txtViewer_t *viewer, txtViewer_t *new_source);
//切换解析器
void txtViewer_changeProcessMode(txtViewer_t *viewer, p_mode_t p_mode);
//在光标删除
// void txtViewer_CursorDeleteChar(txtViewer_t *viewer);
// //在光标添加
// void txtViewer_CursorAddChar(txtViewer_t *viewer, wchar_t data);
// //在末尾删除一个字符，用于cmd
// void txtViewer_DeleteLastStoreChar(txtViewer_t *viewer);

#if defined (__cplusplus) || defined (c_plusplus)
}
#endif
#endif
