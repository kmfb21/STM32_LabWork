/* machine.h --- 
 * 
 * Filename: machine.h
 * Description: HW4 head file
 * Author: Bryce Himebaugh
 * Maintainer: Bo Fang(bofang)
 * Created: Thu Oct  8 12:40:51 2015
 * Last-Updated: 03/23/2016
 *           By: Bo Fang(bofang)
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Copyright (c) 2015 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

extern uint32_t reg[16];
extern uint32_t psr;

void adds(int, int);
void subs(int, int);
void ands(int, int);
void bics(int, int);
void lsls(int, int);
void asrs(int, int);

/* machine.h ends here */
