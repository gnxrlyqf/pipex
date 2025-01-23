/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:56:54 by mchetoui          #+#    #+#             */
/*   Updated: 2025/01/23 10:58:17 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((*s1 && (*s1 == *s2)) && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	return (*s1 - *s2);
}

char	*mkpath(char *path, char *cmd)
{
	char	*out;
	int		i;

	out = malloc((size_t)(ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!out)
		throw_err(4);
	i = 0;
	while (*path)
		out[i++] = *(path++);
	out[i++] = '/';
	while (*cmd)
		out[i++] = *(cmd++);
	out[i] = 0;
	return (out);
}

char	*is_pwd(char *cmd, char **envp)
{
	char	*out;
	int		i;

	i = -1;
	while (!ft_strnstr(envp[++i], "PWD=", 4))
		;
	out = mkpath(envp[i] + 4, cmd);
	if (!access(out, F_OK | X_OK))
		return (out);
	free(out);
	return (NULL);
}

void	throw_err(int err)
{
	if (err == 1)
		write(2, "Error: Bad syntax.\n", 19);
	if (err == 2)
		write(2, "Error: Input file not found.\n", 30);
	if (err == 3)
		write(2, "Error: Opening output file failed.\n", 35);
	if (err == 4)
		write(2, "Error: Malloc fail.\n", 20);
	if (err == 5)
		write(2, "Error: fork()/pipe() fail.\n", 27);
	if (err == 6)
		write(2, "Error: Command not found.\n", 26);
	exit(err);
}
