/**********************************************************
 * f3d_uart.c
 *
 * contains the initialization basic i/o functions for UART
 *
 * Author: Bo Fang (bofang)
 *         Omar White (omawhite)
 * Date Created: 02/11/2016
 * Last Modified by: Bo Fang (bofang)
 * Date Last Modified: 02/11/2016
 * Assignment: Lab5
 * Part of: CS-Spring-2016
 */
/* Code: */

#include <stm32f30x.h>
#include <f3d_uart.h>
//the initialization function to call
void f3d_uart_init(void) {
  //Define a structure to handle the I/O initialization.
  GPIO_InitTypeDef GPIO_InitStructure;
  //Enable Clock for GPIOC
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  //TX Pin Initialization
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
  //RX Pin Initialization
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
  //Alternate Function Configuration
  GPIO_PinAFConfig(GPIOC,4,GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC,5,GPIO_AF_7);

  //Define a structure to hold the UART initialization.
  USART_InitTypeDef USART_InitStructure;
  //UART1 Clock Enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  //UART1 Configuration
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1 ,&USART_InitStructure);
  USART_Cmd(USART1 , ENABLE);

}
//sends a character
int putchar(int c) {
  while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == (uint16_t)RESET);
  USART_SendData(USART1, c);

  return 0;
} 
//gets a character
int getchar(void) {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == (uint16_t)RESET);
  int c = USART_ReceiveData(USART1);

  return c;
}
//sends a string
void putstring(char *s) {
  while(*s){
    putchar(*s);
    s = s + 1;
  }
}



/* f3d_uart.c ends here */
