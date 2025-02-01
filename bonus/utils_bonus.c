/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:56:54 by mchetoui          #+#    #+#             */
/*   Updated: 2025/01/23 10:58:17 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	wc(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*mkpath(char *path, char *cmd)
{
	char	*out;
	int		i;

	if (*cmd == '/')
		return (NULL);
	out = malloc((size_t)(ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!out)
		throw_err(3, NULL);
	i = 0;
	while (*path)
		out[i++] = *(path++);
	out[i++] = '/';
	while (*cmd)
		out[i++] = *(cmd++);
	out[i] = 0;
	return (out);
}

char	*check_cwd(char *cmd, char **envp)
{
	char	*out;
	int		i;

	i = -1;
	while (ft_strncmp(envp[++i], "PWD=", 4))
		;
	if (!envp[i])
		throw_err(6, cmd);
	out = mkpath(envp[i] + 4, cmd);
	if (!access(out, F_OK | X_OK))
		return (out);
	free(out);
	return (cmd);
}

int	open_files(char *infile, char *outfile, int flags)
{
	int	fd1;
	int	fd2;

	if (infile)
	{
		fd1 = open(infile, O_RDONLY);
		if (fd1 == -1)
		{
			throw_err(2, infile);
			fd1 = open("/dev/null", O_RDONLY);
		}
		dup2(fd1, STDIN_FILENO);
	}
	fd2 = open(outfile, flags, 0600);
	if (fd2 == -1)
	{
		throw_err(2, outfile);
		fd2 = open("/dev/null", O_RDONLY);
	}
	return (fd2);
}

void	throw_err(int err, char *str)
{
	if (err == 1)
		write(2, "Bad syntax.\n", 12);
	if (err == 2)
	{
		write(2, "open(): ", 8);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	if (err == 3)
		write(2, "Malloc fail.\n", 13);
	if (err == 4)
		perror(str);
	if (err == 5)
	{
		write(2, "execve(): Command not found: ", 29);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	if (err == 1 || err == 3 || err == 4 || err == 5)
		exit (err);
}
