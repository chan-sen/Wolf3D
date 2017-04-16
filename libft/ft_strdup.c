/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 04:19:44 by chansen           #+#    #+#             */
/*   Updated: 2016/10/07 15:41:48 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *ns;

	ns = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (ns == NULL)
		return (NULL);
	ft_strcpy(ns, s);
	return (ns);
	free(ns);
}
