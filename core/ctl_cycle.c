#include <ctl_core.h>
#include <ctl_cycle.h>

extern ctl_module_t **ctl_modules;
extern int ctl_modules_n;

int ctl_conf_parse(ctl_conf_t *, char *);

volatile ctl_cycle_t *ctl_cycle;

ctl_cycle_t *
ctl_init_cycle()
{
    int             i;
    void            *rv;
    ctl_conf_t      conf;

    ctl_cycle_t *cycle = (ctl_cycle_t *) malloc(sizeof(ctl_cycle_t));
    if(cycle == NULL) {
        ctl_perror("Error: malloc memory for ctl_cycle\n");
        return NULL;
    }

    cycle->root_dir = CTL_NGX_PREFIX;
    cycle->conf_file = CTL_CONF_FILE;

    void *ctx = (void *) malloc((ctl_modules_n + 1) * sizeof(void *));
    if(ctx == NULL) {
        ctl_perror("Error: malloc memory for cycle->ctx\n");
        return NULL;
    }
    memset(ctx, 0, (ctl_modules_n + 1) * sizeof(void *));

    cycle->conf_ctx = ctx;

    if(ctl_cycle_modules(cycle) != CTL_OK) {
        ctl_perror("Error: init cycle->modules failed\n");
        return NULL;
    }

    for(i=0; cycle->modules[i]; i++) {
        if(cycle->modules[i]->type != CTL_CORE_MODULE) {
            continue;
        }
        if(cycle->modules[i]->create_conf) {
            rv = cycle->modules[i]->create_conf(cycle);
            if(rv == NULL) {
                ctl_perror("Error: create conf for %s \n", cycle->modules[i]->name);
                return NULL;
            }
            cycle->conf_ctx[cycle->modules[i]->index] = rv;
        }
    }

    conf.ctx = cycle->conf_ctx;
    conf.cycle = cycle;
    conf.module_type = CTL_CORE_MODULE;
    conf.cmd_type = CTL_CORE_COMMAND;

    if(ctl_conf_parse(&conf, cycle->conf_file) != CTL_OK) {
        return NULL;
    }

    return cycle;
}
