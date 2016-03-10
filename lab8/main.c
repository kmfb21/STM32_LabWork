/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Bo Fang(bofang)
 * Maintainer: Bo Fang(bofang)
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 03/03/2016
 *           By: Bo Fang(bofang)
 *     Update #: 
 * Keywords: 
 * Compatibility: 
 * 
 */
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <math.h>
#define TIMER 20000

float vtoa(float v) {
  return asin(v)/3.1415926*180;
}

int main(void) {
   setvbuf(stdin, NULL, _IONBF, 0);
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);

  // Set up your inits before you go ahead
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);

  f3d_user_btn_init();
  f3d_lcd_init();

  f3d_lcd_fillScreen(WHITE);

  float acc[3];
  float mag[3];
  char writeData[10];

  float pitch,roll,head;
  float x,y,lastx,lasty,lastp,lastr;
  while(1) {
    //get acceleration
    f3d_accel_read(acc);
    //pitch and print out
    pitch = atan(acc[0]/sqrt(acc[1]*acc[1]+acc[2]*acc[2]));
    pitch = pitch * 180 / M_PI;
    snprintf(writeData, 10, "%f", pitch);
    f3d_lcd_drawString(1, 1, "pitch = ", BLACK, WHITE);
    f3d_lcd_drawString(40, 1, writeData, BLACK, WHITE);
    //roll and print out
    roll = atan(acc[1]/sqrt(acc[0]*acc[0]+acc[2]*acc[2]));
    roll *= 180 / M_PI;
    snprintf(writeData, 10, "%f", roll);
    f3d_lcd_drawString(1, 11, "roll = ", BLACK, WHITE);
    f3d_lcd_drawString(40, 11, writeData, BLACK, WHITE);
    //get mag and calcuate heading angle
    f3d_mag_read(mag);
    head = atan(mag[1]/mag[0]);
    head *= 180 / M_PI;
    snprintf(writeData, 10, "%f", head);
    f3d_lcd_drawString(1, 21, "head = ", BLACK, WHITE);
    f3d_lcd_drawString(40, 21, writeData, BLACK, WHITE);
    //begin drawing and update drawing
    f3d_lcd_drawString(1, 41, "Pitch Roll:", BLACK, WHITE);
    f3d_lcd_drawChar(0-lastr*0.5+60, 0-lastp*0.5+60, 0x40, WHITE, WHITE);
    f3d_lcd_drawChar(0-roll*0.5+60, 0-pitch*0.5+60,0x40, BLACK, WHITE);
    f3d_lcd_drawString(45, 120, "CP", BLUE, WHITE);
    lastp=pitch;lastr=roll;

    f3d_lcd_drawString(1, 91, "Compass:", BLACK, WHITE);
    x = mag[1];
    y = mag[0];
    f3d_lcd_drawChar(lastx*100+50, lasty*100+120, 0x4e, WHITE, WHITE);
    f3d_lcd_drawChar(x*100+50, y*100+120,0x4e, RED, WHITE);
    f3d_lcd_drawString(45, 120, "CP", BLUE, WHITE);
    lastx=x;lasty=y;
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

