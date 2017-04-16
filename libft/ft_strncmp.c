/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 11:17:35 by chansen           #+#    #+#             */
/*   Updated: 2016/09/26 11:17:37 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;
	unsigned		l;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	l = n;
	if (!(*s1 || *s2) || l == 0)
		return (0);
	while ((*us1 || *us2) && l != 0)
	{
		if (*us1 == *us2)
		{
			us1++;
			us2++;
			l--;
		}
		if (*us2 != *us1 && l > 0)
			return (*us1 - *us2);
	}
	return (0);
}
