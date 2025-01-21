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

void free_arr(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char *which(char *cmd, char **envp)
{
	int i;
	char *out;
	char *path;

	i = -1;
	while (!ft_strnstr(envp[++i], "PWD=", 4))
		;
	out = mkpath(envp[i] + 4, cmd);
	if (open(out, O_RDONLY) != -1)
		return (out);
	free(out);
	i = -1;
	while (!ft_strnstr(envp[++i], "PATH=", 5))
		;
	path = ft_strtok(ft_strdup(envp[i] + 5), ':');
	while (path)
	{
		out = mkpath(path, cmd);
		if (open(out, O_RDONLY) != -1)
			return (out);
		free(out);
		path = ft_strtok(NULL, ':');
	}
	return (cmd);
}

void exec(char *cmd, char **envp)
{
	char *dup;
	char **args;
	int i;
	
	dup = ft_strdup(cmd);
	if (!dup)
		return ;
	i = count_words(cmd, ' ');
	args = malloc(sizeof(char *) * (i + 1));
	args[i] = NULL;
	args[0] = which(ft_strtok(dup, ' '), envp);
	i = -1;
	while (args[++i] != NULL)
		args[i + 1] = ft_strtok(NULL, ' ');
	execve(args[0], args, envp);
	free(args[0]);
	free(args);
	perror("Command not found");
	exit(1);
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
	if (fdin == -1 || fdout == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	dup2(fdin, STDIN_FILENO);
	i = 1;
	while (++i < ac - 2)
		pipex(av[i], envp);
	dup2(fdout, STDOUT_FILENO);
	exec(av[ac - 2], envp);
	return (0);
}
