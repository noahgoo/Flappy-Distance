#ifndef PIPE_H_
#define PIPE_H_

#include <stdint.h>
#include "lcd.h"

#define NUM_OF_PIPES 3
#define PIPE_WIDTH 30
#define PIPE_GAP 60
#define PIPE_SPACING (LCD_W + PIPE_WIDTH) / 3
#define PIPE_SPEED 2
#define PIPE_COLOR 0x2C4A

typedef struct {
    int32_t currentState; // State of pipes
    coord_t x; // position of front of pipe
    coord_t gap_y; // center of the gap
    bool player_scored; // did player score through this pipe?
} pipe_t;

void pipe_init(pipe_t *pipe);
coord_t pipe_random_gap(void);
void pipe_start(pipe_t *pipe);
bool pipe_did_player_score(pipe_t *pipe);
void pipe_player_scored(pipe_t *pipe);
void pipe_draw(pipe_t *pipe);
void pipe_tick(pipe_t *pipe);

#endif