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

# include "./../libft/includes"
# include "./../minilibx/mlx.h"

# include <fcntl.h>
# include <math.h>
# include <time.h>

typedef struct	s_;

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
	int			**map;
	t_img		image;
	double		oldtime;
	double		time;
	double		frametime;

}				t_env;


#endif
