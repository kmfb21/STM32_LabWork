/* main.c --- An application that displays images relative to device orientation
 * 
 * Filename: main.c
 * Description: 
 * Author: Kyle Dijkstra
 * Partner: Bo Fang
 * Last Edited: 4/5/16
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 3/29/2016
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_systick.h>
#include <f3d_user_btn.h>
#include <f3d_rtc.h>
#include <queue.h>
#include <stdio.h>
queue_t test;
int main(void) { 


  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  f3d_user_btn_init();
  f3d_led_init();
  f3d_systick_init();
  // init_queue(&test);
  //putchar(getchar());
  /*  while(1){
    // enqueue(&test, 'b');
    //enqueue(&test, 'a');
    //putchar(test.tail);
    //dequeue(&test);
    //putchar(dequeue(&test));
    putchar(getchar());
    //printf("this works\n");
    }*/
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */

