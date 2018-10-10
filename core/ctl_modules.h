#ifndef _CTL_MODULES_H_
#define _CTL_MODULES_H_

#define CTL_MODULE_V1   -1, 0

struct ctl_module_t {
    int     index;
    char    *name;
    ctl_command_t       *commands;
    int     (*create_conf)();
}

#endif
