#include "c335sim.h"
#include "screen.h"
#include "tank.h"
#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>

Tank user;

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
  event_loop();
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
extern uint16_t wallimg[16][16];
int c335_main( int argc, char *argv[] ) {

  //f3d_lcd_fillScreen(BLACK);

  initTank(&user,100,100,0);
  user.head=0;
  drawTank(&user);
  drawMap();
  //pressed();
  //return(0);
  while (1) {
    tank_game();
    Delay(EVENT_LOOP_TIME);
  }
}
