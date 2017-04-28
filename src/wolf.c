/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:07:00 by chansen           #+#    #+#             */
/*   Updated: 2017/04/26 12:07:00 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

void		camraydeltadist(t_env *env)
{
	double	camx;

	camx = 2 * env->winx / (double)WIN_WDT - 1;
	env->p1->r->rpx = env->p1->posx;
	env->p1->r->rpy = env->p1->posy;
	env->p1->r->rdx = env->p1->v->dx + env->p1->v->plnx * camx;
	env->p1->r->rdy = env->p1->v->dy + env->p1->v->plny * camx;
	env->p1->mapx = (int)(env->p1->r->rpx);
	env->p1->mapy = (int)(env->p1->r->rpy);
	env->p1->d->ddx = sqrt(1 + pow(env->p1->r->rdy, 2)
		/ pow(env->p1->r->rdx, 2));
	env->p1->d->ddy = sqrt(1 + pow(env->p1->r->rdx, 2)
		/ pow(env->p1->r->rdy, 2));
}

void		stepndist(t_env *env)
{
	if (env->p1->r->rdx < 0)
	{
		env->p1->d->stepx = -1;
		env->p1->d->sdx = (env->p1->r->rpx - env->p1->mapx) * env->p1->d->ddx;
	}
	else
	{
		env->p1->d->stepx = 1;
		env->p1->d->sdx = (env->p1->mapx + 1.0 - env->p1->r->rpx)
			* env->p1->d->ddx;
	}
	if (env->p1->r->rdy < 0)
	{
		env->p1->d->stepy = -1;
		env->p1->d->sdy = (env->p1->r->rpy - env->p1->mapy) * env->p1->d->ddy;
	}
	else
	{
		env->p1->d->stepy = 1;
		env->p1->d->sdy = (env->p1->mapy + 1.0 - env->p1->r->rpy)
			* env->p1->d->ddy;
	}
}

void		dda_pwd(t_env *env)
{
	env->p1->d->hit = 0;
	while (env->p1->d->hit == 0)
	{
		if (env->p1->d->sdx < env->p1->d->sdy)
		{
			env->p1->d->sdx += env->p1->d->ddx;
			env->p1->mapx += env->p1->d->stepx;
			env->p1->d->side = 0;
		}
		else
		{
			env->p1->d->sdy += env->p1->d->ddy;
			env->p1->mapy += env->p1->d->stepy;
			env->p1->d->side = 1;
		}
		if (env->map[env->p1->mapx][env->p1->mapy] == 1)
			env->p1->d->hit = 1;
	}
	if (env->p1->d->side == 0)
		env->p1->d->pwd = (env->p1->mapx - env->p1->r->rpx
			+ (1 - env->p1->d->stepx) / 2) / env->p1->r->rdx;
	else
		env->p1->d->pwd = (env->p1->mapy - env->p1->r->rpy
			+ (1 - env->p1->d->stepy) / 2) / env->p1->r->rdy;
}

void		drawwallline(t_env *env)
{
	int		lh;
	int		start;
	int		end;
	int		color;
	int		flor;

	flor = 0x229922;
	lh = (int)(WIN_HGT / env->p1->d->pwd);
	start = (-(lh)) / 2 + WIN_HGT / 2;
	if (start < 0)
		start = 0;
	end = (lh / 2 + WIN_HGT / 2);
	if (end >= WIN_HGT)
		end = WIN_HGT - 1;
	color = wall_color(env, env->p1->d->side);
	drawline(env, line(point(env->winx, start), point(env->winx, end)), color);
	drawline(env, line(point(env->winx, start), point(env->winx, 0)), 0x00FFFF);
	drawline(env, line(point(env->winx, end), point(env->winx, WIN_HGT)), flor);
}

void		woof(t_env *env)
{
	env->winx = 0;
	while (env->winx < WIN_WDT)
	{
		camraydeltadist(env);
		stepndist(env);
		dda_pwd(env);
		drawwallline(env);
		env->winx++;
	}
}
