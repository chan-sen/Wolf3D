

#include "./../includes/wolf3d"

void wolfy(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT, "chansen - Wolf3d");

	if ()
	mlx_loop_hook(env->mlx, wolf_hook, env);

	mlx_hook(env->win, 17, 0, exit_hook, env);
	mlx_loop(env->mlx);
}

void wolf3d(void)
{
	t_env	*env;

	make_env(env);
	wolfy(env);
}

int		main(int argc, char **argv)
{
	wolf3d();
	return (0);
}
