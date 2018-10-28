#include <ctl_core.h>
#include <ctl_cycle.h>
#include <ctl_modules.h>

extern ctl_module_t **ctl_modules;
extern int ctl_modules_n;

volatile ctl_cycle_t *ctl_cycle;

ctl_cycle_t *
ctl_init_cycle()
{
    int i;
    void *rv;
    ctl_cycle_t *cycle = (ctl_cycle_t *) malloc(sizeof(ctl_cycle_t));
    if(cycle == NULL) {
        ctl_perror("Error: malloc memory for ctl_cycle\n");
        return NULL;
    }

    cycle->root_dir = CTL_NGX_PREFIX;
    cycle->conf_file = CTL_CONF_FILE;

    void *ctx = (void *) malloc(ctl_modules_n * sizeof(void *));
    if(ctx == NULL) {
        ctl_perror("Error: malloc memory for cycle->ctx\n");
        return NULL;
    }

    cycle->conf_ctx = ctx;

    for(i=0; ctl_modules[i]; i++) {
        if(ctl_modules[i]->create_conf) {
            rv = ctl_modules[i]->create_conf(cycle);
            if(rv == NULL) {
                return NULL;
            }
            cycle->conf_ctx[ctl_modules[i]->index] = rv;
        }
    }

    return cycle;
}
