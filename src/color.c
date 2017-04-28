/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:13:00 by chansen           #+#    #+#             */
/*   Updated: 2017/04/26 12:13:00 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

int		wall_color(t_env *env, int side)
{
	if (side == 1)
	{
		if ((env->p1->d->stepx == -1 && env->p1->d->stepy == -1)
			|| (env->p1->d->stepx == 1 && env->p1->d->stepy == -1))
			return (0x0000FF);
		else
			return (0x992222);
	}
	else
	{
		if ((env->p1->d->stepx == -1 && env->p1->d->stepy == -1)
			|| (env->p1->d->stepx == -1 && env->p1->d->stepy == 1))
			return (0xFFFF00);
		else
			return (0x800080);
	}
}
