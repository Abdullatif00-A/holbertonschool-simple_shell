#include "shell.h"

/**
 * execute_cmd - Executes a command with path resolution
 * @args: Argument vector (command and its arguments)
 * @line: The input line to free on exit
 * Return: 127 if command not found, 0 otherwise
 */
int execute_cmd(char **args, char *line)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args[0] == NULL)
		return (0);

	/* Built-in: exit */
	if (_strcmp(args[0], "exit") == 0)
		return (handle_exit(args, line));

	/* Built-in: env */
	if (_strcmp(args[0], "env") == 0)
	{
		int i = 0;
		while (environ[i])
			printf("%s\n", environ[i++]);
		return (0);
	}

	/* Check if command contains '/' */
	if (_strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
			cmd_path = _strdup(args[0]);
		else
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			return (127);
		}
	}
	else
	{
		cmd_path = find_command(args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			return (127);
		}
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			free(cmd_path);
			exit(127);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		if (waitpid(pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
			{
				int exit_status = WEXITSTATUS(status);
				free(cmd_path);
				return (exit_status);
			}
		}
		free(cmd_path);
		return (2);
	}
	return (0);
}

/**
 * handle_exit - Handles the exit built-in with optional status
 * @args: Argument vector
 * @line: The input line to free before exiting
 * Return: 2 if error, does not return if successful
 */

int handle_exit(char **args, char *line)
{
	int status = 0;

	if (args[1] != NULL)
	{
		if (!is_number(args[1]))
		{
			fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", args[1]);
			free(args);
			free(line);
			exit(2);
		}
		status = _atoi(args[1]) % 256;
	}
	free(args);
	free(line);
	exit(status);
}


