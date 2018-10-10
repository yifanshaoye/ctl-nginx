#include <ctl_core.h>

ctl_command_t ctl_conf_commands[] = {
    ctl_null_command
};

ctl_module_t ctl_conf_module = {
    CTL_MODULE_V1,
    ctl_conf_commands,
    NULL
};
