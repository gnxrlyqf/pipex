/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:56:17 by mchetoui          #+#    #+#             */
/*   Updated: 2025/01/23 10:56:35 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	ft_strncmp(char *s1, char *s2, int n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
		return (0);
	return (*s1 - *s2);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*new;

	new = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!src || !new)
		return (NULL);
	i = -1;
	while (src[++i])
		new[i] = src[i];
	new[i] = '\0';
	return (new);
}

char	*ft_strchr(char *str, int c)
{
	while (*str && *str != c)
		str++;
	if (!*str && c)
		return (NULL);
	return (str);
}

char	*ft_strtok_r(char *str, char *delims, char **save)
{
	int	i;

	i = 0;
	if (!str)
		str = *save;
	while (*str && ft_strchr(delims, *str))
		str++;
	if (!*str)
		return (NULL);
	while (*str && !ft_strchr(delims, *str))
	{
		i++;
		str++;
	}
	*save = str + 1 * (*str != 0);
	*str = 0;
	return (str - i);
}
