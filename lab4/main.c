/**********************************************************
 * main.c
 *
 * Testing LEDs and Button
 *
 * Author: Bo Fang (bofang)
 *         Ziyu Xiang (ziyxiang)
 * Date Created: 02/08/2016
 * Last Modified by: Bo Fang (bofang)
 * Date Last Modified: 02/08/2016
 * Assignment: Lab4
 * Part of: CS-Spring-2016
 */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {

  //initial
  int i = 0;
  f3d_led_init();
  f3d_user_btn_init();  

  while(1) {
    for (i = 0; i < 8; i++) {//8 LEDs sequentially using a for loop
      f3d_led_on(i);
      delay();
      while (user_btn_read());//if butten is pressed stop here
      f3d_led_off(i);
    }
    f3d_led_all_on();//LEDs all on
    delay();
    f3d_led_all_off();//LEDs all off
    delay();
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
