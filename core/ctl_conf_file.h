#ifndef _CTL_CONF_FILE_H_
#define _CTL_CONF_FILE_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctl_cycle.h>

struct ctl_command_s {
    char        *name;
    int         type;
    int         (*set)(ctl_conf_t *, void *);
    int         offset;
};

#define ctl_null_command {'\0', 0, NULL, 0}

#define CTL_CONF_UNSET  -1
#define CTL_ADDR_UNSET  0

#define CTL_CONF_BLOCK_START    1
#define CTL_CONF_BLOCK_DONE     2
#define CTL_CONF_FILE_DONE      3

#define CTL_CORE_COMMAND    1
#define CTL_EVENT_COMMAND   2
#define CTL_HTTP_COMMAND    4

#define CTL_MAX_COMMAND_LEN     32
#define CTL_MAX_ARG_LEN         64 

typedef struct {
    int fd;
    char *name;
    struct stat info;
    int line;
    char *start;
    char *pos;
    char *end;
} ctl_conf_file_t;

struct ctl_conf_s {
    char                name[CTL_MAX_COMMAND_LEN];
    char                arg[CTL_MAX_ARG_LEN];    // only one argument is supported, now !

    ctl_cycle_t         *cycle;
    ctl_conf_file_t     conf_file;

    void                *ctx;
    int                 module_type;
    int                 cmd_type;
};


#endif
