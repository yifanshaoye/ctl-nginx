#include <ctl_core.h>

static ctl_command_t ctl_epoll_commands[] = {
    ctl_null_command
}

ctl_module_t ctl_epoll_module = {
    CTL_MODULE_V1,
    ctl_epoll_commands,
    NULL
};


