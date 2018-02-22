/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:58:36 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/04/10 18:50:18 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define P g->player

int		actions(t_game *g)
{
	g->oldtime = g->time;
	g->time = clock();
	g->frametime = (g->time - g->oldtime) / CLOCKS_PER_SEC;
	if (g->isrunning != 0)
		g->isrunning == 1 ? move(g, 1) : move(g, -1);
	if (g->isturning != 0)
		g->isturning == 1 ? rotate(g, 1) : rotate(g, -1);
	mlx_hook(g->win, 2, 1, kbrd_press, g);
	mlx_hook(g->win, 3, 2, kbrd_release, g);
	mlx_hook(g->win, 17, 0L, exit_prog, NULL);
	reload(g);
	return (0);
}

void	move(t_game *g, int i)
{
	if (g->level.map[(int)P.pos.y][(int)(P.pos.x + i * P.dir.x *
		g->movespeed)] == '0')
		P.pos.x = P.pos.x + i * P.dir.x * g->movespeed;
	if (g->level.map[(int)(P.pos.y + i * P.dir.y *
		g->movespeed)][(int)P.pos.x] == '0')
		P.pos.y = P.pos.y + i * P.dir.y * g->movespeed;
}

void	rotate(t_game *g, int i)
{
	double olddirx;
	double oldplanex;

	olddirx = g->player.dir.x;
	g->player.dir.x = g->player.dir.x * cos(i * g->rotspeed) - g->player.dir.y *
		sin(i * g->rotspeed);
	g->player.dir.y = olddirx * sin(i * g->rotspeed) + g->player.dir.y * cos(i *
			g->rotspeed);
	oldplanex = g->player.plane.x;
	g->player.plane.x = g->player.plane.x * cos(i * g->rotspeed) -
		g->player.plane.y * sin(i * g->rotspeed);
	g->player.plane.y = oldplanex * sin(i * g->rotspeed) + g->player.plane.y *
		cos(i * g->rotspeed);
}

int		kbrd_press(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	if (keycode == KEY_UP)
		g->isrunning = 1;
	else if (keycode == KEY_DOWN)
		g->isrunning = -1;
	else if (keycode == KEY_LEFT)
		g->isturning = -1;
	else if (keycode == KEY_RIGHT)
		g->isturning = 1;
	reload(g);
	return (0);
}

int		kbrd_release(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	if (keycode == KEY_UP)
		g->isrunning = 0;
	else if (keycode == KEY_DOWN)
		g->isrunning = 0;
	else if (keycode == KEY_LEFT)
		g->isturning = 0;
	else if (keycode == KEY_RIGHT)
		g->isturning = 0;
	reload(g);
	return (0);
}
