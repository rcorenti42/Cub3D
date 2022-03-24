/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:07:04 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/24 20:07:05 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_e(t_cub *cub)
{
	cub->player.dir_x = 1;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0.66;
}

void	fill_player(t_cub *cub, char c)
{
	if (c == 'N')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
		cub->player.plane_x = 0.66;
		cub->player.plane_y = 0;
	}
	if (c == 'S')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = 1;
		cub->player.plane_x = -0.66;
		cub->player.plane_y = 0;
	}
	if (c == 'W')
	{
		cub->player.dir_x = -1;
		cub->player.dir_y = 0;
		cub->player.plane_x = 0;
		cub->player.plane_y = -0.66;
	}
	if (c == 'E')
		fill_e(cub);
}

int	ft_check_file_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i -= 4;
	if (i <= 0)
		return (1);
	if (ft_strcmp(str + i, ".cub") == 0)
		return (0);
	return (i);
}

int	ft_skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
