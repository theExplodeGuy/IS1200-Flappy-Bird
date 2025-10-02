// Authored by: Marios Stavrou

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

void draw_bg(volatile unsigned char *buf){
  const unsigned char *bg = (const unsigned char*) 0x02000000;

  for (int y = 0; y < SCREEN_Y; y++) {
      for (int x = 0; x < SCREEN_X; x++) {
          // Wrap horizontally using modulo
          int src_x = (x - scroll_x) % 160;
          buf[y * SCREEN_X + x] = bg[(y+1) * 160 + src_x];
      }
  }
}

void draw_gameover(volatile unsigned char *buf){
  const unsigned char *gameover_bg = (const unsigned char*) 0x02025e40;

  for (int y = 0; y < SCREEN_Y; y++) {
      for (int x = 0; x < SCREEN_X; x++) {
          buf[y * SCREEN_X + x] = gameover_bg[(y) * 320 + x];
      }
  }
}

void draw_starting_screen(volatile unsigned char *buf){
  const unsigned char *starting_bg = (const unsigned char*) 0x0203AFC0;

  for (int y = 0; y < SCREEN_Y; y++) {
      for (int x = 0; x < SCREEN_X; x++) {
          buf[y * SCREEN_X + x] = starting_bg[(y) * 320 + x];
      }
  }
}