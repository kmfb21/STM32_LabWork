/* f3d_uart.h --- 
 * 
 * Filename: f3d_uart.h
 * Description: Head files of drivers of TX and RX 
 * Author: Bryce Himebaugh
 * Maintainer: Bo Fang (bofang) Omar White (omawhite)
 * Created: Thu Sep 26 07:05:43 2013
 * Last-Updated: Thu Feb 11 23:10:14 2016
 *           By: Bo Fang (bofang)
 *     Update #: 0
 * Keywords: Add comment of head
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

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

void f3d_uart_init(void);
int putchar(int);
int getchar(void);
void putstring(char *);

/* f3d_uart.h ends here */
