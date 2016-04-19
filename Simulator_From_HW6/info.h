//cell size
#define CELL 16

//speed and time
#define TANK_V_INC 1
#define TANK_H_INC 1
#define BULL_V 3
#define EVENT_LOOP_TIME 20

//born place
#define USER_x 56
#define USER_y 128

//is enemy alive
#define ENEMY0 lives&1
#define ENEMY1 lives>>1&1
#define ENEMY2 lives>>2&1

//delta x and y move based on 4 bits random number
#define tank_h(n) (tank_move##n>>1&1)-(tank_move##n>>3&1)
#define tank_v(n) (tank_move##n>>2&1)-(tank_move##n&1)

//probablity of AI changes his move
#define ACTION rand()%3==0
