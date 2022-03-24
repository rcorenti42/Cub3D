/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:54:45 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/24 22:24:55 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map(t_cub *cub)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	if (check_chars(cub->map + 6, &x, &y, 0) != 0)
		return (1);
	if (check_open_map(cub->map + 6) != 0)
		return (printf("Error\nMap is not closed\n"));
	cub->player.pos_x = x + 0.5;
	cub->player.pos_y = y + 6.5;
	fill_player(cub, cub->map[y + 6][x]);
	cub->map[y + 6][x] = '0';
	return (0);
}

int	ft_free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (1);
	while (map[i] != NULL)
		free(map[i++]);
	free(map);
	return (1);
}

char	**store_map(int ac, char **av)
{
	int	fd;

	fd = 0;
	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (NULL);
	}
	if (ft_check_file_name(av[1]) != 0)
	{
		printf("Error\nNot a .cub file\n");
		return (NULL);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 1)
	{
		printf("Error\nCouldn't open file\n");
		return (NULL);
	}
	return (ft_store_map(fd));
}
