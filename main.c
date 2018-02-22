/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:12:46 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/04/10 18:52:30 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game*)ft_memalloc(sizeof(t_game));
	if (argc == 2)
	{
		game->level = read_level(argv[1]);
		game->mlx = mlx_init();
		init_game(game);
		reload(game);
		mlx_loop(game->mlx);
	}
	else
		exit_prog(4);
	return (0);
}
