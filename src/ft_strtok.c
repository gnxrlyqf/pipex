#include "../includes/main.h"

char *ft_strtok(char *str, char delim)
{
	int i;
	static char *iter;

	i = 0;
	if (!str)
		str = iter;
	while (*str && *str == delim)
		str++;
	if (!*str)
		return (NULL);
	while (*str && *str != delim)
	{
		i++;
		str++;
	}
	iter = str + 1 * (*str != 0);
	*str = 0;
	return (str - i);
}
