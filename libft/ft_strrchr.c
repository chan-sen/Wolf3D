/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 22:41:52 by chansen           #+#    #+#             */
/*   Updated: 2016/09/23 22:41:53 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = ft_strlen(s);
	if (s == NULL)
		return ((char *)s);
	while (str[0] != '\0')
		str++;
	if (c == 0)
		return (str);
	while (i != 0)
	{
		i--;
		str--;
		if (s[i] == (char)c)
			return (str);
	}
	return (NULL);
}
