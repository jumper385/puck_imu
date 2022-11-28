#include <zephyr/zephyr.h>

extern struct k_msgq accel_queue;

struct acceleration {
    float x;
    float y;
    float z;
};