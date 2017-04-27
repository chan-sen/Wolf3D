

#include "./../includes/wolf3d.h"


double			findystart(int **map, int mx, int my)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < my)
	{
		while (x < mx)
		{
			if (map[y][x] >= 2 && map[y][x] <= 5)
			{

				return ((double)y);
			}
			x++;
		}
		y++;
	}
	return (0.0);
}


double		findxstart(int **map, int mx, int my)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < my)
	{
		while (x < mx)
		{
			if (map[y][x] >= 2 && map[y][x] <= 5)
				return ((double)x);
			x++;
		}
		y++;
	}
	return (0.0);
}

int		exit_hook(t_env *env)
{
	free(env);
	env = NULL;
	exit(0);
}

t_img		make_img(void *mlx)
{
	t_img	image;

	image.img = mlx_new_image(mlx, WIN_WDT, WIN_HGT);
	image.data = mlx_get_data_addr(image.img, &image.bits,
		&image.sizeline, &image.endian);
	image.height = WIN_HGT;
	image.width = WIN_WDT;
	return (image);
}

void image_to(t_env *env)
{
	printf("supbebe\n");
	env->oldtime = env->time;
	env->time = clock();
	env->frametime = (env->time - env->oldtime) / CLOCKS_PER_SEC;
	printf("timeframed\n");
	mlx_clear_window(env->mlx, env->win);
	printf("windowclear\n");
	if (env->image.img)
		mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
	printf("imageput\n");
	mlx_string_put(env->mlx, env->win, 0, 0, 0xFFFFFF,
		ft_itoa((int)(1 / env->frametime)));
	printf("fps put\n");
	env->image = make_img(env->mlx);
	printf("imagemade\n");
	env->p1->mvspd = (env->frametime * 5.0);
	env->p1->rtspd = (env->frametime * 3.0);
}

int		wall_color(int gridnum, int side)
{
	int	color;

	color = 0;
	if (gridnum == 1)
	{
		color = 0x0000FF;
		if (side == 1)
			color = color / 2;
	}
	return (color);
}


