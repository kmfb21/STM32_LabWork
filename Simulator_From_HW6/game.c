#include "c335sim.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>

#define PADDLE_MOVE_INCREMENT 3
#define PADDLE_HEIGHT 25
#define PADDLE_THICKNESS 3
#define BALL_DIM 3
#define EVENT_LOOP_TIME 20

rect_t left_paddle;
rect_t right_paddle;
rect_t ball;

int ball_vx = 1;
int ball_vy = 2;

/*The event loop that handles the key input*/
void event_loop(void) {
  static int paddle_left_move = 0; 
  static int paddle_right_move = 0;
  SDL_Event event;
  SDL_PollEvent(&event);
  switch(event.type) {
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      paddle_right_move = 0;
      break;
    case SDLK_DOWN:
      paddle_right_move = 0;
      break;
    case SDLK_a:
      paddle_left_move = 0;
      break;
    case SDLK_z:
      paddle_left_move = 0;
      break;
    default:
      break;
    }
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      paddle_right_move = -PADDLE_MOVE_INCREMENT;
      break;
    case SDLK_DOWN:
      paddle_right_move = PADDLE_MOVE_INCREMENT;
      break;
    case SDLK_a:
      paddle_left_move = -PADDLE_MOVE_INCREMENT; 
      break;
    case SDLK_z:
      paddle_left_move = PADDLE_MOVE_INCREMENT; 
      break;
    case SDLK_q:
      printf("Q PRESSED - Exit Program\n");
      exit(0);
      break;
    default:
      break;
    }
    break;
  }
  if (paddle_left_move) {
    moveRect(&left_paddle, 0, paddle_left_move, BLACK);
  }
  if (paddle_right_move) {
    moveRect(&right_paddle, 0, paddle_right_move, BLACK);
  }
}

/*Where the collisions are handled*/
void pong_game(void) {
  int collision;

  f3d_lcd_drawString(40,60,"hit q to quit",WHITE,BLACK);
  redrawRect(&left_paddle);
  redrawRect(&right_paddle);
  event_loop();
  collision = moveRect(&ball, ball_vx, ball_vy, BLACK);

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

  if(argc==3) {
    return (0);
  }

  f3d_lcd_fillScreen(BLACK);
  initRect(&left_paddle,0,ST7735_height/2-(PADDLE_HEIGHT/2),PADDLE_THICKNESS,PADDLE_HEIGHT,WHITE);
  initRect(&right_paddle,ST7735_width-PADDLE_THICKNESS,ST7735_height/2-(PADDLE_HEIGHT/2),PADDLE_THICKNESS,PADDLE_HEIGHT,WHITE);
  initRect(&ball,ST7735_width/2-(BALL_DIM/2),ST7735_height/2-(BALL_DIM/2),BALL_DIM,BALL_DIM,WHITE);

  while (1) {
    pong_game();
    Delay(EVENT_LOOP_TIME);
  }
} 
