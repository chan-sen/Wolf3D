/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 09:56:04 by chansen           #+#    #+#             */
/*   Updated: 2016/09/25 09:56:05 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*d;
	const unsigned char		*s;
	unsigned char			b;

	d = dst;
	s = src;
	b = c;
	while (n--)
	{
		if (*s == b)
		{
			*(d++) = *(s++);
			return (d);
		}
		*(d++) = *(s++);
	}
	return (0);
}
