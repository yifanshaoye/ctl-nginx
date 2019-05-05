#include <ctl_core.h>
#include <ctl_conf_file.h>
#include <ctl_modules.h>
#include <ctl_epoll.h>

static void *ctl_create_epoll_conf(ctl_cycle_t *);

static ctl_command_t ctl_epoll_commands[] = {
    ctl_null_command
};

ctl_module_t ctl_epoll_module = {
    CTL_MODULE_V1,
    ctl_epoll_commands,
    CTL_EVENT_MODULE,
    ctl_create_epoll_conf
};

static void *
ctl_create_epoll_conf(ctl_cycle_t *cycle)
{
    if(cycle == NULL) return NULL;

    ctl_epoll_conf_t *ecf;

    ecf = (ctl_epoll_conf_t *) malloc(sizeof(ctl_epoll_conf_t));
    if(ecf == NULL) {
        ctl_perror("Error: malloc memory for ctl_epoll_conf failed\n");
        return NULL;
    }

    ecf->connections = CTL_CONF_UNSET;
    return ecf;
}

