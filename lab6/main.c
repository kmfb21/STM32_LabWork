/**********************************************************
 * main.c for lab6
 *
 * Author: Bo Fang (bofang)
 *         Carson Reid Schwalm (cschwalm)
 * Date Created: 02/21/2016
 * Last Modified by: Bo Fang (bofang)
 * Date Last Modified: 02/21/2016
 * Assignment: Lab6
 * Part of: CS-Spring-2016
 */

//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

int main(void){

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
//initial uart led gyro btn
  f3d_uart_init();
  f3d_led_init();
  f3d_gyro_init();
  f3d_user_btn_init();
//v[] for velocity
  float v[3];
//statement recording x or y or z
  short statement = 0;
  while(1) {
    //getdata and print it
    f3d_gyro_getdata(v);
    printf("%f\n",v[statement]);
    if(user_btn_read()) {
      statement++;
      statement %= 3;
      while(user_btn_read());
    }
    if(v[statement]>-5 && v[statement]<5){
      f3d_led_off(0);
    }else{
      f3d_led_on(0);
    }
    //positive
    if(v[statement]>=5){
      f3d_led_on(7);
    }else{
      f3d_led_off(7);
    }
    if(v[statement]>=50){
      f3d_led_on(6);
    }else{
      f3d_led_off(6);
    }
    if(v[statement]>=100){
      f3d_led_on(5);
    }else{
      f3d_led_off(5);
    }
    if(v[statement]>=300){
      f3d_led_on(4);
    }else{
      f3d_led_off(4);
    }
    //negative
    if(v[statement]<=-5){
      f3d_led_on(1);
    }else{
      f3d_led_off(1);
    }
    if(v[statement]<=-50){
      f3d_led_on(2);
    }else{
      f3d_led_off(2);
    }
    if(v[statement]<=-100){
      f3d_led_on(3);
    }else{
      f3d_led_off(3);
    }
    if(v[statement]<=-300){
      f3d_led_on(4);
    }else{
      f3d_led_off(4);
    }
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
