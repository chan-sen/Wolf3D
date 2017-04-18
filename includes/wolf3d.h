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
	void 					*img;
	char					*data;
	int						height;
	int						width;
	int						sizeline;
	int						bits;
	int						endian;
}								t_img;


typedef struct	s_p1
{
	double				posx;
	double				posy;
	double				dx;
	double				dy;
	double				plnx;
	double				plny;
	double				camx;
	double				rpx;
	double				rpy;
	double				rdx;
	double				rdy;
	int						mapx;
	int						mapy;

}								t_p1;

typedef struct	s_keys
{
	int						spc;
	int						w;
	int						a;
	int						s;
	int						d;
}								t_keys;

typedef struct	s_env
{
	void					*mlx;
	void 					*win;
	t_keys				*keys;
	t_p1					*p1;
	t_map					*map;
	t_img					image;
	double				oldtime;
	double				time;
	double				frametime;

}				t_env;


#endif
