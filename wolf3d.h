/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:31:39 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/04/13 19:40:00 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <time.h>
# include <math.h>

# define WIN_W 1024
# define WIN_H 768

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_PAUSE 49
# define KEY_R 15

# define MOUSE_L 1
# define MOUSE_R 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef	struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_distance
{
	double	x;
	double	y;
}				t_distance;

typedef struct	s_intpair
{
	int	x;
	int	y;
}				t_intpair;

typedef struct	s_level
{
	int			height;
	int			width;
	t_vector	coord;
	char		*name;
	char		**map;
}				t_level;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}				t_player;

typedef	struct	s_wall
{
	double	travdist;
	int		side;
	int		col;
}				t_wall;

typedef struct	s_ray
{
	t_vector	pos;
	t_vector	dir;
	t_distance	sidedist;
	t_distance	deltadist;
	t_intpair	map;
	t_intpair	step;
	t_wall		wall;
	double		camerax;
}				t_ray;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pxls;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	double		time;
	double		oldtime;
	double		frametime;
	double		movespeed;
	double		rotspeed;
	int			isturning;
	int			isrunning;
	t_level		level;
	t_player	player;

}				t_game;

t_level			read_level(char *file);
void			init_game(t_game *g);
void			reload(t_game *g);
void			raycast(t_game *g);
void			move(t_game *g, int i);
void			rotate(t_game *g, int i);
int				kbrd_press(int keycode, t_game *g);
int				kbrd_release(int keycode, t_game *g);
int				rgb2hex(int r, int g, int b);
int				actions(t_game *g);
int				exit_prog(int num);

#endif
