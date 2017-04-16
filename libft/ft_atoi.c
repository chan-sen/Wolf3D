/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:46:27 by chansen           #+#    #+#             */
/*   Updated: 2016/10/11 14:54:12 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		nbr;
	int		neg;

	i = 0;
	nbr = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	if (str[i] <= ' ')
		return (nbr);
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] % '0');
		i++;
	}
	return (nbr *= neg);
}
