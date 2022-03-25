/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:02:17 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/25 16:36:45 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_charset(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2, int i, int j)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	if (s1)
	{
		while (s1[i] && s1)
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

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

void	gain_space(int *i, char **line, char **tmp_map)
{
	if (*i <= 6 && (*line)[0] != '\0')
	{
		*tmp_map = ft_strjoin2(*tmp_map, *line, 0, 0);
		*tmp_map = ft_strjoin2(*tmp_map, "\n[", 0, 0);
		(*i)++;
	}
	else if (*i > 6)
	{
		*tmp_map = ft_strjoin2(*tmp_map, *line, 0, 0);
		*tmp_map = ft_strjoin2(*tmp_map, "\n[", 0, 0);
	}
}
