#include "c335sim.h"
#include "screen.h"
#include "tank.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>

#define TANK_V_INC 1
#define TANK_H_INC 1
#define BULL_V 3
#define EVENT_LOOP_TIME 20

Tank user;

extern uint16_t tankimg[16][16];

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
      //printf("Q PRESSED - Exit Program\n");
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
  int collision;

  //f3d_lcd_drawString(40,60,"hit q to quit",WHITE,BLACK);
  //redrawRect(&left_paddle);
  //redrawRect(&right_paddle);
  event_loop();
  //collision = moveTank(&user, user_vx, user_vy, BLACK);
  /*
  switch (collision) {
  case COLLISION_TOP:
    ball_vy = -ball_vy;
    break;
  case COLLISION_BOTTOM:
    ball_vy = -ball_vy;
    break;
  case COLLISION_LEFT:
    ball_vx = -ball_vx;
    break;
  case COLLISION_RIGHT:
    ball_vx = -ball_vx;
    break;
  }
  */
}

int pressed() {
  SDL_Event event;
  while(1) {
    while(event.type!=SDL_KEYDOWN) SDL_PollEvent(&event);
    while(event.type!=SDL_KEYUP) SDL_PollEvent(&event);
    if(event.key.keysym.sym==SDLK_n) return 'n';
    if(event.key.keysym.sym==SDLK_q) return 'q';
  }
}

int c335_main( int argc, char *argv[] ) {

  //f3d_lcd_fillScreen(BLACK);

  initTank(&user,50,50,0);
  drawTank(&user);
  while (1) {
    tank_game();
    Delay(EVENT_LOOP_TIME);
  }
}
