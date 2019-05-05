#include <ctl_core.h>
#include <ctl_cycle.h>
#include <ctl_modules.h>

extern ctl_module_t ctl_core_module;
extern ctl_module_t ctl_conf_module;
extern ctl_module_t ctl_events_module;
extern ctl_module_t ctl_epoll_module;
extern ctl_module_t ctl_http_module;

int ctl_modules_n;

ctl_module_t *ctl_modules[] = {
    &ctl_core_module,
    &ctl_conf_module,
    &ctl_events_module,
    &ctl_epoll_module,
    &ctl_http_module,
    NULL
};

char *ctl_module_names[] = {
    "core",
    "conf",
    "events",
    "epoll",
    "http",
    NULL
};

int
ctl_modules_init() 
{
    int i;
    for(i = 0; ctl_modules[i]; i++) {
        ctl_modules[i]->index = i;
        ctl_modules[i]->name = ctl_module_names[i];
    }

    ctl_modules_n = i;

    return CTL_OK;
}

int
ctl_cycle_modules(ctl_cycle_t *cycle)
{
    cycle->modules = (ctl_module_t **) malloc((ctl_modules_n + 1)* sizeof(ctl_module_t **));
    if(cycle->modules == NULL) {
        ctl_perror("Error: malloc memory for cycle->modules\n");
        return CTL_ERROR;
    }

    memset(cycle->modules, 0, (ctl_modules_n + 1)* sizeof(ctl_module_t *));
    memcpy(cycle->modules, ctl_modules, ctl_modules_n * sizeof(ctl_module_t *));

    cycle->module_n = ctl_modules_n;

    return CTL_OK;
}
