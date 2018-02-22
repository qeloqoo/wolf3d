/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_procedures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:18:22 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/04/10 18:51:57 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		rgb2hex(int r, int g, int b)
{
	r = ((r << 16) & 0xFF0000);
	g = ((g << 8) & 0x00FF00);
	b = (b & 0x000FF);
	return (r | g | b);
}

int		exit_prog(int num)
{
	if (num == 0)
		;
	else if (num == 1)
		ft_putstr("Error reading map\n");
	else if (num == 2)
		ft_putstr("Could not allocate memory\n");
	else if (num == 3)
		ft_putstr("Error while reading map\n");
	else if (num == 4)
		ft_putstr("Not enough or too many parameters specified");
	exit(0);
	return (0);
}

void	reload(t_game *g)
{
	g->img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	g->pxls = mlx_get_data_addr(g->img, &(g->bits_per_pixel), &(g->size_line),
		&(g->endian));
	raycast(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	g->movespeed = g->frametime * 10.0;
	g->rotspeed = g->frametime * 3.0;
	mlx_destroy_image(g->mlx, g->img);
}

int		expose(t_game *g)
{
	reload(g);
	return (0);
}

void	init_game(t_game *g)
{
	g->player.pos = g->level.coord;
	g->player.dir.x = 1.0;
	g->player.dir.y = 0.0;
	g->player.plane.x = 0.0;
	g->player.plane.y = 0.66;
	g->time = 0;
	g->oldtime = 0;
	g->isrunning = 0;
	g->isturning = 0;
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, g->level.name);
	mlx_expose_hook(g->win, expose, g);
	mlx_loop_hook(g->mlx, actions, g);
}
