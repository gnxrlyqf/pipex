#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_list
{
	char			c;
	struct s_list	*next;
}				t_list;

char	*ft_strnstr(char *big, char *little, size_t len);
char	**ft_split(char const *str, char c);
int		contains_nl(char *str);
void	populate_list(t_list **head, char *str);
char	*get_next_line(int fd);
t_list	*add_node(t_list **head, char c);
void	free_list(t_list **head);
char	*make_str(t_list **head, int size);
int		listchr_len(t_list *head);


#endif