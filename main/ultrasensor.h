#ifndef ULTRASENSOR_H_
#define ULTRASENSOR_H_

#include <stdint.h>
#include <stdio.h>
#include "hw.h"
#include "pin.h"

#define TRIGGER_TIMEOUT_US 10
#define ECHO_TIMEOUT_US 3000

void ultrasensor_init(pin_num_t trigger, pin_num_t echo);
float ultrasensor_read_distance(pin_num_t trigger, pin_num_t echo);

#endif