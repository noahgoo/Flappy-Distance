#ifndef BIRD_H_
#define BIRD_H_

#include <stdint.h>
#include "lcd.h"

#define BIRD_MIDDLE 16
#define BIRD_X_POS 50
#define BIRD_SIZE 32

void bird_init(void);
void bird_start(void);
coord_t bird_get_position(void);
void bird_collision(void);
void bird_tick(void);


#endif