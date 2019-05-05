#include <ctl_core.h>
#include <ctl_conf_file.h>
#include <ctl_modules.h>

int ctl_conf_read_token(ctl_conf_t *);
int ctl_conf_handler(ctl_conf_t *, int);
int ctl_conf_parse(ctl_conf_t *, char *);

ctl_command_t ctl_conf_commands[] = {
    ctl_null_command
};

ctl_module_t ctl_conf_module = {
    CTL_MODULE_V1,
    ctl_conf_commands,
    CTL_CORE_MODULE,
    NULL
};

int
ctl_conf_parse(ctl_conf_t *conf, char *filename)
{
    int fd, rc;
    ctl_conf_file_t *cfile;
    enum {
        parse_file = 0,
        parse_block,
    } type;

    if(filename) {
        fd = open(filename, O_RDONLY, 0);
        if(fd == -1) {
            ctl_perror(" conf file: %s doesn't exist !", filename);
            return CTL_ERROR;
        }
        cfile = &conf->conf_file;

        cfile->fd = fd;
        cfile->name = filename;
        fstat(fd, &cfile->info);
        cfile->start = (char *) malloc(cfile->info.st_size * sizeof(char));
        if(cfile->start == NULL) {
            ctl_perror("alloc space for conf file fails");
            return CTL_ERROR;
        }
        cfile->pos = cfile->start;
        cfile->end = cfile->start + cfile->info.st_size;
        cfile->line = 1;

        if(read(fd, cfile->start, cfile->info.st_size) == -1) {
            ctl_perror("read conf file: %s fails", filename);
            return CTL_ERROR;
        }

        type = parse_file;
    } else {
        type = parse_block;
    }


    // begin to parse the conf file
    while(1) {
        rc = ctl_conf_read_token(conf);

        if(rc == CTL_ERROR) {
            ctl_perror("Error happens while parsing conf file: %s: %d\n", conf->cycle->conf_file, conf->conf_file.line);
            return CTL_ERROR;
        }

        if(rc == CTL_CONF_BLOCK_DONE) {
            continue;
        }

        if(rc == CTL_CONF_FILE_DONE) {
            return CTL_OK;
        }

        rc = ctl_conf_handler(conf, rc);
        if(rc == CTL_ERROR) {
            ctl_perror("Invalid Command: %s !\n", conf->name);
            return CTL_ERROR;
        }

    }
    return CTL_ERROR || type;
}

int
ctl_conf_handler(ctl_conf_t *conf, int last)
{
    ctl_pinfo("command: %s, arg: %s, %d\n", conf->name, conf->arg, last);

    int i, rv;
    char *name = conf->name;
    void *context, **pcontext;
    ctl_command_t *cmd;

    for(i = 0; conf->cycle->modules[i]; i++) {
        cmd = conf->cycle->modules[i]->commands;
        for(/* void */ ; cmd->name; cmd++) {
            if(strcmp(name, cmd->name) != 0) {
                continue;
            }

            if(conf->cycle->modules[i]->type != conf->module_type) {
                continue;
            }

            if(!(conf->cmd_type & cmd->type)) {
                continue;
            }

            context = NULL;
            if(cmd->type & CTL_CORE_COMMAND) {
                context =  ((void **)conf->ctx)[conf->cycle->modules[i]->index];
            } else {
                pcontext = *(void **)((char *)conf->ctx + cmd->offset);
                if(pcontext) {
                    context =  pcontext[conf->cycle->modules[i]->ctx_index];
                }
            }

            rv = cmd->set(conf, context);
            return rv;
        }
    }
    return CTL_ERROR;
}

int
ctl_conf_read_token(ctl_conf_t *conf)
{
    char ch, *start, *last;
    ctl_conf_file_t *cf;
    int wsize, words, vdchar, found, comma, sharp_comment;

    cf = &conf->conf_file;
    conf->name[0] = '\0';
    conf->arg[0]  = '\0';

    words = 0;
    vdchar = 0;
    found = 0;
    comma = 0;
    sharp_comment = 0;
    start = cf->pos;
    last = cf->pos;

    for( ;;) {
        if(cf->pos >= cf->end) return CTL_CONF_FILE_DONE;
        ch = *cf->pos++;
        if((ch >= 'a' && ch <= 'z') 
            || (ch >= 'A' && ch <= 'Z') 
            || (ch >= '0' && ch <= '9')
            || ch == '_' || ch == '.'
            || ch == '/'
          ) {
            if(sharp_comment) continue;
            if(!vdchar) {
                vdchar = 1;
                start = cf->pos - 1;
            }
            last = cf->pos - 1;
            continue;
        }

        if(ch == '{') return CTL_CONF_BLOCK_START;
        if(ch == '}') return CTL_CONF_BLOCK_DONE;

        if(ch == '#') {
            sharp_comment = 1;
            continue;
        }

        if(ch == ';') {
            comma = 1;
            if(words == 2) return CTL_OK;
            if(sharp_comment || !vdchar) continue;
            if(vdchar) found = 1;
        }

        if(ch == ' ' || ch == '\t') {
            if(sharp_comment || comma || !vdchar) continue;
            if(vdchar) found = 1; 
        }

        if(ch == LF || ch == CR) {
            cf->line++;
            if(words == 2) return CTL_OK;
            if(comma) {
                return CTL_OK;
            }
            if(!vdchar) continue;
            return CTL_ERROR;
        }

        if(!found) return CTL_ERROR;

        wsize = last - start + 1;
        if(words == 0) {
            strncpy(conf->name, start, wsize);
            conf->name[wsize] = '\0';
        }
        if(words == 1) {
            strncpy(conf->arg, start, wsize);
            conf->arg[wsize] = '\0';
        }
        words++;
        vdchar = 0;
        found = 0;
    }

    return CTL_ERROR;
}
