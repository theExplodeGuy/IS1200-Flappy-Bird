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

  volatile unsigned short *PERIODL = (volatile unsigned short *) 0x04000028;
  volatile unsigned short *PERIODH = (volatile unsigned short *) 0x0400002c;
  volatile unsigned short *CONTROL = (volatile unsigned short *)0x04000024;


  *PERIODL = 29999999 & 0xffff;
  *PERIODH = 29999999 >> 16;

  *CONTROL = 0x7; //also enable interupts

  enable_interrupt();
}