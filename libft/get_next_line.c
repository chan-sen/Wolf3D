/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:59:42 by chansen           #+#    #+#             */
/*   Updated: 2016/11/28 18:00:31 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	endingline(const int fd, char **rdstr, char **line)
{
	if (ft_strlen(rdstr[fd]) > 0)
	{
		*line = ft_strdup(rdstr[fd]);
		ft_strdel(&rdstr[fd]);
		return (1);
	}
	else
		return (0);
}

static int	checkread(const int fd, char **rdstr, char *buf, char **line)
{
	char	*temp;
	char	*chr;
	int		ret;

	ret = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((chr = ft_strchr(buf, '\n')) != NULL)
		{
			temp = ft_strjoin(rdstr[fd], buf);
			*line = ft_strsub(temp, 0, ft_strlendif(temp, chr));
			ft_strdel(&temp);
			ft_strdel(&rdstr[fd]);
			rdstr[fd] = ft_strdup(chr + 1);
			return (1);
		}
		temp = ft_strdup(rdstr[fd]);
		ft_strdel(&rdstr[fd]);
		rdstr[fd] = ft_strjoin(temp, buf);
		ft_strdel(&temp);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char		*rdstr[MAX_FD];
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	char			*s;

	if (fd < 0 || BUFF_SIZE < 1 || (-1 == read(fd, buf, 0)))
		return (-1);
	if (rdstr[fd] == NULL)
		rdstr[fd] = ft_strnew(BUFF_SIZE);
	if ((s = ft_strchr(rdstr[fd], '\n')) != NULL)
	{
		tmp = ft_strdup(s + 1);
		*line = ft_strsub(rdstr[fd], 0, ft_strlendif(rdstr[fd], s));
		ft_strdel(&rdstr[fd]);
		rdstr[fd] = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (1);
	}
	if (checkread(fd, rdstr, buf, line) == 1)
		return (1);
	if (endingline(fd, rdstr, line) == 1)
		return (1);
	ft_strdel(&rdstr[fd]);
	*line = NULL;
	return (0);
}
