//cell size
#define CELL 16

//speed and time
#define TANK_V_INC 4
#define TANK_H_INC 4
#define BULL_V 8
#define BULL_DIM 2
#define EVENT_LOOP_TIME 0

//born place
#define USER_x 56
#define USER_y 128

//is enemy alive
#define ENEMY0 lives&1
#define ENEMY1 lives>>1&1
#define ENEMY2 lives>>2&1
//and have they used their bullets
#define BULL0 lives>>3&1
#define BULL1 lives>>4&1
#define BULL2 lives>>5&1
#define BULLU lives>>6&1

//delta x and y move based on 4 bits random number
#define tank_h(n) (tank_move##n>>1&1)-(tank_move##n>>3&1)
#define tank_v(n) (tank_move##n>>2&1)-(tank_move##n&1)

//probablity of AI changes his move
#define ACTION rand()%3==0
