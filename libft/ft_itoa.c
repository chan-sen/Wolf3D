/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 14:52:29 by chansen           #+#    #+#             */
/*   Updated: 2016/10/01 14:52:30 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		neg;
	int		i;

	num = n;
	neg = 1;
	i = 0;
	if (num < 0)
	{
		num *= -1;
		neg = -1;
	}
	if (!(str = ft_strnew((ft_intdiglen(num) + 1))))
		return (NULL);
	if (num == 0)
		str[i] = '0';
	while (num > 0)
	{
		str[i++] = (char)((num % 10) + '0');
		num = num / 10;
	}
	if (neg < 0)
		str[i] = '-';
	return (ft_strrev(str));
}
