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
	if (!new || !src)
		return (NULL);
	i = -1;
	while (src[++i])
		new[i] = src[i];
	new[i] = '\0';
	return (new);
}

char *ft_strtok_r(char *str, char delim, char **save)
{
	int i;

	i = 0;
	if (!str)
		str = *save;
	while (*str && *str == delim)
		str++;
	if (!*str)
		return (NULL);
	while (*str && *str != delim)
	{
		i++;
		str++;
	}
	*save = str + 1 * (*str != 0);
	*str = 0;
	return (str - i);
}
