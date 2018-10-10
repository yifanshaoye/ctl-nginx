#ifndef _CTL_CONF_FILE_H_
#define _CTL_CONF_FILE_H_

struct ctl_command_s {
    char        *name;
    int         type;
    int         *(*set)();
    int         offset;
}

#endif
