/*
 *    (C) 2024 by mwhitecliff
 *    Zephyr Workshop
 * 
 *    SPDX-License-Identifier: Apache-2.0
 */

#include "version.h"

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(selog, LOG_LEVEL_INF);

extern void read_sensor(void *data, void *d1, void *d2);

#define SENSOR_STACK_SIZE 500
#define SENSOR_PRIORITY -5

K_KERNEL_STACK_DEFINE(sensor_stack_area, SENSOR_STACK_SIZE);

int main (void)
{
    struct k_thread sensor_thread_ctl;
    k_tid_t sensor_tid;

    LOG_INF("Selog %d.%02d.%02d", VERSION_MAJOR, VERSION_MINOR, VERSION_FIX);

    sensor_tid = k_thread_create(&sensor_thread_ctl, sensor_stack_area,
                                 K_KERNEL_STACK_SIZEOF(sensor_stack_area),
                                 read_sensor,
                                 NULL, NULL, NULL,
                                 SENSOR_PRIORITY, 0, K_NO_WAIT);

    if (sensor_tid != &sensor_thread_ctl)
    {
        LOG_ERR("Error while creating thread: %d", (int)sensor_tid);
        return 1;
    }

    k_thread_name_set(sensor_tid, "sensor");

    return 0;
}
