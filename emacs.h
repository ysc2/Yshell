#ifndef __EMACS_H__
#define __EMACS_H__

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <readline/rlstdc.h>
#include <readline/keymaps.h>
#include <readline/tilde.h>
#include <readline/chardefs.h>
#include <readline/rlconf.h>
#include <readline/rltypedefs.h>

#include "builtin.h"

void initialize_readline(void);//初始化readline

char **yshell_completion(const char *text, int start, int end);

char* command_generator(const char *text, int state);

char *dupstr(char *s);
#endif /* __EMACS_H__ */