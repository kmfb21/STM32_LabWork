#include<stdint.h>

typedef struct onetank {
  uint8_t x;
  uint8_t y;
  uint8_t head;
  uint8_t enemy;
} Tank;
void initTank(Tank *,uint8_t,uint8_t,uint8_t);
void drawTank(Tank *);
void eraseTank(Tank *,uint16_t);
void moveTank(Tank *,int8_t,int8_t,uint16_t);
