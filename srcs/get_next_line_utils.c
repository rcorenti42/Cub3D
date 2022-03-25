/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:32:07 by sobouatt          #+#    #+#             */
/*   Updated: 2022/03/25 11:12:53 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_substr(char const *s, unsigned int start, int len, int f)
{
	char	*res;
	int		i;

	i = 0;
	if ((int)start >= ft_strlen((char *)s))
	{
		res = malloc(sizeof(char) * 1);
		if (!res)
			return (NULL);
		free((char *)s);
		res[0] = '\0';
		return (res);
	}
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	if (f == 1)
		free((char *)s);
	return (res);
}
