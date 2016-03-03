/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TIMER 20000

void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);


int main(void) { 
  // If you have your inits set up, this should turn your LCD screen red
  f3d_lcd_init();
  f3d_gyro_init();
  f3d_lcd_fillScreen(WHITE);

  /* Gyro array */
  float gData[3];
  char writeData[10];

  while(1) {
      //delay(10);
      f3d_gyro_getdata(gData);
      snprintf(writeData, 10, "%f", gData[0]);
      f3d_lcd_drawString(1, 1, "x = ", BLACK, WHITE);
      f3d_lcd_drawString(30, 1, writeData, BLACK, WHITE);
      snprintf(writeData, 10, "%f", gData[1]);
      f3d_lcd_drawString(1, 11, "y = ", BLACK, WHITE);
      f3d_lcd_drawString(30, 11, writeData, BLACK, WHITE);
      snprintf(writeData, 10, "%f", gData[2]);
      f3d_lcd_drawString(1, 21, "z = ", BLACK, WHITE);
      f3d_lcd_drawString(30, 21, writeData, BLACK, WHITE);

      drawRectangle(10,80-gData[0]/10,20,ST7735_height, RED);
      drawRectangle(10,20,20,80-gData[0]/10, WHITE);

      drawRectangle(50,80-gData[1]/10,60,ST7735_height, GREEN);
      drawRectangle(50,20,60,80-gData[1]/10, WHITE);

      drawRectangle(100,80-gData[2]/10,110,ST7735_height, BLUE);
      drawRectangle(100,20,110,80-gData[2]/10, WHITE);
      //
      //
      //
      //
      //
      //
      //
      //
      //
  }
}

void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color) {
    int i, j;
    for(i = x1; i < x2; i++) {
	for(j = y1; j < y2; j++) {
	    f3d_lcd_drawPixel(i, j, color);
	}
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */

