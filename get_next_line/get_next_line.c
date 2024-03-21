/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.tr >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:52:23 by alaslan           #+#    #+#             */
/*   Updated: 2024/01/21 11:18:23 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_copy_to_stash(char *stash, char *buf)
{
	char	*result;

	result = 0;
	if (!stash && buf)
	{
		result = ft_strdup(buf);
		if (!result)
			return (NULL);
		return (result);
	}
	result = ft_strjoin(stash, buf);
	ft_free_stash(&stash, 0);
	return (result);
}

int	ft_nl_control(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

char	*ft_get_line(char *stash)
{
	int		i;
	char	*s;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i] != '\n')
		i++;
	s = (ft_substr(stash, 0, i + 1));
	if (!s)
		return (NULL);
	return (s);
}

static char	*ft_next_stash(char *stash)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n')
		i++;
	if (stash[i + 1] == '\0')
		return (ft_free_stash(&stash, 0));
	res = ft_substr(stash, i + 1, ft_strlen(stash));
	if (!res)
	{
		ft_free_stash(&stash, 0);
		return (NULL);
	}
	ft_free_stash(&stash, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		ret;
	static char	*stash = NULL;
	char		*line;

	line = 0;
	ret = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stash(&stash, 0));
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret <= 0 && !stash) || ret == -1)
			return (ft_free_stash(&stash, 0));
		buf[ret] = '\0';
		stash = ft_copy_to_stash(stash, buf);
		if (ft_nl_control(stash))
		{
			line = ft_get_line(stash);
			if (!line)
				return (ft_free_stash(&stash, 0));
			return (stash = ft_next_stash(stash), line);
		}
	}
	return (ft_free_stash(&stash, 1));
}
