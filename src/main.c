#include <zephyr/zephyr.h>
#include "sys_types.h"

#define STACK_SIZE 500

extern void blink_blue(void);
extern void blink_green(void);
extern void blink_red(void);
extern void imu(void);

K_THREAD_DEFINE(led_red_tid, STACK_SIZE, blink_red, NULL, NULL, NULL, 4, 0, 0);
K_THREAD_DEFINE(led_green_tid, STACK_SIZE, blink_green, NULL, NULL, NULL, 3, 0, 0);
K_THREAD_DEFINE(led_blue_tid, STACK_SIZE, blink_blue, NULL, NULL, NULL, 2, 0, 0);
K_THREAD_DEFINE(imu_tid, STACK_SIZE, imu, NULL, NULL, NULL, 1, 0, 0);

void main() {
    struct acceleration accel;
    while(1) {
        k_msgq_get(&accel_queue, &accel, K_FOREVER);
    }

}