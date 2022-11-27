#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>

#define STACK_SIZE 500

#define UART0_NODE DT_ALIAS(serial_out)

LOG_MODULE_REGISTER(blinky_logging);

extern void blink_blue(void);
extern void blink_green(void);
extern void blink_red(void);

K_THREAD_DEFINE(led_red_tid, STACK_SIZE, blink_red, NULL, NULL, NULL, 1, 0, 0);
K_THREAD_DEFINE(led_green_tid, STACK_SIZE, blink_green, NULL, NULL, NULL, 1, 0, 0);
K_THREAD_DEFINE(led_blue_tid, STACK_SIZE, blink_blue, NULL, NULL, NULL, 1, 0, 0);