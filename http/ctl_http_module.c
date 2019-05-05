#include <ctl_core.h>
#include <ctl_conf_file.h>
#include <ctl_modules.h>
#include <ctl_http.h>

static int ctl_http_block();
static void *ctl_create_http_conf(ctl_cycle_t *);

static ctl_command_t ctl_http_commands[] = {
    {
        "http",
        CTL_CORE_COMMAND,
        ctl_http_block,
        0
    },
    ctl_null_command
};

ctl_module_t ctl_http_module = {
    CTL_MODULE_V1,
    ctl_http_commands,
    CTL_CORE_MODULE,
    ctl_create_http_conf
};

static void *
ctl_create_http_conf(ctl_cycle_t *cycle)
{
    if(cycle == NULL) return NULL;

    ctl_http_conf_t     *hcf;

    hcf = (ctl_http_conf_t *) malloc(sizeof(ctl_http_conf_t));
    if(hcf == NULL) {
        ctl_perror("Error: malloc memory for ctl_http_conf failed\n");
        return NULL;
    }

    hcf->main_conf = CTL_ADDR_UNSET;
    hcf->srv_conf = CTL_ADDR_UNSET;
    hcf->loc_conf = CTL_ADDR_UNSET;

    return hcf;
}

static int
ctl_http_block()
{
    return CTL_OK;
}
