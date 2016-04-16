#include<stdint.h>
#define TANK_width 16
#define TANK_height 16

typedef struct onetank {
  uint8_t x;
  uint8_t y;
  uint8_t head;
  uint8_t enemy;
} Tank;
void initTank(Tank *,uint8_t,uint8_t,uint8_t);
void drawTank(Tank *);