void draw(t_env *env)
{
	int		x;

	x = 0;
	while (x < WIN_WDT)
	{
		printf("\nstartdrawing\n");
		printf("posx: %f, posy: %f\n", env->p1->posx, env->p1->posy);
		printf("env->p1->dy: %f", env->p1->v->dy);

		double		camx;

		camx = 2 * x / (double)WIN_WDT - 1; // left side of win = -1, cen = 0, right = 1
		env->p1->r->rpx = env->p1->posx;
		env->p1->r->rpy = env->p1->posy;
		env->p1->r->rdx = env->p1->v->dx + env->p1->v->plnx * camx;
		env->p1->r->rdy = env->p1->v->dy + env->p1->v->plny * camx;

		printf("mx: %d, my: %d", env->mx, env->my);

		printf("hello new vert line:\nstartposx: %f\nstartposy: %f\nrayposx: %f\nrayposy: %f\nraydirx: %f\nraydiry: %f\n",
			env->p1->posx, env->p1->posy, env->p1->r->rpx, env->p1->r->rpy, env->p1->r->rdx, env->p1->r->rdy);


		// map box pos
		env->p1->mapx = (int)(env->p1->r->rpx);
		env->p1->mapy = (int)(env->p1->r->rpy);


		// length from one x and y side to another x & y side
		env->p1->d->ddx = sqrt(1 + pow(env->p1->r->rdy, 2)
			/ pow(env->p1->r->rdx, 2));
		env->p1->d->ddy = sqrt(1 + pow(env->p1->r->rdx, 2)
			/ pow(env->p1->r->rdy, 2));

		printf("deltadistx: %f, deltadisty: %f\n", env->p1->d->ddx, env->p1->d->ddy);


		int		hit = 0; // wall hit?
		int		side; // which side was hit NorthSouth or EastWest

		// calculate side and initial side dist
		// VV

		if (env->p1->r->rdx < 0)
		{
			env->p1->d->stepx = -1;
			env->p1->d->sdx = (env->p1->r->rpx - env->p1->mapx) * env->p1->d->ddx;
		}
		else
		{
			env->p1->d->stepx = 1;
			env->p1->d->sdx = (env->p1->mapx + 1.0 - env->p1->r->rpx) * env->p1->d->ddx;
		}
		if (env->p1->r->rdy < 0)
		{
			env->p1->d->stepy = -1;
			env->p1->d->sdy = (env->p1->r->rpy - env->p1->mapy) * env->p1->d->ddy;
		}
		else
		{
			env->p1->d->stepy = 1;
			env->p1->d->sdy = (env->p1->mapy + 1.0 - env->p1->r->rpy) * env->p1->d->ddy;
		}

		// DDA
		while (hit == 0)
		{
			// jump to next map square, OR in x-dir, OR in y-dir
			if (env->p1->d->sdx < env->p1->d->sdy)
			{
				env->p1->d->sdx += env->p1->d->ddx;
				env->p1->mapx += env->p1->d->stepx;
				side = 0;
			}
			else
			{
				env->p1->d->sdy += env->p1->d->ddy;
				env->p1->mapy += env->p1->d->stepy;
				side = 1;
			}
			// check if ray has hit a wall
			if (env->map[env->p1->mapx][env->p1->mapy] == 1)
				hit = 1;
		}

		printf("\n~\nsidedistx: %f, sidedisty: %f\n", env->p1->d->sdx, env->p1->d->sdy);
		printf("mapx: %d, mapy: %d\n~\n", env->p1->mapx, env->p1->mapy);

		// distance projected on cam
		if (side == 0)
			env->p1->d->pwd = (env->p1->mapx - env->p1->r->rpx
				+ (1 - env->p1->d->stepx) / 2) / env->p1->r->rdx;
		else
			env->p1->d->pwd = (env->p1->mapy - env->p1->r->rpy
				+ (1 - env->p1->d->stepy) / 2) / env->p1->r->rdy;


		printf("perpendicular wall dis: %f\n", env->p1->d->pwd);


		int		lh;
		int		dstart;
		int		dend;
		int		color;



		// height of line to draw
		lh = (int)(WIN_HGT / env->p1->d->pwd);

		// calc low and high pixel to fill vert line
		dstart = (-(lh)) / 2 + WIN_HGT / 2;
		if (dstart < 0)
			dstart = 0;
		dend = (lh / 2 + WIN_HGT / 2);
		if (dend >= WIN_HGT)
			dend = WIN_HGT - 1;

		// choose wall color
		color = wall_color(env->map[env->p1->mapx][env->p1->mapy], side);


		// draw vert line

		printf("line height : %d \n", lh);
		printf("drawlinefrom(%d, %d) to (%d, %d)\n\n", x, dstart, x, dend);

		drawline(env, line(point(x, dstart), point(x, dend)), color);
		drawline(env, line(point(x, dstart), point(x, 0)), 0x992222); // the ceiling is the roof
		drawline(env, line(point(x, dend), point(x, WIN_HGT)), 0x229922); // the floor is the ground

		x++;
	}


}


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

void sliiide2tharight(t_env *env)
{
	if (env->map[(int)(env->p1->posx + env->p1->v->plnx * env->p1->mvspd)]
		[(int)(env->p1->posy)] == 0)
		env->p1->posx += env->p1->v->plnx * env->p1->mvspd;
	if (env->map[(int)(env->p1->posx)]
		[(int)(env->p1->posy + env->p1->v->plny * env->p1->mvspd)] == 0)
		env->p1->posy += env->p1->v->plny * env->p1->mvspd;
}

