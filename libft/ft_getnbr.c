/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:25:41 by chansen           #+#    #+#             */
/*   Updated: 2017/02/28 10:46:05 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int		gethexnbr(char *str, int *i)
{
	int			nbr;

	nbr = 0;
	while (str[(*i)] != '\0')
	{
		nbr *= 16;
		if (ft_isdigit(str[(*i)]) == 1)
			nbr += (str[(*i)++] - 48);
		else if (str[(*i)] >= 'a' && str[(*i)] <= 'f')
			nbr += (str[(*i)++] - 87);
		else if (str[(*i)] >= 'A' && str[(*i)] <= 'F')
			nbr += (str[(*i)++] - 55);
	}
	return (nbr);
}

static int		getbinnbr(char *str, int *i)
{
	int			nbr;

	nbr = 0;
	while (ft_isbinary(str[(*i)]) == 1)
	{
		nbr *= 2;
		nbr += (str[(*i)] - 48);
	}
	return (nbr);
}

int				ft_getnbr(char *str, int *i)
{
	int			nbr;

	nbr = 0;
	if (str[(*i)] == '0' && str[(*i) + 1] == 'x' &&
		ft_ishexascii(str[(*i) + 2]))
	{
		(*i)++;
		(*i)++;
		return (gethexnbr(str, i));
	}
	if (str[(*i)] == '0' && str[(*i) + 1] == 'b' && ft_isbinary(str[(*i) + 2]))
	{
		(*i)++;
		(*i)++;
		return (getbinnbr(str, i));
	}
	while (ft_isdigit(str[(*i)]) == 1)
	{
		nbr *= 10;
		nbr += (str[(*i)++] - 48);
	}
	return (nbr);
}
