/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:20:23 by mchetoui          #+#    #+#             */
/*   Updated: 2024/11/03 02:37:53 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	count_words(const char *str, char c)
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

char	*ft_strndup(char *str, int start, char c)
{
	int		size;
	char	*new;

	size = 0;
	str += start - 1;
	while (*(++str) && *str != c)
		size++;
	new = malloc(size + 1);
	new += size;
	*new = 0;
	while (size--)
		*(--new) = *(--str);
	return (new);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	int		size;
	char	**arr;

	size = count_words(str, c);
	arr = malloc((size + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		if (str[i] != c)
		{
			arr[j++] = ft_strndup((char *)str, i, c);
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
