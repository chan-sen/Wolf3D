/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:00:00 by chansen           #+#    #+#             */
/*   Updated: 2017/04/26 12:00:00 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

t_vctrs		*vs(void)
{
	t_vctrs	*v;

	v = (t_vctrs *)malloc(sizeof(t_vctrs));
	v->dx = 0.0;
	v->dy = 1.0;
	v->plnx = -0.66;
	v->plny = 0.0;
	return (v);
}

t_rays		*rs(void)
{
	t_rays	*r;

	r = (t_rays *)malloc(sizeof(t_rays));
	r->rpx = 0;
	r->rpy = 0;
	r->rdx = 0;
	r->rdy = 0;
	return (r);
}

t_dists		*ds(void)
{
	t_dists	*d;

	d = (t_dists *)malloc(sizeof(t_dists));
	d->stepx = 0;
	d->stepy = 0;
	d->hit = 0;
	d->side = 0;
	d->sdx = 0;
	d->sdy = 0;
	d->ddx = 0;
	d->ddy = 0;
	d->pwd = 0;
	return (d);
}

t_p1		*player(void)
{
	t_p1	*p1;

	p1 = (t_p1 *)malloc(sizeof(t_p1));
	p1->mapx = 0;
	p1->mapy = 0;
	p1->posx = 18.0;
	p1->posy = 22.0;
	p1->mvspd = 1;
	p1->rtspd = 1;
	p1->v = vs();
	p1->r = rs();
	p1->d = ds();
	return (p1);
}

t_env		*make_env(void)
{
	t_env	*env;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit_hook(env);
	env->keys = keyzero();
	env->map = testmap(open("./maps/map1", O_RDONLY), &x, &y);
	env->winx = 0;
	env->p1 = player();
	env->oldtime = 0;
	env->time = 0;
	env->frametime = 0;
	return (env);
}
