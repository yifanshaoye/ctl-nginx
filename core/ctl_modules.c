
extern ctl_module_t ctl_core_module;
extern ctl_module_t ctl_conf_module;
extern ctl_module_t ctl_epoll_module;
extern ctl_module_t ctl_http_module;

int ctl_modules_n;

ctl_module_t *ctl_modules[] = {
    &ctl_core_module,
    &ctl_conf_module,
    &ctl_epoll_module,
    &ctl_http_module,
    NULL
};

char *ctl_module_names[] = {
    "core",
    "conf",
    "epoll",
    "http",
    NULL
};

int
ctl_modules_init() {
    int i;
    for(i = 0; ctl_modules[i]; i++) {
        ctl_modules[i]->index = i;
        ctl_modules[i]->name = ctl_module_names[i];
    }

    ctl_modules_n = i;
}
