#include "c335sim.h"
#include "screen.h"
#include "tank.h"
#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>

Tank user;
Tank tanks[3];
uint8_t lives;
uint8_t positions[3][2] = {
  {0,0},
  {48,0},
  {112,0}
};

void event_loop(void) {
  static int user_v_move = 0;
  static int user_h_move = 0;
  SDL_Event event;
  SDL_PollEvent(&event);
  switch(event.type) {
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      user_v_move = 0;
      break;
    case SDLK_DOWN:
      user_v_move = 0;
      break;
    case SDLK_LEFT:
      user_h_move = 0;
      break;
    case SDLK_RIGHT:
      user_h_move = 0;
      break;
    default:
      break;
    }
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      user_v_move = -TANK_V_INC;
      user_h_move = 0;
      break;
    case SDLK_DOWN:
      user_v_move = TANK_V_INC;
      user_h_move = 0;
      break;
    case SDLK_LEFT:
      user_h_move = -TANK_H_INC;
      user_v_move = 0;
      break;
    case SDLK_RIGHT:
      user_h_move = TANK_H_INC;
      user_v_move = 0;
      break;
    case SDLK_q:
      exit(0);
      break;
    default:
      break;
    }
    break;
  }
  if (user_h_move||user_v_move) {
    moveTank(&user, user_h_move, user_v_move, BLACK);
  }
}

void tank_game(void) {

  f3d_lcd_drawString(25,150,"hit q to quit",WHITE,BLACK);
  //0b  0  0  0  1
  //   -h +v +h -v
  static int tank_move0 = 0b0100;
  static int tank_move1 = 0b0100;
  static int tank_move2 = 0b0100;
  if(ENEMY0) {
    if(tanks[0].x%16==0 && tanks[0].y%16==0 && ACTION)
      tank_move0 = 1<<(rand()%4);
    if(moveTank(tanks, tank_h(0), tank_v(0), BLACK)) {
      if(tanks[0].head%2==0) tank_move0 ^= 0b0101;
      else tank_move0 ^= 0b1010;
    }
  } else {
    initTank(tanks,positions[0][0],positions[0][1],1);
    drawTank(tanks);
    lives|=1;
  }
  if(ENEMY1) {
    //if it is in a cell, it randomly change direction
    if(tanks[1].x%16==0 && tanks[1].y%16==0 && ACTION)
      tank_move1 = 1<<(rand()%4);
    //if it runs and hits other tanks, it go back
    if(moveTank(tanks+1, tank_h(1), tank_v(1), BLACK)) {
      if(tanks[1].head%2==0) tank_move1 ^= 0b0101;
      else tank_move1 ^= 0b1010;
    }
  } else {
    initTank(tanks+1,positions[1][0],positions[1][1],1);
    drawTank(tanks+1);
    lives|=2;
  }
  if(ENEMY2) {
    if(tanks[2].x%16==0 && tanks[2].y%16==0 && ACTION)
      tank_move2 = 1<<(rand()%4);
    if(moveTank(tanks+2, tank_h(2), tank_v(2), BLACK)) {
      if(tanks[2].head%2==0) tank_move2 ^= 0b0101;
      else tank_move2 ^= 0b1010;
    }
  } else {
    initTank(tanks+2,positions[2][0],positions[2][1],1);
    drawTank(tanks+2);
    lives|=4;
  }
  event_loop();
}

int pressed() {
  SDL_Event event;
  uint8_t count=0;
  while(1) {
    count++;
    while(event.type!=SDL_KEYDOWN) SDL_PollEvent(&event);
    while(event.type!=SDL_KEYUP) SDL_PollEvent(&event);
    if(event.key.keysym.sym==SDLK_s) return count;
  }
}

int c335_main( int argc, char *argv[] ) {

  //f3d_lcd_fillScreen(BLACK);

  f3d_lcd_drawString(25,150,"hit s toStart",WHITE,BLACK);
  //use time of user's delay as random seed
  srand(pressed());

  //f3d_lcd_fillScreen(BLACK);
  initTank(&user,USER_x,USER_y,0);
  user.head=0;
  drawTank(&user);
  drawMap();
  lives=0;

  while (1) {
    tank_game();
    Delay(EVENT_LOOP_TIME);
  }
}
