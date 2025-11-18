#include "lcd.h"
#include "bird.h"
#include "flappy_bird_bitmap.h"

enum bird_st_t
{
    idle_st,
    moving_st,
    collision_st,
};

void bird_init(bird_t *bird)
{
    bird->sprite = (const color_t *)flappy_bird;
}

const color_t * bird_get_sprite(bird_t *bird)
{
    return bird->sprite;
}

// TODO: Create bird tick
void bird_tick(bird_t *bird)
{

}