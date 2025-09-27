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

