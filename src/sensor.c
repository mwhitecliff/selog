/*
 *    (C) 2024 by mwhitecliff
 *    Zephyr Workshop
 * 
 *    SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(sensor, LOG_LEVEL_INF);

void read_sensor(void *data, void *d1, void *d2)
{
    LOG_INF("read_sensor start");
    k_sleep(K_SECONDS(1));
    LOG_INF("read_sensor end");
}

