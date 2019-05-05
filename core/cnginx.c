#include <ctl_core.h>
#include <ctl_conf_file.h>
#include <ctl_cycle.h>
#include <ctl_modules.h>

static int ctl_parse_option(int, const char **);
static void ctl_start_master_mode();
static void *ctl_create_core_conf(ctl_cycle_t *);
static int ctl_set_worker_process(ctl_conf_t *, void *);

ctl_cycle_t *ctl_init_cycle();
int ctl_init_signals();

static ctl_command_t ctl_core_commands[] = {
    {
        "worker_process",
        CTL_CORE_COMMAND,
        ctl_set_worker_process,
        0
    },
    ctl_null_command
};

ctl_module_t ctl_core_module = {
    CTL_MODULE_V1,
    ctl_core_commands,
    CTL_CORE_MODULE,
    ctl_create_core_conf
};

static void *
ctl_create_core_conf(ctl_cycle_t *cycle)
{
    if(cycle == NULL) return NULL;

    ctl_core_conf_t *ccf;

    ccf = (ctl_core_conf_t *) malloc(sizeof(ctl_core_conf_t));
    if(ccf == NULL) {
        ctl_perror("Error: malloc memory for ctl_core_conf failed\n");
        return NULL;
    }

    ccf->worker_processes = CTL_CONF_UNSET;
    return ccf;
}

int main(int argc, const char *argv[])
{
    ctl_cycle_t *cycle;

    if(ctl_parse_option(argc, argv) != CTL_OK) {
        return CTL_ERROR;
    }

    if(ctl_modules_init() != CTL_OK) {
        ctl_perror("Error: init molues failed !\n");
        return CTL_ERROR;
    }

    cycle = ctl_init_cycle();
    if(cycle == NULL) {
        ctl_perror("Error: init cycle failed !\n");
        return CTL_ERROR;
    }

    if (ctl_init_signals() != CTL_OK) {
        ctl_perror("Error: init signals failed !\n");
        return CTL_ERROR;
    }

    ctl_start_master_mode();

    return CTL_OK;
}

static int
ctl_parse_option(int argc, const char **argv)
{
    char option;
    int rc = CTL_OK;

    if(argc < 2) {
        return CTL_OK;
    } else if(argc >= 3) {
        ctl_perror("only one option is supported.\n");
        rc = CTL_ERROR;
        goto done;
    } else {
        if(argv[1][0] != '-') {
            ctl_perror("invalid option format, use '-' before an option.\n");
            rc = CTL_ERROR;
            goto done;
        }
        option = argv[1][1];
    }

    switch (option) {
        case 'h':
            ctl_pinfo("-h help\n-v show version\n");
            break;
        case 'v':
            ctl_pinfo("CTL Nginx Version: "CNGINX"\n");
            break;
        default:
            ctl_perror("Invalid Option !");
            rc = CTL_ERROR;
    }

done:

    return rc;
}

int
ctl_init_signals()
{
    return CTL_OK;
}

static void
ctl_start_master_mode()
{

}

static int
ctl_set_worker_process(ctl_conf_t *cf, void *ctx)
{
    
    return CTL_OK &&  cf->module_type && *(int*) ctx;
}
