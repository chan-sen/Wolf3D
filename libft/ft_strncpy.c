/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 14:00:40 by chansen           #+#    #+#             */
/*   Updated: 2016/09/26 14:00:44 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	max;
	size_t	i;
	char	*d;

	max = len;
	i = 0;
	d = (char *)dst;
	while (i < max && src[i])
	{
		d[i] = src[i];
		i++;
	}
	if (len != 0)
		while (i < len)
		{
			d[i] = '\0';
			i++;
		}
	return (d);
}
