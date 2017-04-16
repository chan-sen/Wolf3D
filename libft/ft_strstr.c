/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:32:58 by chansen           #+#    #+#             */
/*   Updated: 2016/09/21 14:32:59 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *lil)
{
	const char *b;
	const char *l;

	b = big;
	if (big == lil)
		return ((char *)big);
	while (*big)
	{
		l = lil;
		while (*l != '\0' && (*b == *l))
		{
			++b;
			++l;
		}
		if (*l == '\0')
			return ((char *)big);
		++big;
		b = big;
	}
	return (NULL);
}
