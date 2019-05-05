#include <ctl_core.h>
#include <ctl_conf_file.h>
#include <ctl_modules.h>

static int ctl_events_block();

static ctl_command_t ctl_events_commands[] = {
    {
        "events",
        CTL_CORE_COMMAND,
        ctl_events_block,
        0
    },
    ctl_null_command
};

ctl_module_t ctl_events_module = {
    CTL_MODULE_V1,
    ctl_events_commands,
    CTL_CORE_MODULE,
    NULL
};

static int
//ctl_events_block(ctl_cycle_t *cycle)
ctl_events_block()
{
    return CTL_OK;
}
