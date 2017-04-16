/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 05:04:35 by chansen           #+#    #+#             */
/*   Updated: 2016/09/25 05:04:37 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = (char*)dst;
	s = (const char*)src;
	if (d <= s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		s += len;
		d += len;
		while (len--)
			*--d = *--s;
	}
	return (dst);
}
