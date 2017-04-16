/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:43:33 by chansen           #+#    #+#             */
/*   Updated: 2016/09/23 15:43:34 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return ((char *)s);
	while (s[0] != '\0')
	{
		if (s[0] == (char)c)
			return ((char *)s);
		s++;
	}
	if (s[0] != (char)c)
		return (NULL);
	return ((char *)s);
}
