/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:53:52 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/24 19:54:10 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_textures(t_cub *cub)
{
	if (cub->path_to_north != NULL)
		free(cub->path_to_north);
	if (cub->path_to_south != NULL)
		free(cub->path_to_south);
	if (cub->path_to_west != NULL)
		free(cub->path_to_west);
	if (cub->path_to_east != NULL)
		free(cub->path_to_east);
	return (1);
}

int	get_texture(t_cub *cub, char *str, int i)
{
	if (ft_strncmp(str, "NO", 2) == 0)
	{
		i += ft_skip_spaces(str + i, 2);
		cub->path_to_north = ft_strdup(str + i);
	}
	else if (ft_strncmp(str, "SO", 2) == 0)
	{
		i += ft_skip_spaces(str + i, 2);
		cub->path_to_south = ft_strdup(str + i);
	}
	else if (ft_strncmp(str, "WE", 2) == 0)
	{
		i += ft_skip_spaces(str + i, 2);
		cub->path_to_west = ft_strdup(str + i);
	}
	else if (ft_strncmp(str, "EA", 2) == 0)
	{
		i += ft_skip_spaces(str + i, 2);
		cub->path_to_east = ft_strdup(str + i);
	}
	else
		return (0);
	if (check_spaces(str + i))
		return (1);
	return (0);
}

int	get_color(char *str, char **ceiling_color, char **floor_color)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'C')
	{
		i += ft_skip_spaces(str + i, 1);
		*ceiling_color = ft_strdup(str + i);
	}
	else if (str[i] == 'F')
	{
		i += ft_skip_spaces(str + i, 1);
		*floor_color = ft_strdup(str + i);
	}
	return (0);
}

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	free_either(void *floor_color, void *ceiling_color)
{
	if (floor_color != NULL)
		free(floor_color);
	if (ceiling_color != NULL)
		free(ceiling_color);
}
