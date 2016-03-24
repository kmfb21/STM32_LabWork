/* flags.h --- 
 * 
 * Filename: flags.h
 * Description: HW4 head file
 * Author: Bryce Himebaugh
 * Maintainer: Bo Fang(bofang)
 * Created: Fri Oct  9 13:40:16 2015
 * Last-Updated: 03/23/2016
 *           By: Bo Fang(bofang)
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

#define CLEAR_Z psr &= ~(0x40000000) 
#define SET_Z psr |= 0x40000000

#define CLEAR_N psr &= ~(0x80000000)
#define SET_N psr |= 0x80000000

#define CLEAR_C psr &= ~(0x20000000)
#define SET_C psr |= 0x20000000

#define CLEAR_V psr &= ~(0x10000000)
#define SET_V psr |= 0x10000000

/* flags.h ends here */
