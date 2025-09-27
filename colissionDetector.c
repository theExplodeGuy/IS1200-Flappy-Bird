#include "colissionDetector.h"
#include "init.h"
#include "draw.h"



void colissionDetector(volatile unsigned char *buf){
    if (bird.y_pos <= 0 || bird.y_pos + 32 >= SCREEN_Y) {
        draw_gameover(buf);
        return;
    }

    for (int i = 0; i < PIPES; i++) {
    int pipe_left = pipes[i].left_edge;
    int pipe_right = pipes[i].left_edge + PIPE_WIDTH;
    int gap_top = pipes[i].gap_y - PIPE_GAP / 2;
    int gap_bottom = pipes[i].gap_y + PIPE_GAP / 2;

    if (bird.x_pos + 32 >= pipe_left && bird.x_pos <= pipe_right) {
      if (bird.y_pos < gap_top || bird.y_pos + 32 > gap_bottom) {
        draw_gameover(buf);
        return;
      }
    }
    }
}

