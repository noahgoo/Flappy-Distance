#include "pipe.h"
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>

#define GAP_MIN 80
#define GAP_MAX 160

enum pipe_st_t
{
    idle_st,
    moving_st,
};

// Initialize the pipe data
void pipe_init(pipe_t *pipe)
{
    pipe->gap_y = pipe_random_gap(); // random gap height
    pipe->player_scored = false;
    pipe->currentState = idle_st;
}

// get random number for gap
coord_t pipe_random_gap(void)
{
    return (coord_t)(GAP_MIN + (rand() % (GAP_MAX - GAP_MIN + 1)));
}

// start a pipe moving
void pipe_start(pipe_t *pipe)
{
    pipe->currentState = moving_st;
}

bool pipe_did_player_score(pipe_t *pipe)
{
    return pipe->player_scored;
}

void pipe_player_scored(pipe_t *pipe)
{
    pipe->player_scored = true;
}

// draw pipe on screen
void pipe_draw(pipe_t *pipe)
{
    // draws top pipe
    lcd_fillRect2(pipe->x, 0, pipe->x + PIPE_WIDTH, pipe->gap_y - PIPE_GAP / 2, PIPE_COLOR);
    // draws bottom pipe
    lcd_fillRect2(pipe->x, pipe->gap_y + PIPE_GAP / 2, pipe->x + PIPE_WIDTH, LCD_H, PIPE_COLOR);
}

void pipe_tick(pipe_t *pipe)
{
    // Transitions
    switch (pipe->currentState)
    {
        case idle_st:
            break;
        case moving_st:
            if (pipe->x + PIPE_WIDTH <= 0)
            {
                // reset pipe if it reaches edge of screen
                pipe->x = LCD_W;
                pipe->gap_y = pipe_random_gap();
                pipe->player_scored = false;
            }
            break;
    }

    // Actions
    switch (pipe->currentState)
    {
        case idle_st:
            break;
        case moving_st:
            // move pipe to the left by PIPE_SPEED
            pipe->x -= PIPE_SPEED;
            pipe_draw(pipe);
    }
}