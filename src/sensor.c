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

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

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
    }
    else
    {
        k_thread_name_set(sensor_tid, "sensor");
    }
}

void sensor_thread(void *data, void *d1, void *d2)
{
    const struct device *bme = DEVICE_DT_GET(DT_NODELABEL(pres1));
    struct sensor_value temp, pres, humi;

    LOG_INF("sensor_thread start");

    while (1)
    {
        k_sleep(K_SECONDS(2));
        sensor_sample_fetch(bme);
        
        sensor_channel_get(bme, SENSOR_CHAN_AMBIENT_TEMP, &temp);
        sensor_channel_get(bme, SENSOR_CHAN_PRESS, &pres);
        sensor_channel_get(bme, SENSOR_CHAN_HUMIDITY, &humi);
        
        LOG_DBG("%d.%02d °C", temp.val1, temp.val2/10000);
        LOG_DBG("%d.%02d %%", humi.val1, humi.val2/10000);
        LOG_DBG("%d.%02d kPa", pres.val1, pres.val2/10000);
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

