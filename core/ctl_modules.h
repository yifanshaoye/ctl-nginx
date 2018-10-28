#ifndef _CTL_MODULES_H_
#define _CTL_MODULES_H_

#include <ctl_conf_file.h>

#define CTL_MODULE_V1   -1, 0

typedef struct ctl_module_s ctl_module_t;

struct ctl_module_s {
    int     index;
    char    *name;
    ctl_command_t       *commands;
    void     *(*create_conf)(ctl_cycle_t *);
};

#endif
