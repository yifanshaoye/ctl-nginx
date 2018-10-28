#ifndef _CTL_CYCLE_H_
#define _CTL_CYCLE_H_

#include <ctl_connection.h>

struct ctl_cycle_s {
    void                ****conf_ctx;
    ctl_listening_t     *listening[CTL_LISTENING_MAX];
    char                *conf_file;
    char                *root_dir;
};

struct ctl_core_conf_s {
    int worker_processes;
};

#endif
