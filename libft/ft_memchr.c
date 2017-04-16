/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 20:32:19 by chansen           #+#    #+#             */
/*   Updated: 2016/09/23 20:32:20 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*str;
	unsigned char			a;

	a = c;
	str = s;
	while (n-- != 0)
	{
		if (*str == a)
			return ((unsigned *)str);
		str++;
	}
	return (NULL);
}
