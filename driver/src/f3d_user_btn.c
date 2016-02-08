/**********************************************************
 * f3d_user_btn.c
 *
 * contains the init and read functions for the User Button
 *
 * Author: Bo Fang (bofang)
 *         Ziyu Xiang (ziyxiang)
 * Date Created: 02/08/2016
 * Last Modified by: Ziyu Xiang (ziyxiang)
 * Date Last Modified: 02/08/2016
 * Assignment: Lab4
 * Part of: CS-Spring-2016
 */

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>


/*Initialization of the UserButton*/
void f3d_user_btn_init(void){

  //initialize the GPIO structure
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  //user button input
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  //enable the clock signal
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  //initialize Pin A
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*reads the User Button*/
int user_btn_read(void){
  return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);  
}