void sliiide2thaleft(t_env *env)
{
	if (env->map[(int)(env->p1->posx - env->p1->v->plnx * env->p1->mvspd)]
		[(int)(env->p1->posy)] == 0)
		env->p1->posx -= env->p1->v->plnx * env->p1->mvspd;
	if (env->map[(int)(env->p1->posx)]
		[(int)(env->p1->posy - env->p1->v->plny * env->p1->mvspd)] == 0)
		env->p1->posy -= env->p1->v->plny * env->p1->mvspd;
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

int	wolf_hook(t_env *env)
{
	printf("HAI\n\n\n\n");
	image_to(env);
	printf("ello\n\n");
	draw(env);
	if (env->keys->w)
		forward(env);
	if (env->keys->s)
		backward(env);
	if (env->keys->q)
		sliiide2thaleft(env);
	if (env->keys->e)
		sliiide2tharight(env);
	if (env->keys->a)
		l_rotate(env);
	if (env->keys->d)
		r_rotate(env);
	// if (env->keys->spc)
	// 	interact(env);
	return (1);
}

int		key_press(int key, t_env *env)
{
	printf("key press: %d", key);
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
	if (key == 12)
		env->keys->q = 1;
	if (key == 14)
		env->keys->e = 1;
	return (key);
}

int		key_release(int	key, t_env *env)
{
	if (key == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
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
	if (key == 12)
		env->keys->q = 0;
	if (key == 14)
		env->keys->e = 0;
	return (key);
}

void wolfy(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT, "chansen - Wolf3d");
	printf("heyeyeyeye\n\n");
	printf("key: %d", env->keys->w);
	mlx_loop_hook(env->mlx, wolf_hook, env);
	mlx_hook(env->win, 2, 0, key_press, env);
	mlx_hook(env->win, 3, 0, key_release, env);
	// mlx_hook(env->win, 6, 0, wolf_mouse, env);
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
	keys->q = 0;
	keys->e = 0;
	return (keys);
}

t_vctrs			*vs()
{
	t_vctrs		*v;

	v = (t_vctrs *)malloc(sizeof(t_vctrs));
	v->dx = 1.0;
	v->dy = 0.0;
	v->plnx = 0.0;
	v->plny = 0.66;
	return (v);
}

t_rays			*rs()
{
	t_rays		*r;

	r = (t_rays *)malloc(sizeof(t_rays));
	r->rpx = 0;
	r->rpy = 0;
	r->rdx = 0;
	r->rdy = 0;
	return (r);
}

t_dists			*ds()
{
	t_dists		*d;

	d = (t_dists *)malloc(sizeof(t_dists));
	d->stepx = 0;
	d->stepy = 0;
	d->sdx = 0;
	d->sdy = 0;
	d->ddx = 0;
	d->ddy = 0;
	d->pwd = 0.0;
	return (d);
}

t_p1			*player()
{
	t_p1		*p1;

	p1 = (t_p1 *)malloc(sizeof(t_p1));

	p1->mapx = 0;
	p1->mapy = 0;
	p1->posx = 3.0;
	p1->posy = 3.0;
	p1->mvspd = 1;
	p1->rtspd = 1;

	p1->v = vs();
	p1->r = rs();
	p1->d = ds();

	return (p1);
}

int		**testmap(int fd, int *x, int *y)
{
	int		**worldmap;
	char	**split;
	char	*line;
	int		w;
	int		h;

	w = 12;
	h = 12;
	worldmap = (int **)ft_memalloc(sizeof(int *) * h);
	while (get_next_line(fd, &line))
	{
		(*x) = 0;
		split = ft_strsplit(line, ' ');
		worldmap[(*y)] = (int *)ft_memalloc(sizeof(int) * w);
		while (split[(*x)] != '\0')
		{
			worldmap[(*y)][(*x)]= ft_atoi(split[(*x)]);
			(*x)++;
		}
		(*y)++;
	}
	return (worldmap);
}


t_env	*make_env(void)
{
	t_env		*env;
	int			x;
	int			y;

	x = 0;
	y = 0;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit_hook(env);
	env->keys = keyzero();
	env->map = testmap(open("./maps/map1", O_RDONLY), &x, &y);
	env->mx = x;
	env->my = y;
	env->p1 = player();
	env->oldtime = 0;
	env->time = 0;
	env->frametime = 0;
	return (env);
}

void wolf3d(void)
{
	t_env	*env;

	env = make_env();
	wolfy(env);
}

int		main()
{
	wolf3d();
	return (0);
}
