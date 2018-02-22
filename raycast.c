/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:07:38 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/04/10 19:01:18 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	put_color(char *pxls, int byte, int col)
{
	pxls[byte] = col;
	pxls[++byte] = col >> 8;
	pxls[++byte] = col >> 16;
}

static void	draw_vert_line(t_game *g, t_wall w, int x)
{
	int lineheight;
	int drawstart;
	int	drawend;
	int	i;
	int	byte;

	lineheight = (int)(WIN_H / w.travdist);
	drawstart = ((-lineheight / 2 + WIN_H / 2) < 0) ? 0 :
		(-lineheight / 2 + WIN_H / 2);
	drawend = ((lineheight / 2 + WIN_H / 2) >= WIN_H) ? (WIN_H - 1) :
		(lineheight / 2 + WIN_H / 2);
	i = -1;
	while (++i < WIN_H)
	{
		byte = (x * g->bits_per_pixel / 8) + (i * g->size_line);
		if (i < drawstart)
			put_color(g->pxls, byte, 0xC8C8C8);
		if (i >= drawstart && i <= drawend)
			put_color(g->pxls, byte, w.col);
		if (i > drawend)
			put_color(g->pxls, byte, 0xFFFFD0);
	}
}

static int	paintw(t_wall w, t_intpair s, char c)
{
	int	mod;
	int col;

	if (w.side == 0)
		mod = (s.x > 0) ? 1 : 3;
	else
		mod = (s.y > 0) ? 4 : 2;
	col = 0;
	if (c == '1')
		col = rgb2hex(127 * mod / 2, 127 * mod / 2, 127 * mod / 2);
	else if (c == '2')
		col = rgb2hex(63 * mod, 0, 0);
	else if (c == '3')
		col = rgb2hex(0, 63 * mod, 0);
	else if (c == '4')
		col = rgb2hex(0, 0, 63 * mod);
	else if (c == '5')
		col = rgb2hex(63 * mod, 63 * mod, 0);
	return (col);
}

static void	rayhit(t_game *g, t_ray r, int x)
{
	while (1)
	{
		if (r.sidedist.x < r.sidedist.y)
		{
			r.sidedist.x += r.deltadist.x;
			r.map.x += r.step.x;
			r.wall.side = 0;
		}
		else
		{
			r.sidedist.y += r.deltadist.y;
			r.map.y += r.step.y;
			r.wall.side = 1;
		}
		if (g->level.map[r.map.y][r.map.x] > '0')
		{
			r.wall.col = paintw(r.wall, r.step, g->level.map[r.map.y][r.map.x]);
			break ;
		}
	}
	r.wall.travdist = (r.wall.side == 0) ? (r.map.x - r.pos.x + (1 - r.step.x)
		/ 2) / r.dir.x : (r.map.y - r.pos.y + (1 - r.step.y) / 2) / r.dir.y;
	draw_vert_line(g, r.wall, x);
}

void		raycast(t_game *g)
{
	t_ray	r;
	int		x;

	x = -1;
	while (++x < WIN_W)
	{
		r.camerax = 2 * x / (double)WIN_W - 1;
		r.pos = g->player.pos;
		r.dir.x = g->player.dir.x + g->player.plane.x * r.camerax;
		r.dir.y = g->player.dir.y + g->player.plane.y * r.camerax;
		r.map.x = (int)r.pos.x;
		r.map.y = (int)r.pos.y;
		r.deltadist.x = sqrt(1 + (r.dir.y * r.dir.y) / (r.dir.x * r.dir.x));
		r.deltadist.y = sqrt(1 + (r.dir.x * r.dir.x) / (r.dir.y * r.dir.y));
		r.step.x = (r.dir.x < 0) ? -1 : 1;
		r.sidedist.x = (r.dir.x < 0) ? (r.pos.x - r.map.x) * r.deltadist.x :
			(r.map.x + 1.0 - r.pos.x) * r.deltadist.x;
		r.step.y = (r.dir.y < 0) ? -1 : 1;
		r.sidedist.y = (r.dir.y < 0) ? (r.pos.y - r.map.y) * r.deltadist.y :
			(r.map.y + 1.0 - r.pos.y) * r.deltadist.y;
		r.wall.col = 0x00C300;
		rayhit(g, r, x);
	}
}
