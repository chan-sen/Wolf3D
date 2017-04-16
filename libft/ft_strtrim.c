/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 14:52:01 by chansen           #+#    #+#             */
/*   Updated: 2016/10/01 14:52:02 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = ft_strlen(s);
	while (s[n - 1] == ' ' || s[n - 1] == '\t' || s[n - 1] == '\n')
		n--;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
	{
		i++;
		n--;
	}
	if (n <= 0)
		n = 0;
	if (!(str = ft_strnew((size_t)(n))))
		return (NULL);
	s = s + i;
	i = 0;
	while (i < n)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}
