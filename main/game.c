#include <stdint.h>
#include <stdio.h>

#include "game.h"
#include "hw.h"
#include "lcd.h"
#include "config.h"
#include "bird.h"
#include "flappy_bird_bitmap.h"

bird_t test_bird;

void game_init(void)
{
    // TODO: Initialize the game
    bird_init(&test_bird);
}

void game_tick(void)
{
    // TODO: game logic
    lcd_drawRGBBitmap(50, 50, test_bird.sprite, 32, 32);
}