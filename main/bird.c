#include <stdio.h>
#include "lcd.h"
#include "bird.h"
#include "flappy_bird_bitmap.h"
#include "cursor.h"
#include "ultrasensor.h"
#include "config.h"

enum bird_st_t
{
    idle_st,
    moving_st,
    collision_st,
};

static enum bird_st_t currentState;
// static coord_t x;
static coord_t y;
static float smoothed_y = 0;


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
            // Use alpha filter to smooth out inputs
            float raw_distance = ultrasensor_read_distance(TRIGGER_PIN, ECHO_PIN);
            if (raw_distance >= 0)
            {
                smoothed_y = (ALPHA * raw_distance) + ((1 - ALPHA) * smoothed_y);
            }

            y = (coord_t)smoothed_y;
            y *= Y_SCALER; // Scale y up
            if (y < 0)  // Keep y in range
            {
                y = 0;
            } else if (y > 213)
            {
                y = 213;
            }
            printf("Y is %ld\n", y);
            lcd_drawRGBBitmap(BIRD_X_POS, y, flappy_bird, BIRD_SIZE, BIRD_SIZE);
            break;
        case collision_st:
            break;
    }
}