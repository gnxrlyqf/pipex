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
			free_arr(path);
			return (out);
		}
	}
	return (NULL);
}

void strappend(char **str1, char *str2)
{
	int i;
	int j;
	char *new;

	new = malloc(strlen(*str1) + strlen(str2) + 1);
	if (!new)
		return ;
	i = -1;
	j = 0;
	while ((*str1)[++i])
		new[j++] = (*str1)[i];
	i = -1;
	while (str2[++i])
		new[j++] = str2[i];
}

char *get_input(char *file)
{
	char *out;
	int fd;
	size_t size;
	ssize_t r;
	char buff[1024];

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	size = 0;
	while (r = read(fd, buff, 1024))
		size += r;
	close(fd);
	fd = open(file, O_RDONLY);
	out = malloc(size + 1);
	size = 0;
	while (1)
	{
		r = -1;
		if (read(fd, buff, 1024))
			break ;
		while ()
	}
}

int main(int ac, char **av, char **envp)
{
	char *input;
}