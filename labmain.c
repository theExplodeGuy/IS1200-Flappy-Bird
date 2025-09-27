// main.c
#define SKY_BLUE   110
#define PIPE_GREEN 52
#define GROUND_BROWN 149
#define BIRD_YELLOW 254
#define BEAK_ORANGE 245
#define WING_LIGHT  255
#define EYE_WHITE       255
#define EYE_PUPIL       0
#define TRANSPARENT 0


volatile unsigned char *VGA_FRONT = (volatile unsigned char*) 0x08000000;
volatile unsigned char *VGA_BACK = (volatile unsigned char*) 0x08000000 + 0x12c00;

volatile int *VGA_CTRL = (volatile int*) 0x04000100;


#define SCREEN_X 320
#define SCREEN_Y 240

#define PIPES 4

#define PIPE_GAP 60
#define PIPE_WIDTH 30

typedef struct Pipe{
  int left_edge; // top most left corner
  int gap_y; // middlle of the opening of the pipe
  int active;
}Pipe;

typedef struct Bird{
  int x_pos;
  int y_pos;
  int alive;
}Bird;

Pipe pipes[PIPES];
Bird bird;

int gaps[15] = {1012, 2004, 1152, 1972, 304, 1996, 
  2021, 2005, 1994, 49, 824, 1453, 5559, 1821, 4897};
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

void update_pipes(){
  for(int i = 0; i < PIPES; i++){
    pipes[i].left_edge -=2;
    if(pipes[i].left_edge + PIPE_WIDTH < 0){
      pipes[i].left_edge = SCREEN_X + 50;
      pipes[i].gap_y = 60 + gaps[rand%15] % (SCREEN_Y - 120);
      rand++;
    }
  }
}

void update_bird(){
  bird.y_pos += 2;
}

void draw_bird(volatile unsigned char *buf){

  const unsigned char *bird_spite = (const unsigned char*) 0x02025800;

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++){
      if(bird.x_pos < SCREEN_X && bird.y_pos < SCREEN_Y && bird_spite[i*32+j] != 255)
        buf[(bird.y_pos + i)* SCREEN_X + (bird.x_pos + j)] = bird_spite[i*32+j];
    }
  }
}

void draw_pipe(int left_most, int gap_y, volatile unsigned char *buf){
  // top part
  for(int y = 0; y < (gap_y - PIPE_GAP/2); y++){
    for(int x = left_most; x < left_most + PIPE_WIDTH; x++){
      // if in screen
      if(x >= 0 && x < SCREEN_X){
        buf[y*SCREEN_X + x] = PIPE_GREEN;
      }
    }
  }

  // bottom part
  for(int y = (gap_y + PIPE_GAP/2); y < SCREEN_Y; y++){
    for(int x = left_most; x < left_most + PIPE_WIDTH; x++){
      // if in screen
      if(x >= 0 && x < SCREEN_X){
        buf[y*SCREEN_X + x] = PIPE_GREEN;
      }
    }
  }
}

void draw_all_pipes(volatile unsigned char *buf){
  for (int i = 0; i < PIPES; i++){
    draw_pipe(pipes[i].left_edge, pipes[i].gap_y, buf);
  }
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
}


void handle_interrupt(int cause){
  if(cause == 16){
    
  }
}

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

// Your code goes into main as well as any needed functions.
int main ( void ) {
  init();
  
  while(1){
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
    
    for (int i=0; i<1000000; i++) {
      asm volatile ("nop");
    }

  }

}
