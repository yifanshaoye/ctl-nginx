#ifndef _CTL_CONF_FILE_H_
#define _CTL_CONF_FILE_H_

struct ctl_command_s {
    char        *name;
    int         type;
    int         (*set)();
    int         offset;
};

#define ctl_null_command {0, 0, 0, 0}

#define CTL_CONF_UNSET  -1
#define CTL_ADDR_UNSET  0

#define CTL_CORE_COMMAND    (1 << 0)
#define CTL_HTTP_COMMAND    (1 << 1)

#endif
