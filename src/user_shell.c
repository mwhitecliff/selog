/*
 *    (C) 2024 by mwhitecliff
 *    Zephyr Workshop
 * 
 *    SPDX-License-Identifier: Apache-2.0
 */

#include "version.h"

#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(user_shell, LOG_LEVEL_INF);

static int cmd_print_version(const struct shell *shell, size_t argc, char **argv)
{
    shell_print(shell, "Version: %d.%02d.%02d", VERSION_MAJOR, VERSION_MINOR, VERSION_FIX);

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_print,
                               SHELL_CMD(version, NULL, "print version", cmd_print_version),
                               SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(print, &sub_print, "Print System information", NULL);