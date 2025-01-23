/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:59:19 by mchetoui          #+#    #+#             */
/*   Updated: 2025/01/23 11:00:12 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_list
{
	char			c;
	struct s_list	*next;
}				t_list;

int		contains_nl(char *str);
void	populate_list(t_list **head, char *str);
char	*get_next_line(int fd);
t_list	*add_node(t_list **head, char c);
void	free_list(t_list **head);
char	*make_str(t_list **head, int size);
int		listchr_len(t_list *head);
void	exec(char *cmd, char **envp);
void	pipex(char *cmd, char **envp);
int		here_doc(char *eof);
int		main(int ac, char **av, char **envp);
int		ft_strncmp(char *s1, char *s2, int n);
char	*which(char *cmd, char **envp);
char	*mkpath(char *path, char *cmd);
char	*is_pwd(char *cmd, char **envp);
void	throw_err(int err);
int		wc(const char *str, char c);
char	*ft_strnstr(char *big, char *little, size_t len);
int		ft_strlen(const char *str);
char	*ft_strdup(char *src);
char	*ft_strtok_r(char *str, char delim, char **save);

#endif
