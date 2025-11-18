#ifndef BIRD_H_
#define BIRD_H_

#include <stdint.h>
#include "lcd.h"

typedef struct {
    int32_t currentState;
    const color_t *sprite; // Pointer to sprite image
    uint16_t s_width; // Sprite width
    uint16_t s_height; // Sprite height
    coord_t x_height; // Height of bird
    bool collision;
} bird_t;

void bird_init(bird_t *bird);
const color_t * bird_get_sprite(bird_t *bird);
void bird_tick(bird_t *bird);

#endif