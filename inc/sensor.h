/*
 *    (C) 2024 by mwhitecliff
 *    Zephyr Workshop
 * 
 *    SPDX-License-Identifier: Apache-2.0
 */
#ifndef SENSOR_H
#define SENSOR_H

void sensor_create(void);
void sensor_thread(void *data, void *d1, void *d2);
void sensor_suspend(void);
void sensor_resume(void);

#endif /*SENSOR_H */
