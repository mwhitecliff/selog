/*
 *    (C) 2024 by mwhitecliff
 *    Zephyr Workshop
 * 
 *    SPDX-License-Identifier: Apache-2.0
 */


#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(selog, LOG_LEVEL_INF);

int main (void)
{
    LOG_INF("Hello world");
    return 0;
}
