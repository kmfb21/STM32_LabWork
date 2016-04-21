#include<f3d_lcd_sd.h>
#include<stdint.h>
#include"screen.h"

#include"wall.h"
#include"tank.h"
#include"info.h"

uint16_t tankimg[16][16] = {
{0x3107,0x418a,0x28c6,0x20c5,0x1,0x2,0x1,0x2,0x1,0x2,0x1,0x2,0x1004,0x3088,0x3087,0x2024},
{0xb4d7,0xcd3a,0x8b53,0x6a6f,0x804,0x20a7,0x1805,0x3048,0x2007,0x2828,0x1807,0x1807,0x48cc,0x8ab4,0x9314,0x7290},
{0xcd5b,0xdd3c,0xccbb,0xabd7,0x2,0x59ae,0x7a32,0x6970,0x6130,0x8255,0x6992,0x2009,0x380c,0x9ab8,0xbbfb,0x9335},
{0x592c,0x79d1,0x9ab5,0xc41b,0x50cd,0xb3b9,0xcc1c,0xaaf9,0xa299,0x9a79,0x9258,0x7175,0x5831,0x6072,0x6912,0x6150},
{0xd4fb,0xcbfa,0xb2f8,0xecdf,0xc3db,0xe4df,0xcbfe,0x8155,0x6812,0x8917,0xaabd,0x9a1b,0x7096,0x9179,0xaa9b,0x8235},
{0x9af5,0xaab7,0xaa57,0xf4df,0xe47f,0xc3bd,0xc37d,0x8977,0x7054,0x7076,0xa23d,0xaa5e,0x7057,0x7877,0x9199,0x79b4},
{0x8211,0x9a35,0xa237,0xec9f,0xe49f,0xab1b,0xcbbf,0xbafd,0x8938,0x7876,0x99dc,0xa21e,0x7017,0x7016,0x8938,0x6933},
{0xab97,0xbb19,0xb299,0xec9f,0xe4bf,0xab3b,0xc3df,0xc39f,0x99ba,0x80f8,0x99fc,0xa1dd,0x7058,0x80d9,0x99da,0x7174},
{0x488b,0x70f0,0x91f6,0xe49f,0xdcbf,0xab9c,0xcc5f,0xd45f,0xdbff,0xa21c,0xa23d,0xaa5e,0x7038,0x5813,0x6013,0x58b0},
{0xc49a,0xb399,0xb359,0xed5f,0xe57f,0xc49e,0xc45e,0xab7b,0xaafb,0xa2bb,0xaadc,0x8999,0x6834,0x8958,0xaa7b,0x8214},
{0x7a50,0x8292,0xabb7,0xbc3a,0x3049,0xcd1d,0xbc7a,0xccfd,0xb43a,0x8253,0x8234,0x380b,0x582f,0x7933,0x7131,0x69b1},
{0xa3f5,0xb457,0xbcb8,0xa3f6,0x1,0x3088,0x38ea,0xbcfa,0xc51a,0x1004,0x2006,0x803,0x3809,0x9295,0xb3b8,0x7a72},
{0xddfc,0xddfc,0xc539,0xa435,0x2,0x2,0x1,0xb4d8,0xacb7,0x1,0x2,0x1,0x616e,0xa356,0x9b55,0x9b95},
{0x9c54,0x93f3,0x51eb,0x3107,0x1,0x1,0x1,0xc599,0xc5da,0x803,0x1,0x1,0x8af2,0x9333,0x410a,0x49ac},
{0x0,0x802,0x0,0x1,0x1,0x0,0x0,0xbdb8,0xbdd8,0x0,0x802,0x1,0x2,0x1,0x1,0x1},
{0x801,0x0,0x0,0x0,0x1,0x0,0x1082,0xbe18,0xce99,0x20,0x21,0x1,0x0,0x2,0x1024,0x1}
};

void initTank(Tank *t,uint8_t x,uint8_t y,uint8_t enemy) {
  t->x=x;
  t->y=y;
  t->enemy=enemy;
  if(enemy) t->head=2;
  else t->head=0;
}
uint16_t changecolor(uint16_t color,int enemy) {
  if(enemy) return color;
  return color > 0x400a ? (0-color):0;
}
void drawTank(Tank *t) {
  uint16_t buf[CELL*CELL];
  int i;
  f3d_lcd_setAddrWindow(t->x, t->y, t->x+CELL-1, t->y+CELL-1, 0x6);
  switch(t->head) {
  case 0:
    for (i = 0; i < CELL*CELL; i++)
      buf[i] = changecolor(tankimg[CELL-1-i/CELL][i%CELL],t->enemy);
    break;
  case 1:
    for (i = 0; i < CELL*CELL; i++)
      buf[i] = changecolor(tankimg[i%CELL][i/CELL],t->enemy);
    break;
  case 2:
    for (i = 0; i < CELL*CELL; i++) {
      buf[i] = changecolor(tankimg[i/CELL][i%CELL],t->enemy);
    }
    break;
  case 3:
    for (i = 0; i < CELL*CELL; i++) {
      buf[i] = changecolor(tankimg[CELL-1-i%CELL][i/CELL],t->enemy);
    }
    break;
  default:
    break;
  }
  f3d_lcd_pushColor(buf,CELL*CELL);
}
void eraseTank(Tank *t,uint16_t background_color) {
  f3d_lcd_drawRectangle(t->x,t->y,CELL,CELL,background_color);
}

