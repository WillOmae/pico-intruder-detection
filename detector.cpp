#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "string.h"

#define PIN_HIGH 1
#define PIN_LOW 0

const uint PIR_PIN = 16;
const uint LED_PIN = 25; /* onboard LED */

uint current_state = 0;

void setup();
void loop();
void detect();

int main()
{
	setup();
	loop();
}

void setup()
{
	gpio_init(PIR_PIN);
	gpio_init(LED_PIN);

	gpio_set_dir(PIR_PIN, GPIO_IN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	/* PIR sensor requires up to 1 minute to calibrate */
	uint led_state_duration_ms = 100;
	uint toggles_per_second = 1000 / (led_state_duration_ms * 2);
	for (int i = 0; i < (60 * toggles_per_second); i++)
	{
		gpio_put(LED_PIN, PIN_HIGH);
		sleep_ms(led_state_duration_ms);
		gpio_put(LED_PIN, PIN_LOW);
		sleep_ms(led_state_duration_ms);
	}
}

void loop()
{
	while (true)
	{
		detect();
		sleep_ms(1000);
	}
}

void detect()
{
	current_state = gpio_get(PIR_PIN);

	if (current_state == PIN_HIGH)
	{
		gpio_put(LED_PIN, PIN_HIGH);
		sleep_ms(1000);
		gpio_put(LED_PIN, PIN_LOW);
	}
}