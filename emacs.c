#include "emacs.h"

void initialize_readline(void)
{
    rl_readline_name = "Yshell";

    rl_attempted_completion_function = yshell_completion;

    rl_instream = stdin;
    rl_outstream = stderr;

    /* Allow conditional parsing of the ~/.inputrc file. */
    rl_readline_name = "Yshell";

    /* Bind up our special shell functions. */
    //rl_add_defun ("shell-expand-line", (Function *)shell_expand_line, -1);
    //rl_bind_key_in_map (CTRL('E'), (Function *)shell_expand_line, emacs_meta_keymap);
}

char **yshell_completion(const char *text, int start, int end)
{
      char **matches;

  matches = (char **)NULL;

//如果输入的是命令，则调用命令补全函数；否则调用文件补全函数
  if (start == 0)
    matches = rl_completion_matches (text, command_generator);

  return (matches);
}

char* command_generator(const char *text, int state)
{
  static int list_index, len;
  char *name;

  if (!state)
    {
      list_index = 0;
      len = strlen (text);
    }

  while (name = commands[list_index].name)
    {
      list_index++;

      if (strncmp (name, text, len) == 0)
        return (dupstr(name));
    }

  return ((char *)NULL);
}



char *dupstr(char *s)
{
    char* p;

    p = malloc(strlen(s) + 1);

    strcpy(p, s);

    return p;
}