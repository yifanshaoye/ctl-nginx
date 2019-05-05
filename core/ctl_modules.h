#ifndef _CTL_MODULES_H_
#define _CTL_MODULES_H_

#include <ctl_conf_file.h>

#define CTL_MODULE_V1   -1, -1, 0, 0

typedef struct ctl_module_s ctl_module_t;

int ctl_modules_init();
int ctl_cycle_modules(ctl_cycle_t *);

#define CTL_CORE_MODULE   1
#define CTL_EVENT_MODULE  2
#define CTL_HTTP_MODULE   4

struct ctl_module_s {
    int     ctx_index;
    int     index;
    char    *name;
    void    *ops;
    ctl_command_t       *commands;
    int     type;
    void     *(*create_conf)(ctl_cycle_t *);
};

#endif
