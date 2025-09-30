#include "score.h"
#include "init.h"
#include "draw.h"


/* Your code goes into main as well as any needed functions. */
void live_score() {

    for (int i = 0; i < PIPES; i++) {
    int pipe_x_center = pipes[i].left_edge + PIPE_WIDTH/2;

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