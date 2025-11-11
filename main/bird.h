#ifndef BIRD_H_
#define BIRD_H_

#include <stdint.h>
#include "lcd.h"

typedef struct {
    int32_t currentState;
    // TODO: Bird image
    coord_t x_height;
    bool collision;
} bird_t;

#endif