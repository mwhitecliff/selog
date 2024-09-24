/*
 *    (C) 2024 by mwhitecliff
 *    Zephyr Workshop
 * 
 *    SPDX-License-Identifier: Apache-2.0
 */

#include "sensor.h"

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(sensor, LOG_LEVEL_DBG);

#define SENSOR_STACK_SIZE 500
#define SENSOR_PRIORITY -5

K_KERNEL_STACK_DEFINE(sensor_stack_area, SENSOR_STACK_SIZE);

// local variable
static struct k_thread sensor_thread_ctl;
static k_tid_t sensor_tid;

void sensor_create(void)
{
    sensor_tid = k_thread_create(&sensor_thread_ctl, sensor_stack_area,
                                 K_KERNEL_STACK_SIZEOF(sensor_stack_area),
                                 sensor_thread,
                                 NULL, NULL, NULL,
                                 SENSOR_PRIORITY, 0, K_NO_WAIT);

    if (sensor_tid != &sensor_thread_ctl)
    {
        LOG_ERR("Error while creating thread: %d", (int)sensor_tid);
        return 1;
    }

    k_thread_name_set(sensor_tid, "sensor");
}

void sensor_thread(void *data, void *d1, void *d2)
{
    LOG_INF("sensor_thread start");

    while (1)
    {
        k_sleep(K_SECONDS(2));
        LOG_DBG("sensor thread is looping...");
    }
    
    LOG_INF("sensor_thread terminate");
}

void sensor_suspend(void)
{
    k_thread_suspend(sensor_tid);
    LOG_INF("sensor task suspended");
}

void sensor_resume(void)
{
    k_thread_resume(sensor_tid);
    LOG_INF("sensor task resume");
}

