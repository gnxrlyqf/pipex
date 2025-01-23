#include <pipex.h>

char *which(char *cmd, char **envp)
{
	int i;
	char *out;
	char *path;
	char *dup;
	char *save;

	out = is_pwd(cmd, envp);
	if (out)
		return (out);
	i = -1;
	while (!ft_strnstr(envp[++i], "PATH=", 5))
		;
	dup = ft_strdup(envp[i] + 5);
	if (!dup)
		throw_err(4);
	path = ft_strtok_r(dup, ':', &save);
	while (path)
	{
		out = mkpath(path, cmd);
		if (!access(out, F_OK | X_OK))
			return (out);
		free(out);
		path = ft_strtok_r(NULL, ':', &save);
	}
	return (free(dup), cmd);
}

void exec(char *cmd, char **envp)
{
	char *dup;
	char *save;
	char **args;
	int i;
	
	dup = ft_strdup(cmd);
	if (!dup)
		return ;
	i = wc(cmd, ' ');
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		throw_err(4);
	args[i] = NULL;
	args[0] = which(ft_strtok_r(dup, ' ', &save), envp);
	i = -1;
	while (args[++i])
		args[i + 1] = ft_strtok_r(NULL, ' ', &save);
	execve(args[0], args, envp);
	free(args[0]);
	free(args);
	throw_err(6);
}

void pipex(char *cmd, char **envp)
{
	int fdp[2];
	pid_t pid;

	if (pipe(fdp) == -1)
		throw_err(5);
	pid = fork();
	if (pid == -1)
		throw_err(5);
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
}

int here_doc(char *eof, int ac)
{
	int fd;
	char *str;

	if (!(ac > 5))
		throw_err(1);
	fd = open("/tmp/pipex_heredoc", O_CREAT | O_WRONLY, 0600);
	while (1)
	{
		write(1, "heredoc> ", 9);
		str = get_next_line(STDIN_FILENO);
		if (!str)
			throw_err(4);
		if (ft_strncmp(str, eof, ft_strlen(str) - 1) == 0)
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	close(fd);
	fd = open("/tmp/pipex_heredoc", O_RDONLY, 0600);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("/tmp/pipex_heredoc");
	return (O_TRUNC);
}

int main(int ac, char **av, char **envp)
{
	int i;
	int flags;

	flags = O_WRONLY | O_CREAT | O_APPEND;
	if (ac < 5)
		throw_err(1);
	if (!ft_strcmp(av[1], "here_doc") && *(av[2]))
		flags |= here_doc(av[2], ac);
	else if (dup2(open(av[1], O_RDONLY), STDIN_FILENO) == -1)
		throw_err(2);
	i = 1 + 1 * (flags == (O_WRONLY | O_CREAT | O_APPEND | O_TRUNC));
	while (++i < ac - 2)
		pipex(av[i], envp);
	if (dup2(open(av[ac - 1], flags, 0777), STDOUT_FILENO) == -1)
		throw_err(3);
	exec(av[ac - 2], envp);
	return (0);
}
