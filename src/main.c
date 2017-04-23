

#include "./../includes/wolf3d.h"


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
		color = 0xFFFFFF;
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
		env->p1->color = wall_color(env->map[env->p1->mapx][env->p1->mapy],
			side);


		// draw vert line

		drawline(env, line(point(x, env->p1->dstart), point(x, env->p1->dend)),
			env->p1->color);

		x++;
	}


}


void forward(t_env *env)
{
	if (env->map[(int)(env->p1->posx + env->p1->dx * env->p1->mvspd)]
		[(int)(env->p1->posy)] == 0)
		env->p1->posx += env->p1->dx * env->p1->mvspd;
	if (env->map[(int)(env->p1->posx)]
		[(int)(env->p1->posy + env->p1->dy * env->p1->mvspd)] == 0)
		env->p1->posy += env->p1->dy * env->p1->mvspd;
}

void backward(t_env *env)
{
	if (env->map[(int)(env->p1->posx - env->p1->dx * env->p1->mvspd)]
		[(int)(env->p1->posy)] == 0)
		env->p1->posx -= env->p1->dx * env->p1->mvspd;
	if (env->map[(int)(env->p1->posx)]
		[(int)(env->p1->posy - env->p1->dy * env->p1->mvspd)] == 0)
		env->p1->posy -= env->p1->dy * env->p1->mvspd;
}

void l_rotate(t_env *env)
{
	double	olddx;
	double	oldplanex;

	olddx = env->p1->dx;
	oldplanex = env->p1->plnx;
	env->p1->dx = env->p1->dx * cos(env->p1->rtspd)
		- env->p1->dy * sin(env->p1->rtspd);
	env->p1->dy = olddx * sin(-env->p1->rtspd)
		+ env->p1->dy * cos(env->p1->rtspd);
	env->p1->plnx = env->p1->plnx * cos(env->p1->rtspd)
		- env->p1->plny * sin(env->p1->rtspd);
	env->p1->plny = env->p1->plny * sin(env->p1->rtspd)
		+ env->p1->plny * cos(env->p1->rtspd);
}

void r_rotate(t_env *env)
{
	double	olddx;
	double	oldplanex;

	olddx = env->p1->dx;
	oldplanex = env->p1->plnx;
	env->p1->dx = env->p1->dx * cos(-env->p1->rtspd)
		- env->p1->dy * sin(-env->p1->rtspd);
	env->p1->dy = olddx * sin(-env->p1->rtspd)
		+ env->p1->dy * cos(-env->p1->rtspd);
	env->p1->plnx = env->p1->plnx * cos(-env->p1->rtspd)
		- env->p1->plny * sin(-env->p1->rtspd);
	env->p1->plny = env->p1->plny * sin(-env->p1->rtspd)
		+ env->p1->plny * cos(-env->p1->rtspd);
}

int	wolf_hook(t_env *env)
{
	printf("HAI\n\n\n\n");
	image_to(env);
	printf("ello\n\n");
	draw(env);
	if (env->keys->w)
		forward(env);
	if (env->keys->a)
		l_rotate(env);
	if (env->keys->s)
		backward(env);
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
	return (keys);
}


void checkx(int **map, t_p1 **p1, int x, int y)
{
	if (map[y][x] == 2)
	{
		(*p1)->dx = 0.0;
		(*p1)->plnx = 0.66;
	}
	if (map[y][x] == 3)
	{
		(*p1)->dx = -1.0;
		(*p1)->plnx = 0;
	}
	if (map[y][x] == 4)
	{
		(*p1)->dx = 0.0;
		(*p1)->plnx = -0.66;
	}
	if (map[y][x] == 5)
	{
		(*p1)->dx = 1.0;
		(*p1)->plnx = 0;
	}
}

void			findxstart(int **map, t_p1 **p1, int mx, int my)
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
				checkx(map, p1, x, y);
				((*p1)->posx) = x;
			}
			x++;
		}
		y++;
	}
}

void checky(int **map, t_p1 **p1, int x, int y)
{
	if (map[y][x] == 2)
	{
		(*p1)->dy = -1;
		(*p1)->plny = 0;
	}
	if (map[y][x] == 3)
	{
		(*p1)->dy = 0;
		(*p1)->plny = 0.66;
	}
	if (map[y][x] == 4)
	{
		(*p1)->dy = 1;
		(*p1)->plny = 0;
	}
	if (map[y][x] == 5)
	{
		(*p1)->dy = 0;
		(*p1)->plny = -0.66;
	}
}

void		findystart(int **map, t_p1 **p1, int mx, int my)
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
				checky(map, p1, x, y);
				((*p1)->posy) = y;
			}
			x++;
		}
		y++;
	}
}

t_p1			*player(int **map, int x, int y)
{
	t_p1		*p1;

	p1 = (t_p1 *)malloc(sizeof(t_p1));
	printf("%p\n", p1);
	printf("%p\n", &p1);
	printf("%p\n", p1);
	printf("%p\n", &p1);
	p1->posx = 0;
	p1->posy = 0;
	p1->dx = 0;
	p1->dy = 0;
	p1->plnx = 0;
	p1->plny = 0;
	p1->camx = 0;
	p1->rpx = 0;
	p1->rpy = 0;
	p1->rdx = 0;
	p1->rdy = 0;

	p1->mapx = 0;
	p1->mapy = 0;
	p1->stepx = 0;
	p1->stepy = 0;

	p1->sdx = 0;
	p1->sdy = 0;
	p1->ddx = 0;
	p1->ddy = 0;
	p1->pwd = 0;

	p1->lh = 0;
	p1->dstart = 0;
	p1->dend = 0;


	findxstart(map, &p1, x, y);
	findystart(map, &p1, x, y);
	printf("HI\n");
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
		worldmap[(*y)] = (int *)ft_memalloc(sizeof(int) * 24);
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
	printf("hello%d\n\n", env->map[0][0]);
	env->p1 = player(env->map, env->mx, env->my);
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
