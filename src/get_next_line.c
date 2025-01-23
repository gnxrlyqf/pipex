/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:25:40 by mchetoui          #+#    #+#             */
/*   Updated: 2024/11/24 18:37:06 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	contains_nl(char *str)
{
	while (*str)
		if (*(str++) == '\n')
			return (1);
	return (0);
}

void populate_list(t_list **head, char *str)
{
	while (*str)
		if (!add_node(head, *(str++)))
			free_list(head);
}

char	*get_next_line(int fd)
{
	char			*str;
	ssize_t			size;
	static t_list	*head;

	str = malloc(1024);
	if (fd < 0 || !str)
		return (free(str), NULL);
	while (1)
	{
		size = read(fd, str, size);
		if (size < 0)
			return (free(str), NULL);
		str[size] = 0;
		populate_list(&head, str);
		if (contains_nl(str) || size <= 0)
			break ;
	}
	free(str);
	return (make_str(&head, listchr_len(head)));
}
