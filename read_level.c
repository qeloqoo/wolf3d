/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubrovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:01:39 by mdubrovs          #+#    #+#             */
/*   Updated: 2017/04/10 19:02:08 by mdubrovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	scan_legend(int fd, t_level *level)
{
	char	*str;
	int		i;
	char	**array;

	if (get_next_line(fd, &str) != 1)
		exit_prog(1);
	i = 0;
	array = ft_strsplit(str, ',');
	while (array[i] != NULL)
		i++;
	if (i != 5)
		exit_prog(3);
	level->width = ft_atoi(array[0]);
	level->height = ft_atoi(array[1]);
	level->coord.x = (double)ft_atoi(array[2]);
	level->coord.y = (double)ft_atoi(array[3]);
	level->name = ft_strdup(array[4]);
	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array[i]);
}

static char	**scan_map(int fd, int height, int width)
{
	char	**map;
	char	*str;
	int		i;

	if (!(map = (char**)malloc(sizeof(char*) * height + 1)))
		exit_prog(2);
	i = -1;
	while (++i < height && width > 0)
	{
		if (get_next_line(fd, &str) != 1)
			exit_prog(3);
		map[i] = str;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

t_level		read_level(char *file)
{
	int		fd;
	t_level	level;

	if ((fd = open(file, O_RDONLY)) == -1)
		exit_prog(1);
	else
		scan_legend(fd, &level);
	level.map = scan_map(fd, level.height, level.width);
	return (level);
}
