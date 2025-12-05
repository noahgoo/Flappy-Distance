#include <stdio.h>
#include "lcd.h"
#include "bird.h"
#include "flappy_bird_bitmap.h"
#include "cursor.h"
#include "ultrasensor.h"
#include "config.h"
#include "esp_timer.h"

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
           
            static uint32_t last_sensor_read = 0;
            static float smoothed_y = 15.0;  // Initialize to reasonable middle value

            if (esp_timer_get_time() / 1000 - last_sensor_read > 60) 
            {
                float raw = ultrasensor_read_distance(TRIGGER_PIN, ECHO_PIN);
                printf("RAW: %.2f\n", raw);
    
                // Only process valid readings
                if (raw >= 5.0 && raw <= 200.0) 
                {
                    // Step 1: Median filter kills those 0.5-3cm spikes
                    float median = ultrasensor_median_filter(raw);
                    printf("MEDIAN: %.2f\n", median);
                    
                    // Step 2: Alpha filter smooths what's left
                    smoothed_y = (ALPHA * median) + ((1.0 - ALPHA) * smoothed_y);
                    printf("SMOOTHED: %.2f\n", smoothed_y);
                }
    
                last_sensor_read = esp_timer_get_time() / 1000;
            }

            // Scale and clamp
            y = (coord_t)(smoothed_y * Y_SCALER);
            if (y < 0) y = 0;
            else if (y > 213) y = 213;

            lcd_drawRGBBitmap(BIRD_X_POS, y, flappy_bird, BIRD_SIZE, BIRD_SIZE);
            break;
        case collision_st:
            break;
    }
}