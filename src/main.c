/*
 *    (C) 2024 by mwhitecliff
 *    Zephyr Workshop
 * 
 *    SPDX-License-Identifier: Apache-2.0
 */

#include "version.h"
#include "sensor.h"

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(selog, LOG_LEVEL_INF);


int main (void)
{

    sensor_create();

    return 0;
}
