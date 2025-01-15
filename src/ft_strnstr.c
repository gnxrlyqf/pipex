/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:32:07 by mchetoui          #+#    #+#             */
/*   Updated: 2024/11/03 02:39:01 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*temp;

	if (!big || !little || !*little)
		return (big);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == *little)
		{
			j = i;
			temp = little;
			while (*temp && *temp == big[j] && j++ < len)
				temp++;
			if (!*temp)
				return (big + i);
		}
		i++;
	}
	return (NULL);
}
