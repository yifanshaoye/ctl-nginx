#ifndef _CTL_CYCLE_H_
#define _CTL_CYCLE_H_

#include <ctl_connection.h>
#include <ctl_modules.h>

struct ctl_cycle_s {
    void                ****conf_ctx;
    ctl_listening_t     *listening[CTL_LISTENING_MAX];
    ctl_module_t        **modules;
    int                 module_n;
    char                *conf_file;
    char                *root_dir;
};

struct ctl_core_conf_s {
    int worker_processes;
};

#endif
