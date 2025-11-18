// flappy_bird_bitmap.h
// 32x32 Flappy Bird sprite as RGB565 color bitmap
// Total size: 2048 bytes (32x32 pixels × 2 bytes per pixel)
// Format: RGB565 as uint16_t array
// Background: Black (0x0000)

#ifndef FLAPPY_BIRD_BITMAP_H
#define FLAPPY_BIRD_BITMAP_H

#include <stdint.h>

// 32x32 RGB565 color bitmap (1024 uint16_t values)
extern const uint16_t flappy_bird[];

#endif // FLAPPY_BIRD_BITMAP_H