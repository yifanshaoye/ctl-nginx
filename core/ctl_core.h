
#ifndef _CTL_CORE_H_
#define _CTL_CORE_H_

#define CTL_OK      0
#define CTL_ERROR   -1

typedef struct ctl_cycle_s ctl_cycle_t;

// output, log, etc ...
#define ctl_perror(fmt, ...) printf(fmt, __VA_ARGS__)
#define ctl_pinfo ctl_perror

#define CTL_NGX_PREFIX "/root/cnginx/ctl-nginx"
#define CTL_CONF_FILE "/root/cnginx/ctl-nginx/conf/nginx.conf"

#endif
