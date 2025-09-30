#define SKY_BLUE   110
#define PIPE_GREEN 52
#define GROUND_BROWN 149
#define BIRD_YELLOW 254
#define BEAK_ORANGE 245
#define WING_LIGHT  255
#define EYE_WHITE       255
#define EYE_PUPIL       0
#define TRANSPARENT 0

#define SCREEN_X 320
#define SCREEN_Y 240

#define PIPES 4

#define PIPE_GAP 60
#define PIPE_WIDTH 30

extern const int gaps[15];
extern int rand;
extern int scroll_x;
extern int score;


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

extern Pipe pipes[PIPES];
extern Bird bird;


void init_pipes();

void init_bird();

void init();

void init_hexdisplays();

void set_displays(int display_number, int value);