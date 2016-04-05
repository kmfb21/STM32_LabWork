/* main.c --- 
 * 
 * Filename: main.c
 * Description: This is the main file for the SD card reader.  We print the image to the STM LCD then using the accelerometer, rotate the image so it is upright.  We use the nunchuck joystick and buttons to revolve through 3 different images
 * Author: Bo Fang(bofang) and Carson Schwalm(cschwalm)
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 04/04/2016
 *           By: Bo Fang(bofang) and Carson Schwalm(cschwalm)
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
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <math.h>
#include "bmp.h"
struct bmpfile_magic magic; 
struct bmpfile_header header; 
BITMAPINFOHEADER info;
struct bmppixel pix;

void drawpic(char* pic, short dir);

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;                /* File system object */
FIL Fil;                /* File object */
BYTE Buff[128];                /* File read buffer */

int main(void) {
  char footer[20];
  int count=0;
  int i;

  FRESULT rc;                        /* Result code */
  DIR dir;                        /* Directory object */
  FILINFO fno;                        /* File information object */
  UINT bw, br;
  unsigned int retval;
  

  f3d_uart_init();
  f3d_lcd_init();
  f3d_delay_init();
  f3d_rtc_init();
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);

  f_mount(0, &Fatfs);                /* Register volume work area (never fails) */

  printf("\nOpen an existing file (message.txt).\n");
  rc = f_open(&Fil, "MESSAGE.TXT", FA_READ);
  if (rc) die(rc);
 
  printf("\nType the file content.\n");
  for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);        /* Read a chunk of file */
    if (rc || !br) break;                        /* Error or end of file */
    for (i = 0; i < br; i++)                        /* Type the data */
      putchar(Buff[i]);
  }
  if (rc) die(rc);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
  
  printf("\nCreate a new file (hello.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  printf("\nWrite a text data. (Hello world!)\n");
  rc = f_write(&Fil, "Hello world!\r\n", 14, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
  
  printf("\nOpen root directory.\n");
  rc = f_opendir(&dir, "");
  if (rc) die(rc);
  
  printf("\nDirectory listing...\n");
  for (;;) {
    rc = f_readdir(&dir, &fno);                /* Read a directory item */
    if (rc || !fno.fname[0]) break;        /* Error or end of dir */
    if (fno.fattrib & AM_DIR)
      printf("   <dir>  %s\n", fno.fname);
    else
      printf("%8lu  %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
  
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);
  
  //Declare nunchuk struct.  access elements of this to see output
  nunchuk_t n;
  short rotation = 0; //this is the rotating selector.
  short direction = 0; //this is the direction of picture
  drawpic("out.bmp",direction);  

  float acc[3];
  float pitch,roll;
  char *pictures[3];
  pictures[0] = "out.bmp";
  pictures[1] = "1.bmp";
  pictures[2] = "2.bmp";
  while (1) {
    f3d_accel_read(acc);
    pitch = atan(acc[0]/sqrt(acc[1]*acc[1]+acc[2]*acc[2]));
    pitch = pitch * 180 / M_PI;
    roll = atan(acc[1]/sqrt(acc[0]*acc[0]+acc[2]*acc[2]));
    roll *= 180 / M_PI;
    
    f3d_nunchuk_read(&n);
    //Check if button is pushed.  if yes move to different picture
    if(n.c == 1 || n.jx > 140){
      while(n.c == 1 || n.jx > 140) f3d_nunchuk_read(&n);
      rotation++;
      rotation %= 3;
      //printf("%s\n",pictures[rotation]);
      drawpic(pictures[rotation], direction);
    }
    if(n.z == 1 || n.jx < 100){
      while(n.z == 1 || n.jx < 100) f3d_nunchuk_read(&n);
      rotation--;
      rotation = (rotation + 3)%3;
      //printf("%s\n",pictures[rotation]);
      drawpic(pictures[rotation], direction);
    }
    printf("pitch: %.2f roll: %.2f\n",acc[0],acc[1]);
    if(acc[0]>0.6) {
      direction = 0;
      drawpic(pictures[rotation], direction);
      while(acc[0]>0.6) f3d_accel_read(acc);
    }
    if(acc[0]<-0.6) {
      direction = 2;
      drawpic(pictures[rotation], direction);
      while(acc[0]<-0.6) f3d_accel_read(acc);
    }
    if(acc[1]>0.6) {
      direction = 3;
      drawpic(pictures[rotation], direction);
      while(acc[1]>0.6) f3d_accel_read(acc);
    }
    if(acc[1]<-0.6) {
      direction = 1;
      drawpic(pictures[rotation], direction);
      while(acc[1]<-0.6) f3d_accel_read(acc);
    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

void drawpic(char* pic, short dir) {
  FRESULT rc;                        /* Result code */
  UINT bw, br;

  f3d_lcd_fillScreen(WHITE);
  printf("\nOpen an BMP file.\n");
  rc = f_open(&Fil, pic, FA_READ);
  printf("read success\n");
  if (rc) die(rc);
  printf("\nReading the picture.\n");
  
  rc = f_read(&Fil, &magic, sizeof(magic), &br);
  printf("Magic %c%c\n", magic.magic[0], magic.magic[1]); 
  rc = f_read(&Fil, &header, sizeof(header), &br);
  printf("file size %d offset %d\n", header.filesz, header.bmp_offset);
  rc = f_read(&Fil, &info, sizeof(info), &br);
  printf("Width %d Height %d, bitspp %d\n", info.width, info.height, info.bitspp);
  
  int counter,x1,y1,xf,yf,tmp;
  uint16_t color;
  uint8_t x = 0, y = 0;
  uint16_t colors[info.width];
  switch(dir) {
  case 3:
    tmp = info.height;
    info.height = info.width;
    info.width = tmp;
    //Upside From Right
    f3d_lcd_setAddrWindow (0,0,128,160,7);
    info.width = 128;
    info.height = 129;
    for(y=0;y<info.height;y++) {
      for(x=0;x<info.width;x++) {
	rc = f_read(&Fil, &pix, sizeof(pix), &br);
	color = ((pix.r >> 3) << 11) | ((pix.g >> 2) << 5) | (pix.b >> 3);
	colors[x] = color;
      }
      f3d_lcd_pushColor(colors,info.width+1);
    }
    break;
  case 0:
    tmp = info.height;
    info.height = info.width;
    info.width = tmp;
    //botton
    f3d_lcd_setAddrWindow (0,0,128,160,4);
    for(y=0;y<info.height;y++) {
      for(x=0;x<info.width;x++) {
	rc = f_read(&Fil, &pix, sizeof(pix), &br);
	color = ((pix.r >> 3) << 11) | ((pix.g >> 2) << 5) | (pix.b >> 3);
	colors[x] = color;
      }
      f3d_lcd_pushColor(colors,info.width);
    }
    break;
  case 2:
    //up
    f3d_lcd_setAddrWindow (0,0,128,160,0);
    for(y=0;y<info.height;y++) {
      for(x=0;x<info.width;x++) {
	rc = f_read(&Fil, &pix, sizeof(pix), &br);
	color = ((pix.r >> 3) << 11) | ((pix.g >> 2) << 5) | (pix.b >> 3);
	colors[x] = color;
      }
      f3d_lcd_pushColor(colors,info.width);
    }
    break;
  case 1:
    //left
    f3d_lcd_setAddrWindow (0,0,128,160,5);
    info.width = 128;
    info.height = 129;
    for(y=0;y<info.height;y++) {
      for(x=0;x<info.width;x++) {
	rc = f_read(&Fil, &pix, sizeof(pix), &br);
	color = ((pix.r >> 3) << 11) | ((pix.g >> 2) << 5) | (pix.b >> 3);
	colors[x] = color;
      }
      f3d_lcd_pushColor(colors,info.width+1);
    }
    break;
  default:
    break;
  }
  if (rc) die(rc);
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
}


/* main.c ends here */

