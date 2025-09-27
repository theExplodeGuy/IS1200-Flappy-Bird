#include "init.h"
#include "update.h"

void update_pipes(){
  for(int i = 0; i < PIPES; i++){
    pipes[i].left_edge -=2;
    if(pipes[i].left_edge + PIPE_WIDTH < 0){
      pipes[i].left_edge = SCREEN_X + 50;
      pipes[i].gap_y = 60 + gaps[rand%15] % (SCREEN_Y - 120);
      rand++;
    }
  }
}

void update_bird(){
  bird.y_pos += 2;
}

void update_bird_btn(){
  bird.y_pos -= 10;
}

void update_bg(){
  scroll_x = (scroll_x + 1) % 320;
}