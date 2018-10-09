#ifndef _CTL_CYCLE_H_
#define _CTL_CYCLE_H_

struct ctl_cycle_s {
    void                ****conf_ctx;
    ctl_listening_t     *listening[CTL_LISTEN_MAX];
    char                *conf_file;
    char                *root_dir;
};

#endif
