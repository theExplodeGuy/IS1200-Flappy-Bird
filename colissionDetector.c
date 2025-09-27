#include "colissionDetector.h"
#include "init.h"
#include "draw.h"



int collision_bound(){
    if (bird.y_pos+20 < 0 || bird.y_pos+15 > SCREEN_Y) {
      bird.x_pos = -1000000000;
      bird.y_pos = -1000000000;  
      return 1;
    }
    return 0;
}

int collision_pipe(){
  for (int i = 0; i < PIPES; i++) {
    int pipe_left = pipes[i].left_edge;
    int pipe_right = pipes[i].left_edge + PIPE_WIDTH;
    int gap_top = pipes[i].gap_y - PIPE_GAP / 2;
    int gap_bottom = pipes[i].gap_y + PIPE_GAP / 2;

    if (bird.x_pos +20 >= pipe_left && bird.x_pos <= pipe_right) {
      if (bird.y_pos + 12 < gap_top || bird.y_pos + 22 > gap_bottom) {
        bird.x_pos = -1000000000;
        bird.y_pos = -1000000000; 
        return 1;
      }
    }
  }
  return 0;
}

