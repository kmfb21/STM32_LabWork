/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
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
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include "bmp.h"
struct bmpfile_magic magic; 
struct bmpfile_header header; 
BITMAPINFOHEADER info;
struct bmppixel pix;
void drawpic(char* pic);

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;		/* File system object */
FIL Fil;		/* File object */
BYTE Buff[128];		/* File read buffer */

int main(void) { 
  char footer[20];
  int count=0;
  int i;

  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  f3d_lcd_init();
  f3d_delay_init();
  f3d_rtc_init();

  f_mount(0, &Fatfs);		/* Register volume work area (never fails) */


drawpic("out.bmp");

  printf("\nOpen an existing file (message.txt).\n");
  rc = f_open(&Fil, "MESSAGE.TXT", FA_READ);
  if (rc) die(rc);
 
  printf("\nType the file content.\n");
  for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	/* Read a chunk of file */
    if (rc || !br) break;			/* Error or end of file */
    for (i = 0; i < br; i++)		        /* Type the data */
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
    rc = f_readdir(&dir, &fno);		/* Read a directory item */
    if (rc || !fno.fname[0]) break;	/* Error or end of dir */
    if (fno.fattrib & AM_DIR)
      printf("   <dir>  %s\n", fno.fname);
    else
      printf("%8lu  %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
  
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);

  while (1);
}
void drawpic(char* pic) {
  FRESULT rc;
  UINT br;
  //***************************
  //lab work here
  f3d_lcd_fillScreen(WHITE);
  printf("\nOpen an BMP file.\n");
  rc = f_open(&Fil, pic, FA_READ);
  if (rc) die(rc);
  printf("\nReading the picture.\n");
  rc = f_read(&Fil, &magic, sizeof(magic), &br);
  printf("Magic %c%c\n", magic.magic[0], magic.magic[1]); 
  rc = f_read(&Fil, &header, sizeof(header), &br);
  printf("file size %d offset %d\n", header.filesz, header.bmp_offset);
  rc = f_read(&Fil, &info, sizeof(info), &br);
  printf("Width %d Height %d, bitspp %d\n", info.width, info.height, info.bitspp);
 
  //uint16_t color;
  uint8_t x = 0, y = 0;
  //uint16_t* matrix[info.height];
  uint16_t* matrix = (uint16_t*)malloc(sizeof(uint16_t) * info.height * info.width);
  int count = 0;
  //uint16_t** matrix = (uint16_t **)malloc(sizeof(*matrix) * info.height);
  for(y=0;y<info.height;y++) {
    //matrix[y] = (uint16_t *)malloc(sizeof(**matrix) * info.width);
    for(x=0;x<info.width;x++) {
      //printf("x: %d y: %d\n",x,y);
      rc = f_read(&Fil, &pix, sizeof(pix), &br);
      matrix[count++] = ((pix.r >> 3) << 11) | ((pix.g >> 2) << 5) | (pix.b >> 3);
    }
    //matrix[y][x] = '\0';
  }
  printf("read Done\n");
  //uint16_t colors[ST7735_width];
 
  int i,j;
  count = 0;
  for(j=0;j<info.height;j++) {
    //for(i=0;i<info.width;j++) {
    //  colors[i] = matrix[j];
    //}
    printf("j: %d\n",j);
    //f3d_lcd_pushColor(matrix[j],info.width);
    for(i=0;i<info.width;i++) f3d_lcd_drawPixel(i,j,matrix[count++]);
    //free(matrix[j]);
  }
  free(matrix);
  

  if (rc) die(rc);
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);

  //***************************
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
