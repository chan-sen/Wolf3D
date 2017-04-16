/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:02:31 by chansen           #+#    #+#             */
/*   Updated: 2016/09/29 14:02:32 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned char	*str;
	unsigned		i;
	unsigned		j;

	i = 0;
	j = 0;
	str = (unsigned char *)ft_strnew(len);
	if (!(str))
		return (NULL);
	while (s[i] && i < start)
		i++;
	while (j < len)
	{
		str[j] = (unsigned char)s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return ((char *)str);
}
