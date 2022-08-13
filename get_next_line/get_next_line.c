/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truthe <truthe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:20:56 by truthe            #+#    #+#             */
/*   Updated: 2021/11/16 16:21:57 by truthe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ch_n(char **str, char **stat)
{
	char	*pointers;
	char	*tmp;

	if (ft_strchr(*str, '\n'))
	{
		pointers = ft_strchr(*str, '\n');
		pointers++;
		tmp = *stat;
		*stat = ft_strdup(pointers);
		if (tmp)
			free(tmp);
		*pointers = '\0';
	}
	return (*stat);
}

char	*ch_remainder(char	**str, char **stat)
{
	if (*stat)
	{
		free(*str);
		*str = ft_strdup(*stat);
		free(*stat);
		*stat = 0;
	}
	return (*str);
}

char	*ft_read(int fd, char *buf)
{
	int			k;
	char		*str;
	static char	*stat;
	char		*tmp;

	k = 1;
	str = ft_strdup("");
	str = ch_remainder(&str, &stat);
	while (k > 0 && !ft_strchr(str, '\n'))
	{
		k = read (fd, buf, BUFFER_SIZE);
		if (k < 0)
			break ;
		buf[k] = '\0';
		tmp = str;
		str = ft_strjoin (str, buf);
		free(tmp);
	}
	stat = ch_n(&str, &stat);
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	char	*str;
	char	*buf;

	if ((fd < 0) || (fd > 256) || (BUFFER_SIZE < 1))
		return (0);
	buf = malloc (BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	str = ft_read(fd, buf);
	if (!*str)
	{
		free(str);
		str = 0;
		return (NULL);
	}
	return (str);
}
