#include <ctl_core.h>

static ctl_command_t ctl_http__commands[] = {
    {
        "http",
        CTL_HTTP_COMMAND,
        ctl_http_block,
        0,
    },
    ctl_null_command
}

ctl_module_t ctl_http_module = {
    CTL_MODULE_V1,
    ctl_http_commands,
    ctl_create_http_conf
};

static void *
ctl_create_http_conf(ctl_cycle *cycle)
{
    ctl_http_conf_t     *hcf;
    hcf = (ctl_http_conf_t *) malloc(sizeof(ctl_http_conf_t));
    if(ccf == NULL) {
        ctl_perror("Error: malloc memory for ctl_http_conf failed\n");
        return NULL;
    }

    hcf->main_conf = CTL_ADDR_UNSET;
    hcf->srv_conf = CTL_ADDR_UNSET;
    hcf->loc_conf = CTL_ADDR_UNSET;

    return hcf;
}
