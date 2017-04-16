/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:02:11 by chansen           #+#    #+#             */
/*   Updated: 2017/02/28 21:16:18 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	unsigned	i;
	unsigned	a;
	unsigned	b;

	i = 0;
	a = 0;
	b = 0;
	str = ft_strnew(((ft_strlen((char *)s1)) + (ft_strlen((char *)s2))));
	if (!str)
		return (NULL);
	while (s1[a])
		str[i++] = s1[a++];
	while (s2[b])
		str[i++] = s2[b++];
	return (str);
}
