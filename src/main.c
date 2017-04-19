

#include "./../includes/wolf3d"

void image_to(t_env *env)
{
	env->oldtime = env->time;
	env->time = clock();
	env->frametime = (env->time - env->oldtime) / CLOCKS_PER_SEC;
	mlx_clear_window(env->mlx, env->win);
	if (env->image.img)
		mlx_destroy_image(env->mlx, env->image.img);
	mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
	mlx_string_put(env->mlx, env->win, 0, 0, 0xFFFFFF,
		ft_itoa((int)(1 / env->frametime)));
	free(env->image);
	env->image = make_img(env->mlx);

}

void draw(t_env *env)
{
	int		x;

	x = 0;
	while (x < WIN_WDT);
	{
		env->p1->camx = 2 * x / (double)(WIN_WDT) - 1; // left side of win = -1, cen = 0, right = 1
		env->p1->rpx = env->p1->posx;
		env->p1->rpy = env->p1->posy;
		env->p1->rdx = env->p1->dx + env->p1->plnx * env->p1->camx;
		env->p1->rdy = env->p1->dy + env->p1->plny * env->p1->camx;


		// map box pos
		env->p1->mapx = (int)(env->p1->rpx);
		env->p1->mapy = (int)(env->p1->rpy);


		// length from one x and y side to another x & y side
		env->p1->ddx = sqrt(1 + (env->p1->rdy * env->p1->rdy)
			/ (env->p1->rdx * env->p1->rdx));
		env->p1->ddy = sqrt(1 + (env->p1->rdx * env->p1->rdx)
			/ (env->p1->rdy * env->p1->rdy));

		int		stepx; //what direction to step in (+1 or -1)
		int		stepy;

		int		hit = 0; // wall hit?
		int		side; // which side was hit NorthSouth or EastWest

		// calculate side and initial side dist
// VV

		if (env->p1->rdx < 0)
		{
			env->p1->stepx = -1;
			env->p1->sdx = (env->p1->rpx - env->p1->mapx) * env->p1->ddx;
		}
		else
		{
			env->p1->stepx = 1;
			env->p1->sdx = (env->p1->mapx + 1.0 - env->p1->rpx) * env->p1->ddx;
		}
		if (env->p1->rdy < 0)
		{
			env->p1->stepy = -1;
			env->p1->sdy = (env->p1->rpy - env->p1->mapy) * env->p1->ddy;
		}
		else
		{
			env->p1->stepy = 1;
			env->p1->sdy = (env->p1->mapy + 1.0 - env->p1->rpy) * env->p1->ddy;
		}

		// DDA
		while (hit == 0)
		{
			// jump to next map square, OR in x-dir, OR in y-dir
			if (env->p1->sdx < env->p1->sdy)
			{
				env->p1->sdx += env->p1->ddx;
				env->p1->mapx += env->p1->stepx;
				side = 0;
			}
			else
			{
				env->p1->sdy += env->p1->ddy;
				env->p1->mapy += env->p1->stepy;
				side = 1;
			}
			// check if ray has hit a wall
			if (env->map[env->p1->mapx][env->p1->mapy] == 1)
				hit = 1;
		}

		// distance projected on cam
		if (side == 0)
			env->p1->pwd = (env->p1->mapx - env->p1->rpx + (1 - env->p1->stepx) / 2) / env->p1->rdx;
		else
			env->p1->pwd = (env->p1->mapy - env->p1->rpy + (1 - env->p1->stepy) / 2) / env->p1->rdy;

		// height of line to draw
		env->p1->lh = (int)(WIN_HGT / env->p1->pwd);

		// calc low and high pixel to fill vert line
		env->p1->dstart = (-(env->p1->lh)) / 2 + WIN_HGT / 2;
		if (env->p1->dstart < 0)
			env->p1->dstart = 0;
		env->p1->dend = (env->p1->lh / 2 + WIN_HGT / 2);
		if (env->p1->dend >= WIN_HGT)
			env->p1->dend = WIN_HGT - 1;

		// choose wall color

		x++;
	}
}