extern uint8_t map[10][8];
extern Tank user;
extern Tank tanks[3];
int hit(int xtemp,int ytemp, Tank *t) {
  return ((t->x)<=xtemp && xtemp<(t->x+CELL) && (t->y)<=ytemp && ytemp<(t->y+CELL));
}
int collision(int xtemp,int ytemp, Tank *t) {
  if(((t->x)<=xtemp && xtemp<(t->x+CELL) && (t->y)<=ytemp && ytemp<(t->y+CELL))
     ||((t->x)<=(xtemp+CELL-1) && (xtemp+CELL-1)<(t->x+CELL) && (t->y)<=(ytemp+CELL-1) && (ytemp+CELL-1)<(t->y+CELL))
     ||((t->x)<=(xtemp+CELL-1) && (xtemp+CELL-1)<(t->x+CELL) && (t->y)<=ytemp && ytemp<(t->y+CELL))
     ||((t->x)<=xtemp && xtemp<(t->x+CELL) && (t->y)<=(ytemp+CELL-1) && (ytemp+CELL-1)<(t->y+CELL)))
    return 1;
  return 0;
}
int moveTank(Tank *t, int8_t delta_x, int8_t delta_y, uint16_t background_color) {
  int xtemp;
  int ytemp;
  eraseTank(t,background_color);

  // update heading
  if(delta_y<0) t->head=0;
  if(delta_x>0) t->head=1;
  if(delta_y>0) t->head=2;
  if(delta_x<0) t->head=3;

  // update x,y postion based on deltas, 
  xtemp = (int) (t->x + delta_x);
  ytemp = (int) (t->y + delta_y);
  //tanks collision
  if((t!=&user && collision(xtemp,ytemp,&user))||
     (t!=tanks && collision(xtemp,ytemp,tanks))||
     (t!=tanks+1 && collision(xtemp,ytemp,tanks+1))||
     (t!=tanks+2 && collision(xtemp,ytemp,tanks+2))) {
    drawTank(t);
    return 1;
  }
  //wall hit
  int leftcol = xtemp/CELL;
  int uprow = ytemp/CELL;
  int rightcol = (xtemp+CELL-1)/CELL;
  int downrow = (ytemp+CELL-1)/CELL;
  if(delta_x<0 && (map[uprow][leftcol] || map[downrow][leftcol]))
    xtemp = rightcol*CELL;
  if(delta_x>0 && (map[uprow][rightcol] || map[downrow][rightcol]))
    xtemp = leftcol*CELL;
  if(delta_y<0 && (map[uprow][leftcol] || map[uprow][rightcol]))
    ytemp = downrow*CELL;
  if(delta_y>0 && (map[downrow][leftcol] || map[downrow][rightcol]))
    ytemp = uprow*CELL;
  //bound hit
  if (xtemp < 0)
    xtemp = 0;
  if (xtemp > (ST7735_width - CELL)) 
    xtemp = ST7735_width - CELL;
  if (ytemp < 0) 
    ytemp = 0;
  if (ytemp > (ST7735_height - CELL)) 
    ytemp = ST7735_height - CELL;

  t->x = (uint8_t) xtemp;
  t->y = (uint8_t) ytemp;

  // draw the new tank
  drawTank(t);
  return 0;
}

void initBull(Bull *b,Tank *t) {
  int x,y;
  x=t->x+7;
  y=t->y+7;
  b->head=t->head;
  b->enemy=t->enemy;
  switch(b->head) {
  case 0:
    y-=7;
    break;
  case 1:
    x+=7;
    break;
  case 2:
    y+=7;
    break;
  case 3:
    x-=7;
    break;
  default:
    break;
  }
  uint16_t bullcolor;
  if(b->enemy) bullcolor=RED;
  else bullcolor=YELLOW;
  initRect(&(b->ins),x,y,BULL_DIM,BULL_DIM,bullcolor);
}

int moveBull(Bull *b,uint16_t background) {
  int x=0,y=0,i=0;
  switch(b->head) {
  case 0:
    y=-BULL_V;
    break;
  case 1:
    x=BULL_V;
    break;
  case 2:
    y=BULL_V;
    break;
  case 3:
    x=-BULL_V;
    break;
  default:
    break;
  }
  int xtemp=b->ins.pos_x+x;
  int ytemp=b->ins.pos_y+y;
  if(b->enemy) {
    //enemy hits user
    if(hit(xtemp,ytemp,&user)) return 2;
  } else {
    //user hits enemy
    for(i=0;i<3;i++)
      if(hit(xtemp,ytemp,tanks+i)) return i+10;
  }
  //bullet hits walls
  if(map[ytemp/CELL][xtemp/CELL]||
     map[(ytemp+1)/CELL][(xtemp+1)/CELL]||
     map[ytemp/CELL][(xtemp+1)/CELL]||
     map[(ytemp+1)/CELL][xtemp/CELL]) return 1;
  //bullet moves and hits boundary 
  if(moveRect(&(b->ins),x,y,BLACK)) return 1;
  return 0;
}
