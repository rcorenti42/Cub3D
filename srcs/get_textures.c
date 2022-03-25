/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:51:24 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/25 16:13:59 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_txt(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map[i] != NULL)
	{
		if (get_texture(cub, cub->map[i], ft_skip_spaces(cub->map[i], 0) != 0))
			break ;
		i++;
	}
	if (cub->path_to_north == NULL || cub->path_to_south == NULL
		|| cub->path_to_west == NULL || cub->path_to_east == NULL)
		return (printf("Error\nProblem with some of the texture file\n"));
	return (0);
}

unsigned int	get_bits(char *color, int *i)
{
	unsigned int	bit;
	int				tmp;

	bit = 0;
	tmp = 0;
	while (ft_is_digit(color[*i]))
	{
		tmp++;
		if (bit != 0)
			bit *= 10;
		bit += color[(*i)++] - '0';
	}
	if (!tmp)
		return (256);
	return (bit);
}

unsigned int	get_hex(char *color, unsigned int r,
	unsigned int g, unsigned int b)
{
	unsigned int	rgb;
	int				i;

	i = 0;
	r = get_bits(color, &i);
	if (color[i++] != ',' || r > 255)
		return (0);
	g = get_bits(color, &i);
	if (color[i++] != ',' || g > 255)
		return (0);
	b = get_bits(color, &i);
	if (b > 255 || color[i] != '\0')
		return (0);
	rgb = 65536 * r + 256 * g + b;
	if (rgb == 0)
		rgb = 65793;
	return (rgb);
}

int	fill_colors(t_cub *cub)
{
	int		i;
	char	*floor_color;
	char	*ceiling_color;

	floor_color = NULL;
	ceiling_color = NULL;
	i = 0;
	while (cub->map[i] != NULL)
		if (get_color(cub->map[i++], &floor_color, &ceiling_color) != 0)
			break ;
	if (floor_color == NULL || ceiling_color == NULL)
	{
		free_either(floor_color, ceiling_color);
		return (printf("Error\nProblen with floor or ceiling color\n"));
	}
	cub->floor_color = get_hex(floor_color, 0, 0, 0);
	cub->ceiling_color = get_hex(ceiling_color, 0, 0, 0);
	if (cub->ceiling_color == 0 || cub->floor_color == 0)
	{
		free_either(floor_color, ceiling_color);
		return (printf("Error\nProblem with floor or ceiling color\n"));
	}
	free_either(floor_color, ceiling_color);
	return (0);
}

int	fill_textures(t_cub *cub)
{
	cub->path_to_north = NULL;
	cub->path_to_south = NULL;
	cub->path_to_west = NULL;
	cub->path_to_east = NULL;
	if (fill_txt(cub) != 0)
		return (1);
	if (fill_colors(cub) != 0)
		return (1);
	return (0);
}
