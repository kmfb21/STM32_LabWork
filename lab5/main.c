/* main.c --- 
 * 
 * Filename: main.c
 * Description: word count
 * Author: Bo Fang (bofang)
 *         Omar White (omawhite)
 * Maintainer: Omar White (omawhite)
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: Thu Feb 11 23:21:20 2016
 *           By: Bo Fang (bofang)
 *     Update #: 0
 * Keywords: Word Count
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

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  //wordcount
  int lines = 0;//set initial count variables
  int words = 0;
  int characters = 0;

  int c; /* current character */
  while (1){
    while ((c = getchar()) != 0x1b) {//if we have not read to end yet
        characters++;//one more character
        if (c=='\n') {
            lines++;//if there is a new line \n, word+1 and line+1
            words++;
        }
        if (c==' ' || c=='\t' || c=='\r' || c=='\f' || c=='\v') {
            words++;//if anything else to stop a word, word+1
        }
    }
    printf("%d  %d %d\n", lines, words, characters);//output
  }
  return 0;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
