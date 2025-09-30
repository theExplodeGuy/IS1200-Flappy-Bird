#include "score.h"
#include "init.h"
#include "draw.h"

void set_displays(int display_number, int value){
  volatile int *arr[6] = {
    (volatile int *)0x04000050,
    (volatile int *)0x04000060,
    (volatile int *)0x04000070,
    (volatile int *)0x04000080,
    (volatile int *)0x04000090,
    (volatile int *)0x040000a0
};

  int volatile *display_address = arr[display_number-1];
  int display_values[10] = {
    0xc0,
    0xf9,
    0xa4, 
    0xb0, 
    0x99,
    0x92, 
    0x82, 
    0xf8,
    0x80, 
    0x90
  };
    *display_address = display_values[value];
}


/* Your code goes into main as well as any needed functions. */
void live_score() {

    for (int i = 0; i < PIPES; i++) {
    int pipe_x_center = pipes[i].left_edge + PIPE_WIDTH/2;
    int pipe_y_center = pipes[i].gap_y;

    if (pipe_x_center >= bird.x_pos -10 && pipe_x_center <= bird.x_pos +10) {
        score = score + 10;
        set_displays(1, score%10);
        set_displays(2, (score/10%10));
        set_displays(3, (score/100%10));
        set_displays(4, (score/1000%10));
        set_displays(5, (score/10000%10));
        set_displays(6, (score/100000%10));
      
    }
  }
}