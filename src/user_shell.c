/*
 *    (C) 2024 by mwhitecliff
 *    Zephyr Workshop
 * 
 *    SPDX-License-Identifier: Apache-2.0
 */

#include "version.h"
#include "sensor.h"

#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/random/random.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(user_shell, LOG_LEVEL_INF);

static int cmd_print_version(const struct shell *shell, size_t argc, char **argv)
{
    shell_print(shell, "Version: %d.%02d.%02d", VERSION_MAJOR, VERSION_MINOR, VERSION_FIX);

    return 0;
}

static int cmd_print_random(const struct shell *shell, size_t argc, char **argv)
{
    uint32_t rnd = sys_rand32_get();
    shell_print(shell, "Number: %d", rnd);

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_print,
                               SHELL_CMD(version, NULL, "print version", cmd_print_version),
                               SHELL_CMD(random, NULL, "print random value", cmd_print_random),
                               SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(print, &sub_print, "Print System information", NULL);


static int cmd_selog_suspend(const struct shell *shell, size_t argc, char **argv)
{
    sensor_suspend();
    return 0;
}

static int cmd_selog_resume(const struct shell *shell, size_t argc, char **argv)
{
    sensor_resume();
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_selog,
                               SHELL_CMD(suspend, NULL, "suspend read thread", cmd_selog_suspend),
                               SHELL_CMD(resume, NULL, "resume read thread", cmd_selog_resume),
                               SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(selog, &sub_selog, "Control selog system", NULL);