int	wolf_hook(t_env *env)
{
	image_to(env);
	draw(env);
	if (env->keys->w)
		forward(env);
	if (env->keys->a)
		l_rotate(env);
	if (env->keys->s)
		backward(env);
	if (env->keys->d)
		r_rotate(env);
	if (env->keys->spc)
		interact(env);
	return (1);
}

int		key_press(int key, t_env *env)
{
	if (key == 49)
		env->keys->spc = 1;
	if (key == 13)
		env->keys->w = 1;
	if (key == 0)
		env->keys->a = 1;
	if (key == 1)
		env->keys->s = 1;
	if (key == 2)
		env->keys->d = 1;
	return (key);
}

int		key_release(int	key, t_env *env)
{
	if (key == 49)
		env->keys->spc = 0;
	if (key == 13)
		env->keys->w = 0;
	if (key == 0)
		env->keys->a = 0;
	if (key == 1)
		env->keys->s = 0;
	if (key == 2)
		env->keys->d = 0;
	return (key);
}

void wolfy(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT, "chansen - Wolf3d");
	mlx_loop_hook(env->mlx, wolf_hook, env);
	mlx_hook(env->win, 2, 0, key_press, env);
	mlx_hook(env->win, 3, 0, key_release, env);
	mlx_hook(env->win, 6, 0, wolf_mouse, env);
	mlx_hook(env->win, 17, 0, exit_hook, env);
	mlx_loop(env->mlx);
}

t_keys	*keyzero(void)
{
	t_keys		*keys;

	keys = (t_keys *)malloc(sizeof(t_keys));
	keys->spc = 0;
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	return (keys);
}

void setdoublepair(double *a, double b, double *c, double d)
{
	(*a) = b;
	(*c) = d;
}

void			findxstart(t_map *map, double *posx, double *dx, double *plnx)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] >= 2 && map[y][x] <= 5)
			{
				if (map[y][x] == 2)
					setdoublepair(*dx, 0.0, *plnx, 0.66);
				if (map[y][x] == 3)
					setdoublepair(*dx, -1.0, *plnx, 0);
				if (map[y][x] == 4)
					setdoublepair(*dx, 0.0, *plnx, -0.66);
				if (map[y][x] == 5)
					setdoublepair(*dx, 1.0, *plnx, 0);
				(*posx) = x;
			}
			x++;
		}
		y++;
	}
}

double		findystart(t_map *map, double *posy, double *dy, double *plny)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] >= 2 && map[y][x] <= 5)
			{
				if (map[y][x] == 2)
					setdoublepair(*dy, -1, *plny, 0);
				if (map[y][x] == 3)
					setdoublepair(*dy, 0, *plny, 0.66);
				if (map[y][x] == 4)
					setdoublepair(*dy, 1, *plny, 0);
				if (map[y][x] == 5)
					setdoublepair(*dy, 0, *plny, -0.66);
				(*posy) = y;
			}
			x++;
		}
		y++;
	}
}

t_p1			*player(t_map *map)
{
	t_p1		*p1;

	p1 = (t_p1 *)malloc(sizeof(t_p1));
	findxstart(map, &p1->posx, &p1->dx, &p1->plnx);
	findystart(map, &p1->posy, &p1->dy, &p1->plny);
	p1->camx = 0;
	p1->rpx = 0;
	p1->rpy = 0;
	p1->rdx = 0;
	p1->rdy = 0;
	return (p1);
}

t_env	*make_env(void)
{
	t_env		*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit_hook(env);
	env->keys = keyzero();
	env->map = testmap();
	env->p1 = player(env->map);
	env->oldtime = 0;
	env->time = 0;
	env->framtime = 0;
	return (env);
}

void wolf3d(void)
{
	t_env	*env;

	env = make_env();
	wolfy(env);
}

int		main(int argc, char **argv)
{
	wolf3d();
	return (0);
}
