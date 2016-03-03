/**********************************************************
 * main.c for lab7 debug_printf
 *
 * Author: Bo Fang (bofang)
 *         Bradley Vine (bradvine)
 * Date Created: 02/25/2016
 * Last Modified by: Bo Fang (bofang)
 * Date Last Modified: 02/25/2016
 * Assignment: Lab7
 * Part of: CS-Spring-2016
 */

//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
//#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>
#include <stm32f30x.h>


// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out  */
  }
}

int main(void){

  f3d_led_init();
  f3d_uart_init();
  while(1){
    f3d_led_on(0);
    printf("The light on\n");
    delay();
    f3d_led_off(0);
    printf("The light off\n");
    delay();
  }

}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
