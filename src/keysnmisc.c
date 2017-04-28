
#include "./../includes/wolf3d.h"

int		exit_hook(t_env *env)
{
	free(env);
	env = NULL;
	exit(0);
}

int		key_press(int key, t_env *env)
{
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

t_keys	*keyzero(void)
{
	t_keys		*keys;

	keys = (t_keys *)malloc(sizeof(t_keys));
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->q = 0;
	keys->e = 0;
	return (keys);
}

int		**testmap(int fd, int *x, int *y)
{
	int		**worldmap;
	char	**split;
	char	*line;
	int		w;
	int		h;

	w = 36;
	h = 36;
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
