
CC = gcc
CFLAGS = -pipe -W -Wall -Wpointer-arith -Wunused -Werror -g -O0
LINK = $(CC)

ALL_INCS = -I core \
    -I event \
    -I http 

ALL_DEPS = core/ctl_core.h \
	core/ctl_conf_file.h \
	core/ctl_cycle.h \
	core/ctl_modules.h \
	event/ctl_epoll.h \
	http/ctl_http.h

build: objs/cnginx

objs/cnginx: objs/core/cnginx.o \
	objs/core/ctl_conf.file.o \
	objs/core/ctl_cycle.o \
	objs/core/ctl_modules.o \
	objs/event/ctl_events_module.o \
	objs/event/ctl_epoll_module.o \
	objs/http/ctl_http_module.o

	$(LINK) -o objs/cnginx \
	objs/core/cnginx.o \
	objs/core/ctl_conf.file.o \
	objs/core/ctl_cycle.o \
	objs/core/ctl_modules.o \
	objs/event/ctl_events_module.o \
	objs/event/ctl_epoll_module.o \
    objs/http/ctl_http_module.o

objs/core/cnginx.o: core/cnginx.c $(ALL_DEPS)
	test -d objs/core || mkdir -p objs/core
	$(CC) -c $(CFLAGS) $(ALL_INCS) -o $@ $<

objs/core/ctl_conf.file.o: core/ctl_conf_file.c $(ALL_DEPS)
	$(CC) -c $(CFLAGS) $(ALL_INCS) -o $@ $<

objs/core/ctl_cycle.o: core/ctl_cycle.c $(ALL_DEPS)
	$(CC) -c $(CFLAGS) $(ALL_INCS) -o $@ $<

objs/core/ctl_modules.o: core/ctl_modules.c $(ALL_DEPS)
	$(CC) -c $(CFLAGS) $(ALL_INCS) -o $@ $<

objs/event/ctl_events_module.o: event/ctl_events_module.c $(ALL_DEPS)
	test -d objs/event || mkdir -p objs/event
	$(CC) -c $(CFLAGS) $(ALL_INCS) -o $@ $<

objs/event/ctl_epoll_module.o: event/ctl_epoll_module.c $(ALL_DEPS)
	$(CC) -c $(CFLAGS) $(ALL_INCS) -o $@ $<

objs/http/ctl_http_module.o: http/ctl_http_module.c $(ALL_DEPS)
	test -d objs/http || mkdir -p objs/http
	$(CC) -c $(CFLAGS) $(ALL_INCS) -o $@ $<
