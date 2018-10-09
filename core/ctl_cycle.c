#include <ctl_cycle.h>

volatile ctl_cycle_t *ctl_cycle;

ctl_cycle_t *
ctl_init_cycle()
{
    cycle = (ctl_cycle_t *) malloc(sizeof(ctl_cycle_t));
    if(cycle == NULL) {
        ctl_perror("Error: malloc memory for ctl_cycle\n");
        return NULL;
    }

    cycle->root_dir = CTL_NGX_PREFIX;
    cycle->conf_file = CTL_CONF_FILE;

    for(i=0; ctl_modules[i]; i++) {
        if(ctl_modules[i]->create_conf) {
            rv = ctl_modules[i]->create_conf(cycle);
            if(rv != CTL_OK) {
                return NULL;
            }
        }
    }

    return cycle;
}
