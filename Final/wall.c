#include<stdint.h>
#include<f3d_lcd_sd.h>
#include"screen.h"

#include"wall.h"
#include"tank.h"
#include"info.h"

uint16_t wallimg[16][16] = {
{0x6916,0x70d9,0x6898,0x6879,0x899d,0x68b9,0x6899,0x68b9,0x6058,0x6898,0x70d9,0x68b9,0x813c,0x70ba,0x6079,0x68f8},
{0x7257,0x40b4,0x38d3,0x30f3,0x3893,0x3053,0x3894,0x3053,0x61d9,0x40b5,0x40b4,0x40d5,0x30b4,0x30b4,0x3074,0x3893},
{0x8aba,0x4074,0x48f6,0x40b5,0x48d6,0x48d5,0x48d5,0x40b5,0x721a,0x40b5,0x48d5,0x5116,0x40b5,0x40d6,0x48b6,0x48b5},
{0x8259,0x5076,0x58b7,0x5096,0x5076,0x5076,0x5056,0x5036,0x717a,0x5076,0x5877,0x60b8,0x5077,0x5077,0x5057,0x5096},
{0x71b7,0x60b7,0x5856,0x5857,0x5016,0x6077,0x5876,0x60d8,0x7139,0x60d8,0x5856,0x5857,0x5857,0x5057,0x5057,0x6117},
{0x40d1,0x4094,0x40b5,0x3874,0x71da,0x4095,0x4094,0x48f5,0x40b4,0x4094,0x4094,0x4074,0x5977,0x48f6,0x3875,0x48d4},
{0x4112,0x40b4,0x40f5,0x40f5,0x7a9c,0x4094,0x4916,0x4115,0x40d5,0x40f5,0x40f5,0x40b5,0x59b8,0x40f6,0x40b5,0x4915},
{0x50f3,0x5075,0x5056,0x5036,0x799c,0x5036,0x5057,0x5077,0x5036,0x5057,0x5037,0x5016,0x60b8,0x4816,0x5037,0x5095},
{0x5092,0x6097,0x5857,0x5817,0x817c,0x5017,0x5838,0x5817,0x4816,0x5817,0x6078,0x5858,0x68ba,0x6058,0x5017,0x5876},
{0x7a98,0x50f6,0x48d5,0x48d5,0x5116,0x48b6,0x50f7,0x4896,0x69ba,0x48d6,0x48d6,0x5117,0x48f6,0x48d6,0x48b6,0x50f5},
{0x82f9,0x40b4,0x4115,0x40f5,0x40f5,0x4915,0x40d5,0x40b5,0x6a1a,0x40d5,0x4915,0x4956,0x4115,0x4116,0x40f6,0x48f4},
{0x8279,0x5096,0x5055,0x5076,0x5096,0x58b6,0x5076,0x5056,0x715a,0x5056,0x5896,0x58d7,0x5097,0x5097,0x5077,0x50b5},
{0x7997,0x5836,0x6017,0x5817,0x5816,0x6037,0x5816,0x6078,0x70fa,0x6057,0x5816,0x6017,0x5817,0x5017,0x5016,0x6097},
{0x69f6,0x5937,0x6178,0x5957,0x823c,0x6138,0x6138,0x6199,0x6198,0x6178,0x6158,0x58f7,0x71da,0x6139,0x58f8,0x6178},
{0x4111,0x4114,0x4134,0x3934,0x7abc,0x3894,0x40f5,0x40f5,0x4115,0x38f4,0x40f5,0x40b5,0x5998,0x40d5,0x3894,0x40d4},
{0x50f3,0x58d6,0x4895,0x50b6,0x79db,0x4835,0x5056,0x5076,0x58b7,0x5076,0x5076,0x5076,0x58f8,0x4856,0x5076,0x50b5}
};
uint8_t map[10][8] = {
  {0,0,1,0,0,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,1,0,0,0,0,1,0},
  {0,1,1,0,0,1,1,0},
  {0,1,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};
void drawWall(uint8_t x, uint8_t y) {
  uint16_t buf[CELL*CELL];
  int i;
  f3d_lcd_setAddrWindow(x,y,x+CELL-1,y+CELL-1,0x6);
  for(i=0;i<CELL*CELL;i++)
    buf[i]=wallimg[CELL-1-i/CELL][i%CELL];
  f3d_lcd_pushColor(buf,CELL*CELL);
}
extern Tank user;
void drawMap(void) {
  int i,j;
  for(i=0;i<10;i++)
    for(j=0;j<8;j++) {
      if(map[i][j])
	drawWall(j*CELL,i*CELL);
    }
}