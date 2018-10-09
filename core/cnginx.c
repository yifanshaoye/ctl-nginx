#include <ctl_core.h>

static int ctl_parse_option(int, const char **);
static void ctl_start_master_mode();

ctl_cycle_t *ctl_init_cycle();
int ctl_init_signals();

int main(int argc, const char *argv[])
{
    ctl_cycle_t *cycle;

    if(ctl_parse_option(argc, argv) != CTL_OK) {
        return CTL_ERROR;
    }

    /*
    ctl_cyle = (ctl_cycle_t *) malloc(sizeof(ctl_cycle_t));
    if(ctl_cycle == NULL) {
        ctl_perror("Error: malloc ctl_cyle !\n");
        return -1;
    }*/

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
ctl_parse_option(int argc, const char **)
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
            ctl_pinfo("CTL Nginx Version: ",CNGINX,"\n");
            break;
        default:
            ctl_perror("Invalid Option !");
            rc = CTL_ERROR;
    }

done:

    return rc;
}

static void
ctl_start_master_mode()
{

}
