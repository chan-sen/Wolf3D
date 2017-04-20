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
	float			x;
	float			y;
}					t_point;

typedef struct		s_line
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	float			d;
	int				dx;
	int				dy;
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


typedef struct	s_p1
{
	double		posx; // player position
	double		posy;
	double		dx; // direction vector
	double		dy;
	double		plnx; // plane vector
	double		plny;
	double		camx; // x cord in cam space for vert line drawing
	double		rpx; // ray position
	double		rpy;
	double		rdx; // ray dir
	double		rdy;


	int			mapx; // map int cord for current box
	int			mapy;
	int			stepx; // for direction to step in (+1 or -1)
	int			stepy;
	double		sdx; // side dist
	double		sdy;
	double		ddx; // delta dist
	double		ddy;
	double		pwd; // perpendicular wall dist

	int			lh; // line height
	int			dstart;
	int			dend;

	int			color;

	// move and rot speed
	double		mvspd;
	double		rtspd;

}				t_p1;

typedef struct	s_keys
{
	int			spc;
	int			w;
	int			a;
	int			s;
	int			d;
}				t_keys;

typedef struct	s_env
{
	void		*mlx;
	void 		*win;
	t_keys		*keys;
	t_p1		*p1;
	int		**map;
	t_img		image;
	double		oldtime;
	double		time;
	double		frametime;

}				t_env;

int		**testmap(int fd);

void		put_image_pixel(t_img image, int x, int y, int color);
t_point		point(float x, float y);
t_line		line(t_point p1, t_point p2);
void		drawline(t_env *map, t_line line, int color);



#endif
