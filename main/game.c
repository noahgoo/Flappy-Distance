#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "hw.h"
#include "lcd.h"
#include "config.h"
#include "bird.h"
#include "flappy_bird_bitmap.h"
#include "pipe.h"
#include "esp_random.h"
#include "cursor.h"
#include "pin.h"

#define STATS_ARRAY_L 50
#define STATS_X 0
#define STATS_Y 0

// All pipes
pipe_t pipes[NUM_OF_PIPES];

typedef enum {
    waiting_st,
    playing_st,
    game_over_st
} game_state_st;

game_state_st currentState;

// Scoring stats
static int16_t pipes_passed;
char stats[STATS_ARRAY_L];

void game_init(void)
{
    srand(esp_random());
    currentState = waiting_st;
    pipes_passed = 0;

    // initialize bird and pipes
    bird_init();

    for (uint8_t i = 0; i < NUM_OF_PIPES; i++)
    {
        pipe_init(&pipes[i]);
        if (i == 0)
            pipes[i].x = LCD_W;
        else
            pipes[i].x = LCD_W + (i * PIPE_SPACING);
    }
}

void game_tick(void)
{
    switch (currentState)
    {
        case waiting_st:
            bird_tick();
            // Check for button A press to start game
            if (!pin_get_level(HW_BTN_A))
            {
                currentState = playing_st;
                bird_start();
                for (uint8_t i = 0; i < NUM_OF_PIPES; i++)
                    pipe_start(&pipes[i]);
            }
            break;
        case playing_st:
            // Tick like normal
            bird_tick();
            for (uint8_t i = 0; i < NUM_OF_PIPES; i++)
                pipe_tick(&pipes[i]);

            // check for collisions
            coord_t bird_y = bird_get_position();
            for (uint8_t i = 0; i < NUM_OF_PIPES; i++)
            {
                if ((pipes[i].x < BIRD_X_POS + BIRD_SIZE) && // Check the bird is on the same x level as the pipe
                    (pipes[i].x + PIPE_WIDTH > BIRD_X_POS))
                {
                    if ((bird_y + BIRD_SIZE > pipes[i].gap_y + PIPE_GAP / 2) || // check if the bird is outside the gap
                        (bird_y < pipes[i].gap_y - PIPE_GAP / 2))
                    {
                        bird_collision();
                        printf("Collision when bird is at %ld\n", bird_y);
                        printf("Pipe was at %ld\n", pipes[i].gap_y - PIPE_GAP / 2);
                        currentState = game_over_st;
                    }
                }
            }

            // Check if pipe was passed by bird and player scored
            for (uint8_t i = 0; i < NUM_OF_PIPES; i++)
            {
                if ((pipes[i].x + PIPE_WIDTH < BIRD_X_POS) && (pipes[i].x > 0))
                {
                    if (!pipe_did_player_score(&pipes[i]))
                    {
                        pipes_passed += 1;
                        pipe_player_scored(&pipes[i]);
                    }
                }
        
            }

            // Draw stats
            sprintf(stats, "Score: %d", pipes_passed);
            lcd_drawString(STATS_X, STATS_Y, stats, CONFIG_STATS_COLOR);
            break;
        case game_over_st:
            currentState = waiting_st;
            game_init();
            break;
    }
}