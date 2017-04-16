/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 20:06:12 by chansen           #+#    #+#             */
/*   Updated: 2016/09/25 20:06:14 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lil, size_t len)
{
	int			i;
	size_t		j;

	j = 0;
	if (!*lil)
		return ((char *)big);
	while (big[j] != '\0')
	{
		i = 0;
		while (big[j + i] == lil[i] && len != 0 && i + j < len)
		{
			i++;
			if (lil[i] == '\0')
				return ((char *)big + j);
		}
		j++;
	}
	return (NULL);
}
