// main.c
// Authored by: Panayiotis Charalambous. Marios Stavrou

#include "init.h"
#include "draw.h"
#include "update.h"
#include "colissionDetector.h"
#include "score.h"
#include "helpers.h"


volatile unsigned char *VGA_FRONT = (volatile unsigned char*) 0x08000000;
volatile unsigned char *VGA_BACK = (volatile unsigned char*) 0x08000000 + 0x12c00;

volatile int *VGA_CTRL = (volatile int*) 0x04000100;

void handle_interrupt(int cause){
  volatile unsigned short *STATUS_TO = (volatile unsigned short *)0x04000020;
  volatile unsigned short *CONTROL = (volatile unsigned short *)0x04000024;


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
      *CONTROL = 0x8;
      read_registers();
    }

    live_score();

    update_bird();

    *(VGA_CTRL + 1) = (unsigned int) next;
    // Request swap (value doesn't matter; write to trigger)
    *(VGA_CTRL + 0) = 0;
    VGA_FRONT = next;
  }

  else if (cause == 17){
    volatile unsigned short *SW_EDGE = (volatile unsigned short *)0x0400001c;
    *SW_EDGE = 0x4;
    init();  
    clear_registers();
  }

  else if (cause == 18){
    volatile unsigned int *BTN_ADDRESS_EDGE = (volatile unsigned int *) 0x040000dc;
    *BTN_ADDRESS_EDGE = 0x1;

    volatile int *BTN_ADDRESS = (volatile int *) 0x040000d0;
    if(*BTN_ADDRESS % 10)
      update_bird_btn();
  }
}

int main ( void ) {
  init_start_screen();
  draw_starting_screen(VGA_FRONT);
}





