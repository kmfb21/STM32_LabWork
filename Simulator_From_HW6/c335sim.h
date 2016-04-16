#ifndef C335SIM_H
#define C335SIM_H
#include <stdint.h>

void Delay(int);
int c335_main(int argc, char *argv[]);

#define BLACK 0x0000
#define BLUE 0xF800
#define CYAN 0xFFE0
#define GREEN 0x07E0
#define MAGENTA 0xF81F
#define RED 0x001F
#define WHITE 0xFFFF
#define YELLOW 0x07FF
/* 
 * MADCTL [MY MX MV]
 *    MY  row address order   0 (bottom to top), 1 (top to bottom)
 *    MX  col address order   0 (right to left), 1 (left to right)
 *    MV  col/row exchange    0 normal,          1 exchange
 */

#define MADCTLGRAPHICS 0x6
#define MADCTLBMP      0x2

#define ST7735_width  128
#define ST7735_height 160

void f3d_lcd_setAddrWindow(uint16_t x0, uint16_t y0, 
			  uint16_t x1, uint16_t y1, uint8_t madctl);
void f3d_lcd_pushColor(uint16_t *color, int cnt);
void f3d_lcd_init();

#endif
