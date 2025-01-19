#include "../includes/main.h"

char *mkpath(char *path, char *cmd)
{
	char *out;
	int i;

	out = malloc((size_t)(strlen(path) + strlen(cmd) + 2));
	if (!out)
		return (NULL);
	i = 0;
	while (*path)
		out[i++] = *(path++);
	out[i++] = '/';
	while (*cmd)
		out[i++] = *(cmd++);
	out[i] = 0;
	return (out);
}

char *which(char *cmd, char **envp)
{
	int i;
	char *out;
	char **path;

	i = -1;
	while (!ft_strnstr(envp[++i], "PWD=", 4))
		;
	out = mkpath(envp[i] + 4, cmd);
	if (open(out, O_RDONLY) != -1)
		return (out);
	i = -1;
	while (!ft_strnstr(envp[++i], "PATH=", 5))
		;
	path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (path[++i])
	{
		out = mkpath(path[i], cmd);
		if (open(out, O_RDONLY) != -1)
		{
			// free_arr(path);
			return (out);
		}
	}
	return (NULL);
}

int exec(char *cmd, char **envp)
{
	char **args;

	args = ft_split(cmd, ' ');
	args[0] = which(args[0], envp);
	if (execve(args[0], args, envp) == -1)
		return (-1);
	return (0);
}

int pipex(char *cmd, char **envp)
{
	int fdp[2];
	pid_t pid;

	if (pipe(fdp) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
	{
		close(fdp[0]);
		dup2(fdp[1], STDOUT_FILENO);
		exec(cmd, envp);
	}
	else
	{
		wait(NULL);
		close(fdp[1]);
		dup2(fdp[0], STDIN_FILENO);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	int i;
	int fdin;
	int fdout;

	if (ac < 5)
		return (1);
	fdin = open(av[1], O_RDONLY);
	fdout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fdin, STDIN_FILENO);
	i = 1;
	while (++i < ac - 2)
		pipex(av[i], envp);
	dup2(fdout, STDOUT_FILENO);
	exec(av[ac - 2], envp);
	return (0);
}