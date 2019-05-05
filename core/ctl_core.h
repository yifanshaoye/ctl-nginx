
#ifndef _CTL_CORE_H_
#define _CTL_CORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CTL_OK      0
#define CTL_ERROR   -1

typedef struct ctl_cycle_s ctl_cycle_t;
typedef struct ctl_conf_s ctl_conf_t;
typedef struct ctl_command_s ctl_command_t;
typedef struct ctl_core_conf_s  ctl_core_conf_t;
typedef struct ctl_epoll_conf_s ctl_epoll_conf_t;

// output, log, etc ...
#define ctl_perror  printf
#define ctl_pinfo ctl_perror

#define CNGINX "0.0.1"
#define CTL_NGX_PREFIX "/home/chentenglong/cnginx/ctl-nginx/"
//#define CTL_CONF_FILE "/home/chentenglong/cnginx/ctl-nginx/conf/cnginx.conf"
#define CTL_CONF_FILE "/home/ctl/ctl-nginx/conf/cnginx.conf"

#define LF     (u_char) '\n'
#define CR     (u_char) '\r'
#define CRLF   "\r\n"


#endif
