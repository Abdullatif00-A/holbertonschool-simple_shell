#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

/* Function Prototypes */
int execute_cmd(char **args, char *line, int last_status);
int handle_exit(char **args, char *line, int last_status);
char **parse_line(char *line);
char *find_command(char *command);
ssize_t _getline(char **lineptr, size_t *n, int fd);

int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *s);
char *_strchr(const char *s, int c);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strtok(char *str, const char *delim);
int is_number(const char *s);
int _atoi(const char *s);

extern char **environ;
int handle_cd(char **args);
#endif /* SHELL_H */

