// main.c

#include "init.h"
#include "draw.h"
#include "update.h"
#include "colissionDetector.h"


volatile unsigned char *VGA_FRONT = (volatile unsigned char*) 0x08000000;
volatile unsigned char *VGA_BACK = (volatile unsigned char*) 0x08000000 + 0x12c00;

volatile int *VGA_CTRL = (volatile int*) 0x04000100;

int get_btn(void){
  volatile int *BTN_ADDRESS = (volatile int *) 0x040000d0;
  return (*BTN_ADDRESS % 10);
}

void handle_interrupt(int cause){
  volatile unsigned short *STATUS_TO = (volatile unsigned short *)0x04000020;

  volatile unsigned char *next = (VGA_FRONT == (volatile unsigned char *)0x08000000)
                                       ? (volatile unsigned char *)(0x08000000 + 0x012c00)
                                       : (volatile unsigned char *)0x08000000;

  if(cause == 16){
    *STATUS_TO = 0x0;
    update_bg();      
    update_pipes();
      

    draw_bg(next);
    draw_all_pipes(next);
    draw_bird(next);


    if(collision_bound() || collision_pipe()){
      draw_gameover(next);
      *STATUS_TO = 0x1;
    }

    if(get_btn())
      update_bird_btn();
    else
      update_bird();

    *(VGA_CTRL + 1) = (unsigned int) next;
    // Request swap (value doesn't matter; write to trigger)
    *(VGA_CTRL + 0) = 0;
    VGA_FRONT = next;
  }

  else if (cause == 17){
    update_bird_btn();
    volatile unsigned short *SW_EDGE = (volatile unsigned short *)0x0400001c;
    *SW_EDGE = 0x4;
  }

}




// Your code goes into main as well as any needed functions.
int main ( void ) {
  init();
  
  while(1){
    
    get_btn();

  }

}
