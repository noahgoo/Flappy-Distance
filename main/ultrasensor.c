#include "ultrasensor.h"
#include "rom/ets_sys.h"
#include "esp_timer.h"

// Initialize trigger and echo pins for sensor
void ultrasensor_init(pin_num_t trigger, pin_num_t echo)
{
    pin_reset(trigger);
    pin_reset(echo);
    pin_output(trigger, true);
    pin_input(echo, true);
}

// read the distance from a pulse of the ultrasonic sensor
float ultrasensor_read_distance(pin_num_t trigger, pin_num_t echo)
{
    // Set trigger high for 10u seconds
    pin_set_level(trigger, 1);
    ets_delay_us(TRIGGER_TIMEOUT_US);
    pin_set_level(trigger, 0);

    int64_t start = esp_timer_get_time();
    while (pin_get_level(echo) == 0) // Loop while echo is still low
    {
        if (esp_timer_get_time() - start > ECHO_TIMEOUT_US) return -1.0;
    }

    start = esp_timer_get_time(); // Echo went high
    while (pin_get_level(echo) == 1) // Loop while high
    {
        if (esp_timer_get_time() - start > ECHO_TIMEOUT_US) return -1.0;
    }
    int64_t duration = esp_timer_get_time() - start;

    return (duration * 0.0343) / 2.0;
}