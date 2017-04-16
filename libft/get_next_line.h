/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:59:00 by chansen           #+#    #+#             */
/*   Updated: 2017/01/30 14:27:55 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "./libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define BUFF_SIZE	42

# define MAX_FD		2147483647

int		get_next_line(const int fd, char **line);

#endif
