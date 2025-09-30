#include "init.h"

extern void enable_interrupt(void);

const int gaps[15] = {
    1012, 2004, 1152, 1972, 304, 1996,
    2021, 2005, 1994, 49, 824, 1453, 5559, 1821, 4897
};

Pipe pipes[PIPES];
Bird bird;

int scroll_x = 0;

int rand = 0;

int score = 0;

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

void init_hexdisplays(){
  for(int i = 1; i <= 6; i++){
    set_displays(i, 0);
  }
}

void init_pipes(){
  for(int i = 0; i < PIPES; i++){
    pipes[i].left_edge = SCREEN_X + i * 100; // space pipes 80pxls apart
    pipes[i].gap_y = 60 + gaps[rand%15] % (SCREEN_Y - 120); // TODO: rand()
    pipes[i].active = 1; // active
    rand++;
  }
}

void init_bird(){
  bird.x_pos = 80;
  bird.y_pos = 100;
  bird.alive = 1;
}

void init(){
  init_pipes();
  init_bird();
  init_hexdisplays();
  
  volatile unsigned short *PERIODL = (volatile unsigned short *) 0x04000028;
  volatile unsigned short *PERIODH = (volatile unsigned short *) 0x0400002c;
  volatile unsigned short *CONTROL = (volatile unsigned short *)0x04000024;


  *PERIODL = 29999999 & 0xffff;
  *PERIODH = 0;

  *CONTROL = 0x7; //also enable interupts

  volatile unsigned short *SW = (volatile unsigned short *)0x04000018;
  volatile unsigned short *SW_EDGE = (volatile unsigned short *)0x0400001c;
  *SW = 0x4;
  *SW_EDGE = 0x4;

  enable_interrupt();
}