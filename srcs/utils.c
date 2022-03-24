/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:02:17 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/24 20:04:09 by sobouatt         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
