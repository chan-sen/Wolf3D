/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 23:30:26 by chansen           #+#    #+#             */
/*   Updated: 2016/10/01 23:30:28 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	new = ft_strnew(len);
	if (!new)
		return (NULL);
	while (len-- > 0)
	{
		new[i] = str[len];
		i++;
	}
	new[i] = '\0';
	return (new);
}
