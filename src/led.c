#include <zephyr.h>
#include <zephyr/drivers/gpio.h>

#define GREEN_LED_NODE DT_ALIAS(green_led)
#define RED_LED_NODE DT_ALIAS(red_led)
#define BLUE_LED_NODE DT_ALIAS(blue_led)

struct led {
	struct gpio_dt_spec spec; 
	int sleep_time;
	int id;
};

void blink(struct led led_config){
	int ret;

	ret = gpio_pin_configure_dt(&led_config.spec, GPIO_OUTPUT_ACTIVE);

	if (ret < 0) return;

	while(1) {
		ret = gpio_pin_toggle_dt(&led_config.spec);
		if (ret < 0) return;

		k_msleep(led_config.sleep_time);
	}
}

void blink_red(void) {
	struct led led_config = {
		.sleep_time = 333,
		.spec = GPIO_DT_SPEC_GET(RED_LED_NODE, gpios),
		.id = 0xff0000,
	};
	printk("Enabling Red LED");
	blink(led_config);
};

void blink_green(void) {
	struct led led_config = {
		.sleep_time = 250,
		.spec = GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios),
		.id = 0x00ff00,
	};
	blink(led_config);
};

void blink_blue(void) {
	struct led led_config = {
		.sleep_time = 653,
		.spec = GPIO_DT_SPEC_GET(BLUE_LED_NODE, gpios),
		.id = 0x0000ff,
	};
	blink(led_config);
};