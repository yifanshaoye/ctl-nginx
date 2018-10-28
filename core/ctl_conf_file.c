#include <ctl_core.h>
#include <ctl_conf_file.h>
#include <ctl_modules.h>

ctl_command_t ctl_conf_commands[] = {
    ctl_null_command
};

ctl_module_t ctl_conf_module = {
    CTL_MODULE_V1,
    ctl_conf_commands,
    NULL
};
