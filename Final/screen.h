#include<stdint.h>

#define COLLISION_TOP 1
#define COLLISION_BOTTOM 2
#define COLLISION_LEFT 3
#define COLLISION_RIGHT 4

typedef struct rect {
  uint8_t pos_x;
  uint8_t pos_y;
  uint8_t width;
  uint8_t depth;
  uint16_t color;
} rect_t;
void initRect(rect_t *, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
void eraseRect(rect_t *, uint16_t);
void redrawRect(rect_t *);
int moveRect(rect_t *, int8_t, int8_t, uint16_t);

//void f3d_lcd_drawPixel(uint8_t x, uint8_t y, uint16_t color);
//void f3d_lcd_fillScreen(uint16_t);
//void f3d_lcd_drawChar(uint8_t, uint8_t, unsigned char, uint16_t, uint16_t);
//void f3d_lcd_drawString(uint8_t, uint8_t, char *, uint16_t, uint16_t);
void f3d_lcd_drawRectangle(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
