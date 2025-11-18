#include <stdio.h>
#include "config.h"
#include "game.h"
#include "pin.h"
#include "lcd.h"
#include "sound.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"

static const char *TAG = "lab07";

// The update period as an integer in ms
#define PER_MS ((uint32_t)(CONFIG_GAME_TIMER_PERIOD*1000))
#define TIME_OUT 500 // ms

TimerHandle_t update_timer; // Declare timer handle for update callback

volatile bool interrupt_flag;

uint32_t isr_triggered_count;
uint32_t isr_handled_count;

// Interrupt handler for game - use flag method
void update() {
	interrupt_flag = true;
	isr_triggered_count++;
}

// Main application
void app_main(void)
{
	ESP_LOGI(TAG, "Starting");

	// ISR flag and counts
	interrupt_flag = false;
	isr_triggered_count = 0;
	isr_handled_count = 0;

	// Initialization
	lcd_init();
	lcd_frameEnable();
	lcd_fillScreen(CONFIG_COLOR_BACKGROUND);
	game_init();
	// TODO: Initialize sound

	// Configure I/O pins for buttons
	pin_reset(HW_BTN_A);
	pin_input(HW_BTN_A, true);
	pin_reset(HW_BTN_B);
	pin_input(HW_BTN_B, true);
	pin_reset(HW_BTN_MENU);
	pin_input(HW_BTN_MENU, true);
	pin_reset(HW_BTN_OPTION);
	pin_input(HW_BTN_OPTION, true);
	pin_reset(HW_BTN_SELECT);
	pin_input(HW_BTN_SELECT, true);
	pin_reset(HW_BTN_START);
	pin_input(HW_BTN_START, true);

	// Initialize update timer
	update_timer = xTimerCreate(
		"update_timer",        // Text name for the timer.
		pdMS_TO_TICKS(PER_MS), // The timer period in ticks.
		pdTRUE,                // Auto-reload the timer when it expires.
		NULL,                  // No need for a timer ID.
		update                 // Function called when timer expires.
	);
	if (update_timer == NULL) {
		ESP_LOGE(TAG, "Error creating update timer");
		return;
	}
	if (xTimerStart(update_timer, pdMS_TO_TICKS(TIME_OUT)) != pdPASS) {
		ESP_LOGE(TAG, "Error starting update timer");
		return;
	}

	// Main game loop
	uint64_t t1, t2, tmax = 0; // For hardware timer values
	while (pin_get_level(HW_BTN_MENU)) // while MENU button not pressed
	{
		while (!interrupt_flag) ;
		t1 = esp_timer_get_time();
		interrupt_flag = false;
		isr_handled_count++;

#ifndef CONFIG_ERASE
		lcd_fillScreen(CONFIG_COLOR_BACKGROUND);
#endif // CONFIG_ERASE
		game_tick();

		lcd_writeFrame();
		t2 = esp_timer_get_time() - t1;
		if (t2 > tmax) tmax = t2;
	}

	printf("Handled %lu of %lu interrupts\n", isr_handled_count, isr_triggered_count);
	printf("WCET us:%llu\n", tmax);
}
