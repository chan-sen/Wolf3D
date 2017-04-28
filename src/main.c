

#include "./../includes/wolf3d.h"

void image_to(t_env *env)
{
	env->oldtime = env->time;
	env->time = clock();
	env->frametime = (env->time - env->oldtime) / CLOCKS_PER_SEC;
	mlx_clear_window(env->mlx, env->win);
	if (env->image.img)
		mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
	mlx_string_put(env->mlx, env->win, 0, 0, 0xFFFFFF,
		ft_itoa((int)(1 / env->frametime)));
	env->image = make_img(env->mlx);
	env->p1->mvspd = (env->frametime * 6.0);
	env->p1->rtspd = (env->frametime * 3.0);
}

int	wolf_hook(t_env *env)
{
	image_to(env);
	woof(env);
	if (env->keys->w)
		forward(env);
	if (env->keys->s)
		backward(env);
	sliiide(env);
	if (env->keys->a)
		l_rotate(env);
	if (env->keys->d)
		r_rotate(env);
	return (1);
}

void wolfy(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT, "chansen - Wolf3d");
	mlx_loop_hook(env->mlx, wolf_hook, env);
	mlx_hook(env->win, 2, 0, key_press, env);
	mlx_hook(env->win, 3, 0, key_release, env);
	mlx_hook(env->win, 17, 0, exit_hook, env);
	mlx_loop(env->mlx);
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
