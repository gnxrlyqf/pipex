/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:18:46 by mchetoui          #+#    #+#             */
/*   Updated: 2024/11/23 03:45:37 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

t_list	*add_node(t_list **head, char c)
{
	t_list	*curr;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (new);
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	return (new);
}

void	free_list(t_list **head)
{
	t_list	*current;
	t_list	*temp;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}

char	*make_str(t_list **head, int size)
{
	char	*new;
	t_list	*curr;
	t_list	*temp;
	int		i;

	new = malloc(sizeof(char) * (size + 1));
	if (!new || !*head || !size)
		return (free(new), NULL);
	new[size] = 0;
	i = size;
	curr = *head;
	while (curr && i)
	{
		*(new++) = curr->c;
		i--;
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	*head = curr;
	return (new - size);
}

int	listchr_len(t_list *head)
{
	int		len;
	t_list	*curr;

	curr = head;
	len = 0;
	while (curr && curr->c != '\n')
	{
		len++;
		curr = curr->next;
	}
	if (curr)
		len++;
	return (len);
}
