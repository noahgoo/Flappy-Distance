#include "ultrasensor.h"
#include "rom/ets_sys.h"
#include "esp_timer.h"
#include <string.h>

// Initialize trigger and echo pins for sensor
void ultrasensor_init(pin_num_t trigger, pin_num_t echo)
{
    pin_reset(trigger);
    pin_reset(echo);
    pin_output(trigger, true);
    pin_input(echo, true);
}

// Median filter to kill spikes
float ultrasensor_median_filter(float new_reading) {
    static float buffer[MEDIAN_SIZE] = {15.0, 15.0, 15.0, 15.0, 15.0};  // Initialize to reasonable value
    static uint8_t index = 0;
    
    // Add to circular buffer
    buffer[index] = new_reading;
    index = (index + 1) % MEDIAN_SIZE;
    
    // Sort and return median
    float sorted[MEDIAN_SIZE];
    memcpy(sorted, buffer, sizeof(buffer));
    
    // Bubble sort
    for (int i = 0; i < MEDIAN_SIZE - 1; i++) {
        for (int j = 0; j < MEDIAN_SIZE - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                float temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    
    return sorted[MEDIAN_SIZE / 2];  // Return middle value
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
        if (esp_timer_get_time() - start > ECHO_TIMEOUT_US)
        {
            printf("TIMEOUT: Echo never went HIGH\n");
            return -1.0;
        } 
    }

    start = esp_timer_get_time(); // Echo went high
    while (pin_get_level(echo) == 1) // Loop while high
    {
        if (esp_timer_get_time() - start > ECHO_TIMEOUT_US) 
        {
            printf("TIMEOUT: ECHO never went LOW\n");
            return -1.0;
        }
    }
    int64_t duration = esp_timer_get_time() - start;

    return (duration * 0.0343) / 2.0;
}