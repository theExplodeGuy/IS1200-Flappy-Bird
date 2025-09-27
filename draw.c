#include "init.h"

void draw_bird(volatile unsigned char *buf){
  const unsigned char *bird_spite = (const unsigned char*) 0x02025800;

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++){
      if(bird.x_pos < SCREEN_X && bird.y_pos < SCREEN_Y && bird_spite[i*32+j] != 255)
        buf[(bird.y_pos + i)* SCREEN_X + (bird.x_pos + j)] = bird_spite[i*32+j];
    }
  }
}

void draw_pipe(int left_most, int gap_y, volatile unsigned char *buf){
  // top part
  for(int y = 0; y < (gap_y - PIPE_GAP/2); y++){
    for(int x = left_most; x < left_most + PIPE_WIDTH; x++){
      // if in screen
      if(x >= 0 && x < SCREEN_X){
        buf[y*SCREEN_X + x] = PIPE_GREEN;
      }
    }
  }

  // bottom part
  for(int y = (gap_y + PIPE_GAP/2); y < SCREEN_Y; y++){
    for(int x = left_most; x < left_most + PIPE_WIDTH; x++){
      // if in screen
      if(x >= 0 && x < SCREEN_X){
        buf[y*SCREEN_X + x] = PIPE_GREEN;
      }
    }
  }
}

void draw_all_pipes(volatile unsigned char *buf){
  for (int i = 0; i < PIPES; i++){
    draw_pipe(pipes[i].left_edge, pipes[i].gap_y, buf);
  }
}