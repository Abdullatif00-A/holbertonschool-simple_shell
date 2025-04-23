#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int has_path_env(void);
char **parse_line(char *line);
int execute_cmd(char **args);
extern char **environ;
char *find_command(char *command);
ssize_t _getline(char **lineptr, size_t *n, int fd);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *s);
char *_strchr(const char *s, int c);

#endif
