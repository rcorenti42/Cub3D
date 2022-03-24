/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:15:07 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/24 20:05:53 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_store_map(int fd)
{
	int		gnl_rt;
	char	*tmp_map;
	char	**map;
	char	*line;

	gnl_rt = 1;
	tmp_map = NULL;
	while (gnl_rt)
	{
		gnl_rt = get_next_line(fd, &line);
		tmp_map = ft_strjoin2(tmp_map, line, 0, 0);
		tmp_map = ft_strjoin2(tmp_map, "\n", 0, 0);
		free(line);
	}
	map = ft_split(tmp_map, '\n');
	free(tmp_map);
	return (map);
}

int	check_around(char **map, int i, int j)
{
	if (i == 0 || j == 0)
		return (1);
	if (ft_strlen(map[i]) - 1 == j)
		return (1);
	if (map[i + 1] == NULL)
		return (1);
	if (ft_strlen(map[i - 1]) - 1 < j || ft_strlen(map[i + 1]) - 1 < j)
		return (1);
	if (map[i + 1][j] == ' ' || map[i - 1][j] == ' '
		|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (1);
	return (0);
}

int	check_open_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != ' ' && map[i][j] != '1')
				if (check_around(map, i, j) != 0)
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_chars(char **map, int *x, int *y, int p_count)
{
	int	i;
	int	j;

	i = -1;
	if (map == NULL)
		return (1);
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (is_player(map[i][j]) == 1)
			{
				p_count++;
				*x = j;
				*y = i;
			}
			else if (is_charset(map[i][j]) != 1)
				return (printf("Error\nInvalid character %c", map[i][j]));
		}
	}
	if (p_count != 1)
		return (printf("Error\nNo player on the map\n"));
	return (0);
}

int	ft_parser(t_cub *cub, int ac, char **av)
{
	cub->map = store_map(ac, av);
	if (cub->map == NULL)
		return (1);
	if (fill_textures(cub) != 0)
		return (ft_free_map(cub->map));
	if (ft_check_map(cub) != 0)
		return (ft_free_map(cub->map));
	return (0);
}
