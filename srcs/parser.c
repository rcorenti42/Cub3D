/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:15:07 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/25 16:36:37 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_store_map(int fd)
{
	int		gnl_rt;
	char	*tmp_map;
	char	**map;
	char	*line;
	int		i;

	i = 0;
	gnl_rt = 1;
	tmp_map = NULL;
	while (gnl_rt)
	{
		gnl_rt = get_next_line(fd, &line);
		gain_space(&i, &line, &tmp_map);
		free(line);
	}
	map = ft_split(tmp_map, '[');
	free(tmp_map);
	close(fd);
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
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '\n')
				if (check_around(map, i, j) != 0)
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_both(int *x, int *y, int i, int j)
{
	*x = j;
	*y = i;
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
		if (map[i][0] == '\n')
			return (printf("Error\nInvalid return character on the map\n"));
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (is_player(map[i][j]) == 1)
			{
				p_count++;
				init_both(x, y, i, j);
			}
			else if (is_charset(map[i][j]) != 1 && map[i][j] != '\n')
				return (printf("Error\nInvalid character %c\n", map[i][j]));
		}
	}
	if (p_count != 1)
		return (printf("Error\nNo player on the map\n"));
	return (0);
}
