// main.c

#include "init.h"
#include "draw.h"
#include "update.h"


volatile unsigned char *VGA_FRONT = (volatile unsigned char*) 0x08000000;
volatile unsigned char *VGA_BACK = (volatile unsigned char*) 0x08000000 + 0x12c00;

volatile int *VGA_CTRL = (volatile int*) 0x04000100;



int scroll_x = 0;
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

void update_bg(){
  scroll_x = (scroll_x + 1) % 320;
}

void handle_interrupt(int cause){
  if(cause == 16){
    volatile unsigned char *next = (VGA_FRONT == (volatile unsigned char *)0x08000000)
                                       ? (volatile unsigned char *)(0x08000000 + 0x012c00)
                                       : (volatile unsigned char *)0x08000000;

    
    update_bg();
    draw_bg(next);
    update_pipes();
    update_bird();
    draw_all_pipes(next);
    draw_bird(next);

    *(VGA_CTRL + 1) = (unsigned int) next;
    // Request swap (value doesn't matter; write to trigger)
    *(VGA_CTRL + 0) = 0;
    VGA_FRONT = next;
  }
}



// Your code goes into main as well as any needed functions.
int main ( void ) {
  init();
  
  while(1){
    
    for (int i=0; i<1000000; i++) {
      asm volatile ("nop");
    }

  }

}
