#include "freetype_draw.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <math.h>

#include <wchar.h>
#include "ft2build.h"
#include FT_FREETYPE_H


#define FB_DEV "/dev/fb0"   //LCD设备节点

#define argb8888_to_rgb565(color)  ({ \
    unsigned int temp = (color); \
    ((temp & 0xF80000UL)>>8)| \
    ((temp & 0xFC00UL)>>5)| \
    ((temp & 0xF8UL)>>3); \
})

static unsigned int width;  //LCD宽度
static unsigned int height;  //LCD高度
static unsigned short *screen_base=(void *)0;  //LCD显存基地址 RGB565
static unsigned long screen_size;
static int fd = -1;
static FT_Library library;
static FT_Face face;

// 应用层显存
static unsigned short *screen_buff = NULL;

static int fb_dev_init(void)
{
    struct fb_var_screeninfo fb_var = {0};
    struct fb_fix_screeninfo fb_fix = {0};

    /* 打开framebuffer 设备 */
    fd = open(FB_DEV, O_RDWR);
    if(0>fd) {
        fprintf(stderr, "open error %s:%s\n",FB_DEV, strerror(errno));
        return -1;
    }

    /* 获取 framebuffer 设备信息 */
    ioctl(fd,FBIOGET_VSCREENINFO, &fb_var);
    ioctl(fd,FBIOGET_FSCREENINFO, &fb_fix);

    screen_size = fb_fix.line_length * fb_var.yres;
    width = fb_var.xres;
    height = fb_var.yres;

    printf("w: %d, h: %d\n",width, height);
    /* 内存映射 */
    screen_base = mmap(NULL,screen_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(MAP_FAILED == (void *)screen_base) {
        perror("mmap error");
        close(fd);
        return -1;
    }

    /* LCD 背景刷成黑色 */
    memset(screen_base, 0x00, screen_size);
    screen_buff= (unsigned short *)malloc(screen_size * sizeof(unsigned short));

    return 0;
}

static int freetype_init(const char *font, int angle)
{
    FT_Error error;
    FT_Vector pen;
    FT_Matrix matrix;
    float rad;  //旋转角度

    /* FreeType 初始化 */
    error = FT_Init_FreeType(&library);
    if(error) {
        fprintf(stderr, "FT_New_Face error: %d\n",error);
        return -1;
    }

    /* 加载face 对象 */
    error = FT_New_Face(library,font, 0, &face);
    if(error) {
        fprintf(stderr, "FT_New_Face error: %d\n",error);
        return -1;
    }

    // /* 原点坐标 */
    // pen.x = 0 * 64;
    // pen.y = 0 * 64;

    // /* 2*2 矩阵初始化 */
    // rad = (1.0*angle/180)*3.1415; //角度转化为弧度

    // matrix.xx = (FT_Fixed)(cos(rad)* 0x10000L);
    // matrix.xy = (FT_Fixed)(sin(rad)* 0x10000L);
    // matrix.yx = (FT_Fixed)(0* 0x10000L);
    // matrix.yy = (FT_Fixed)(1* 0x10000L);

    // /* 设置 */
    // FT_Set_Transform(face, &matrix, &pen);
    error = FT_Set_Pixel_Sizes(face, 20, 0);  //设置字体大小
    if(error) {
        fprintf(stderr, "FT_New_Face error: %d\n",error);
        return -1;
    }
    return 0;
}

static void lcd_draw_character(int x, int y, const wchar_t *str, unsigned int color)
{
    unsigned short rgb565_color = argb8888_to_rgb565(color);
    FT_GlyphSlot slot = face->glyph;
    size_t len =wcslen(str);  //计算字符个数
    long int temp;
    int n;
    int i, j, p, q;
    int max_x, max_y, start_x, start_y;

    /* 循环加载各个字符 */
    for(n=0; n<len; n++) {
        
        //加载字形、转换得到位图数据
        FT_Error error;
        error = FT_Load_Char(face, str[n], FT_LOAD_RENDER);
        if(error) {
            fprintf(stderr, "Load char error: %d\n",error);
            continue;
        }

        // 计算自行轮廓上边y坐标起点位置 注意是减去bitmap_top
        start_y = y - slot->bitmap_top;
        if(0 > start_y) {
            q = -start_y;
            temp = 0;
            j = 0;
        } else {
            q = 0;
            temp = width * start_y;
            j = start_y;
        }

        // y结束位置
        max_y = start_y + slot->bitmap.rows;
        if(max_y > (int)height)
            max_y = height;
        
        for(; j < max_y; j++,q++,temp+=width) {

            start_x = x + slot->bitmap_left;  //x起点位置
            if(0 > start_x) {
                p = -start_x;
                i = 0;
            } else {
                p = 0;
                i =start_x;
            }

            max_x = start_x + slot->bitmap.width;
            if(max_x > (int)width) 
                max_x = width;
            
            for(; i < max_x; i++,p++) {
                
                //如果数据不为零，则需要填充颜色
                if(slot->bitmap.buffer[q*slot->bitmap.width + p])
                    screen_buff[temp + i] = rgb565_color;

            }
        }

        //调整到下一个字形的原点
        x += slot->advance.x/64;
        y -= slot->advance.y/64;

    }


}

void freetype_test_init()
{
    /* lcd 初始化 */
    if(fb_dev_init()) {
        printf("fb init error !\n");
        return ;
    }

    /* freetype 初始化 */
    if(freetype_init("./msyh.ttc",0)) {
        printf("freetype init error !\n");
        return ;
    }

}

void freetype_test_draw()
{
    /* 在LCD上显示 */
    printf("start draw\n");
    int y = height*0.25;
    lcd_draw_character(0,50,L"你好，你好，你好",0x9900FF);
    lcd_draw_character(0,100,L"ABCD",0x9900FF);
    lcd_draw_character(0,150,L"1234",0x9900FF);
    printf("draw finish\n");
}

void freetype_test_close()
{
    free(screen_buff);
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    munmap(screen_base,screen_size);
    close(fd);
}

void freetype_fill_screen()
{
    /* LCD 背景刷成黑色 */
    memcpy(screen_base, screen_buff, screen_size);
}

void freetype_clean_screen()
{
    /* LCD 背景刷成黑色 */
    memset(screen_buff, 0x00, screen_size);
}


void freetype_draw_one_char(const wchar_t *str, unsigned int color, s16 x, s16 y, s16 win_start_x, s16 win_start_y, s16 win_end_x, s16 win_end_y)
{
    unsigned short rgb565_color = argb8888_to_rgb565(color);
    FT_GlyphSlot slot = face->glyph;
    size_t len =wcslen(str);  //计算字符个数
    long int temp;
    int i, j, p, q;
    int max_x, max_y, start_x, start_y;

        //加载字形、转换得到位图数据
        FT_Error error;
        error = FT_Load_Char(face, str[0], FT_LOAD_RENDER);
        if(error) {
            fprintf(stderr, "Load char error: %d\n",error);
        }

        // 计算自行轮廓上边y坐标起点位置 注意是减去bitmap_top
        start_y = y - slot->bitmap_top + 16;
        if(0 > start_y) {
            q = -start_y;
            temp = 0;
            j = 0;
        } else {
            q = 0;
            temp = width * start_y;
            j = start_y;
        }

        // y结束位置
        max_y = start_y + slot->bitmap.rows;
        if(max_y > (int)height)
            max_y = height;
        
        for(; j < max_y; j++,q++,temp+=width) {

            start_x = x + slot->bitmap_left;  //x起点位置
            if(0 > start_x) {
                p = -start_x;
                i = 0;
            } else {
                p = 0;
                i =start_x;
            }

            max_x = start_x + slot->bitmap.width;
            if(max_x > (int)width) 
                max_x = width;
            
            for(; i < max_x; i++,p++) {
                
                //如果数据不为零，则需要填充颜色
                if(slot->bitmap.buffer[q*slot->bitmap.width + p])
                    screen_buff[temp + i] = rgb565_color;

            }
        }
}
