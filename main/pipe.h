#ifndef PIPE_H_
#define PIPE_H_

#include <stdint.h>
#include "lcd.h"

typedef struct {
    int32_t currentState; // State of pipes
    coord_t x_current; // where pipe is on screen
    coord_t y_top; // top pipe y height
    coord_t y_bottom; // bottomw pipe y height
} pipe_t;

void pipe_tick(pipe_t *pipe);

#endif