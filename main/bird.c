#include <stdio.h>
#include "lcd.h"
#include "bird.h"
#include "flappy_bird_bitmap.h"
#include "cursor.h"

enum bird_st_t
{
    idle_st,
    moving_st,
    collision_st,
};

static enum bird_st_t currentState;
static coord_t x;
static coord_t y;


void bird_init(void)
{
    currentState = idle_st;
}

// let the bird start moving
void bird_start(void)
{
    currentState = moving_st;
}

coord_t bird_get_position(void)
{
    return y;
}

void bird_collision(void)
{
    currentState = collision_st;
}

// Main bird tick function
void bird_tick(void)
{
    // Transistions
    switch (currentState)
    {
        case idle_st:
            break;
        case moving_st:
            break;
        case collision_st:
            break;
    }

    // Actions
    switch (currentState)
    {
        case idle_st:
            // draw bird on start screen
            lcd_drawRGBBitmap(BIRD_X_POS, 75, flappy_bird, BIRD_SIZE, BIRD_SIZE);
            break;
        case moving_st:
            cursor_get_pos(&x, &y); // get cursor position
            if (y > 213)
                y = 213;  
            lcd_drawRGBBitmap(BIRD_X_POS, y, flappy_bird, BIRD_SIZE, BIRD_SIZE);
            break;
        case collision_st:
            break;
    }
}