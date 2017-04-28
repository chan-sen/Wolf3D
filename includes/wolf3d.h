/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 04:02:97 by chansen           #+#    #+#             */
/*   Updated: 2017/04/02 04:02:97 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "./../libft/libft.h"
# include "./../minilibx/mlx.h"

# include <fcntl.h>
# include <math.h>
# include <time.h>

# define WIN_WDT 600
# define WIN_HGT 600

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_line
{
	double		d;
	int			dx;
	int			dy;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			xi;
	int			yi;
	int			e;
	int			etmp;
}				t_line;

typedef struct	s_img
{
	void		*img;
	char		*data;
	int			height;
	int			width;
	int			sizeline;
	int			bits;
	int			endian;
}				t_img;

typedef struct	s_vctrs
{
	double		dx;
	double		dy;
	double		plnx;
	double		plny;
}				t_vctrs;

typedef struct	s_rays
{
	double		rpx;
	double		rpy;
	double		rdx;
	double		rdy;
}				t_rays;

typedef struct	s_dists
{
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		ddx;
	double		ddy;
	double		sdx;
	double		sdy;
	double		pwd;
}				t_dists;

typedef struct	s_p1
{
	int			mapx;
	int			mapy;
	double		posx;
	double		posy;
	double		mvspd;
	double		rtspd;
	t_vctrs		*v;
	t_rays		*r;
	t_dists		*d;
}				t_p1;

typedef struct	s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			q;
	int			e;
}				t_keys;

typedef struct	s_env
{
	int			**map;
	int			winx;
	void		*mlx;
	void		*win;
	t_keys		*keys;
	t_p1		*p1;
	t_img		image;
	double		oldtime;
	double		time;
	double		frametime;
}				t_env;

int				exit_hook(t_env *env);
int				key_press(int key, t_env *env);
int				key_release(int	key, t_env *env);
t_keys			*keyzero(void);
int				**testmap(int fd, int *x, int *y);

t_vctrs			*vs(void);
t_rays			*rs(void);
t_dists			*ds(void);
t_p1			*player(void);
t_env			*make_env(void);

t_img			make_img(void *mlx);
void			put_image_pixel(t_img image, int x, int y, int color);
t_point			point(double x, double y);
t_line			line(t_point p1, t_point p2);
void			drawline(t_env *map, t_line line, int color);

void			forward(t_env *env);
void			backward(t_env *env);
void			sliiide(t_env *env);
void			l_rotate(t_env *env);
void			r_rotate(t_env *env);

int				wall_color(t_env *env, int side);

void			camraydeltadist(t_env *env);
void			stepndist(t_env *env);
void			dda_pwd(t_env *env);
void			drawwallline(t_env *env);
void			woof(t_env *env);

void			image_to(t_env *env);
int				wolf_hook(t_env *env);
void			wolfy(t_env *env);
void			wolf3d(void);

#endif
