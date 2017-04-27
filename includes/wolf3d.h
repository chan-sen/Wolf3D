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


# include <stdio.h>

# define	WIN_WDT	600
# define	WIN_HGT	600

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_line
{
	double			d;
	int				dx;
	int				dy;
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				xi;
	int				yi;
	int				e;
	int				etmp;
}					t_line;


typedef struct	s_img
{
	void 		*img;
	char		*data;
	int			height;
	int			width;
	int			sizeline;
	int			bits;
	int			endian;
}				t_img;

typedef struct	s_vctrs
{
	double		dx; // direction
	double		dy;
	double		plnx; // plane
	double		plny;
}				t_vctrs;

typedef struct	s_rays
{
	double		rpx; // pos
	double		rpy;
	double		rdx; // dir
	double		rdy;
}				t_rays;

typedef struct	s_dists
{
	int			stepx; // for direction to step in (+1 or -1)
	int			stepy;
	int			hit;
	int			side;
	double		ddx; // delta
	double		ddy;
	double		sdx; // side
	double		sdy;
	double		pwd; // perp wall
}				t_dists;

typedef struct	s_p1
{
	int				mapx; // map int cord for current box
	int				mapy;
	double		posx; // player position
	double		posy;
	double		mvspd; // move and rot speed
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
	void 		*win;
	t_keys		*keys;
	t_p1		*p1;
	t_img		image;
	double		oldtime;
	double		time;
	double		frametime;

}				t_env;

int		**testmap(int fd, int *x, int *y);

void		put_image_pixel(t_img image, int x, int y, int color);
t_point		point(double x, double y);
t_line		line(t_point p1, t_point p2);
void		drawline(t_env *map, t_line line, int color);



#endif
