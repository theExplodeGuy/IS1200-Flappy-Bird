// main.c

#include "init.h"
#include "draw.h"
#include "update.h"


volatile unsigned char *VGA_FRONT = (volatile unsigned char*) 0x08000000;
volatile unsigned char *VGA_BACK = (volatile unsigned char*) 0x08000000 + 0x12c00;

volatile int *VGA_CTRL = (volatile int*) 0x04000100;

int get_btn(void){
  volatile int *BTN_ADDRESS = (volatile int *) 0x040000d0;
  return (*BTN_ADDRESS % 10);
}

void handle_interrupt(int cause){
  volatile unsigned char *next = (VGA_FRONT == (volatile unsigned char *)0x08000000)
                                       ? (volatile unsigned char *)(0x08000000 + 0x012c00)
                                       : (volatile unsigned char *)0x08000000;

  if(cause == 16){
    update_bg();
    draw_bg(next);
    update_pipes();
    
    if(get_btn())
      update_bird_btn();
    else
      update_bird();

    draw_all_pipes(next);
    draw_bird(next);

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
