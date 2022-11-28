#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/byteorder.h>

#include "sys_types.h"

#define MPU6050_ADDR 0x68

extern struct acceleration;

K_MSGQ_DEFINE(accel_queue, sizeof(struct acceleration), 10, 4);

void imu(void) {
    int ret;
    struct acceleration acc;

    uint8_t accel[6];

    const struct device *const i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));

    if (!device_is_ready(i2c_dev)) {
        return;
    }

    if (ret) return;

    while(1){
        ret = i2c_burst_read(i2c_dev, MPU6050_ADDR, 0x3B, &accel, 6);
        if (ret) return;

        acc.x = (float)(accel[0] << 8 | accel[1])/4096.0;
        acc.y = (float)(accel[2] << 8 | accel[3])/4096.0;
        acc.z = (float)(accel[4] << 8 | accel[5])/4096.0;

        k_msgq_put(&accel_queue, &acc, K_FOREVER);

        printk("acc.x:%.2f\n", acc.x);

        k_msleep(100);
    }
}