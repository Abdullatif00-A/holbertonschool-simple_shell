#include "shell.h"

/**
 * execute_cmd - Executes a command with path resolution
 * @args: Argument vector (command and its arguments)
 * @line: The input line to free on exit
 * @last_status: The status of the last executed command
 * Return: Exit status of the command
 */
int execute_cmd(char **args, char *line, int last_status)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args[0] == NULL)
		return (last_status);

	/* Built-in: exit */
	if (_strcmp(args[0], "exit") == 0)
		return (handle_exit(args, line, last_status));

	/* Built-in: cd */
	if (_strcmp(args[0], "cd") == 0)
		return (handle_cd(args));

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
			perror("./hsh");
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
 * @last_status: Status of last executed command
 * Return: Does not return if successful, exits with status
 */
int handle_exit(char **args, char *line, int last_status)
{
	int status;

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
	else
	{
		status = last_status % 256;
	}

	free(args);
	free(line);
	exit(status);
}

/**
 * handle_cd - Handles the cd built-in command
 * @args: Argument vector
 * Return: 0 on success, 2 on failure
 */
int handle_cd(char **args)
{
	char cwd[1024];
	char *dir, *oldpwd;

	if (args[1] == NULL)
		dir = getenv("HOME");
	else if (_strcmp(args[1], "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (!dir)
		{
			fprintf(stderr, "./hsh: 1: cd: OLDPWD not set\n");
			return (2);
		}
		printf("%s\n", dir);
	}
	else
		dir = args[1];

	if (chdir(dir) != 0)
	{
		fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", dir);
		return (2);
	}

	/* Update PWD and OLDPWD */
	oldpwd = getenv("PWD");
	if (oldpwd)
		setenv("OLDPWD", oldpwd, 1);

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);

	return (0);
}

