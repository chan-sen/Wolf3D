
#include "./../includes/wolf3d.h"

void forward(t_env *env)
{
	if (env->map[(int)(env->p1->posx + env->p1->v->dx * env->p1->mvspd)]
		[(int)(env->p1->posy)] == 0)
		env->p1->posx += env->p1->v->dx * env->p1->mvspd;
	if (env->map[(int)(env->p1->posx)]
		[(int)(env->p1->posy + env->p1->v->dy * env->p1->mvspd)] == 0)
		env->p1->posy += env->p1->v->dy * env->p1->mvspd;
}

void backward(t_env *env)
{
	if (env->map[(int)(env->p1->posx - env->p1->v->dx * env->p1->mvspd)]
		[(int)(env->p1->posy)] == 0)
		env->p1->posx -= env->p1->v->dx * env->p1->mvspd;
	if (env->map[(int)(env->p1->posx)]
		[(int)(env->p1->posy - env->p1->v->dy * env->p1->mvspd)] == 0)
		env->p1->posy -= env->p1->v->dy * env->p1->mvspd;
}

void sliiide(t_env *env)
{
	if (env->keys->q == 1)
	{
		if (env->map[(int)(env->p1->posx - env->p1->v->plnx * env->p1->mvspd)]
			[(int)(env->p1->posy)] == 0)
			env->p1->posx -= env->p1->v->plnx * env->p1->mvspd;
		if (env->map[(int)(env->p1->posx)]
			[(int)(env->p1->posy - env->p1->v->plny * env->p1->mvspd)] == 0)
			env->p1->posy -= env->p1->v->plny * env->p1->mvspd;
	}
	if (env->keys->e == 1)
	{
		if (env->map[(int)(env->p1->posx + env->p1->v->plnx * env->p1->mvspd)]
			[(int)(env->p1->posy)] == 0)
			env->p1->posx += env->p1->v->plnx * env->p1->mvspd;
		if (env->map[(int)(env->p1->posx)]
			[(int)(env->p1->posy + env->p1->v->plny * env->p1->mvspd)] == 0)
			env->p1->posy += env->p1->v->plny * env->p1->mvspd;
	}
}

void l_rotate(t_env *env)
{
	double	olddx;
	double	oldplanex;

	olddx = env->p1->v->dx;

	env->p1->v->dx = env->p1->v->dx * cos(-env->p1->rtspd) - env->p1->v->dy * sin(-env->p1->rtspd);

	env->p1->v->dy = olddx * sin(-env->p1->rtspd) + env->p1->v->dy * cos(-env->p1->rtspd);

	oldplanex = env->p1->v->plnx;

	env->p1->v->plnx = env->p1->v->plnx * cos(-env->p1->rtspd) - env->p1->v->plny * sin(-env->p1->rtspd);

	env->p1->v->plny = oldplanex * sin(-env->p1->rtspd) + env->p1->v->plny * cos(-env->p1->rtspd);
}

void r_rotate(t_env *env)
{
	double	olddx;
	double	oldplanex;

	olddx = env->p1->v->dx;

	env->p1->v->dx = env->p1->v->dx * cos(env->p1->rtspd) - env->p1->v->dy * sin(env->p1->rtspd);

	env->p1->v->dy = olddx * sin(env->p1->rtspd) + env->p1->v->dy * cos(env->p1->rtspd);

	oldplanex = env->p1->v->plnx;

	env->p1->v->plnx = env->p1->v->plnx * cos(env->p1->rtspd) - env->p1->v->plny * sin(env->p1->rtspd);

	env->p1->v->plny = oldplanex * sin(env->p1->rtspd) + env->p1->v->plny * cos(env->p1->rtspd);
}
