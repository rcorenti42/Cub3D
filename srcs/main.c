/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:48 by rcorenti          #+#    #+#             */
/*   Updated: 2022/03/24 21:04:39 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	ft_quit(t_cub *cub, char *str, int index)
{
	if (str)
		ft_putendl_fd(str, 2);
	if (cub->mlx.image)
		mlx_destroy_image(cub->mlx.ptr, cub->mlx.image);
	if (cub->mlx.win)
		mlx_destroy_window(cub->mlx.ptr, cub->mlx.win);
	if (cub->mlx.ptr)
		mlx_destroy_display(cub->mlx.ptr);
	free_textures(cub);
	ft_free_map(cub->map);
	exit(index);
}

int	ft_quit_loop(t_cub *cub)
{
	ft_quit(cub, NULL, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.mlx.ptr = mlx_init();
	if (!cub.mlx.ptr)
		ft_quit(&cub, NULL, 1);
	if (ft_parser(&cub, argc, argv))
		ft_quit(&cub, NULL, 1);
	printf("ceiling=%x\nfloor=%x\n", cub.floor_color, cub.ceiling_color);
	ft_init(&cub);
	cub.mlx.win = mlx_new_window(cub.mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!cub.mlx.win)
		ft_quit(&cub, NULL, 1);
	ft_loop(&cub);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_cub	cub;

// 	cub.map = store_map(ac, av);
// 	if (cub.map == NULL)
// 		return (0);
// 	if (fill_textures(&cub) != 0)
// 		return (ft_free_map(cub.map));
// 	if (ft_check_map(&cub) != 0)
// 	{
// 		free_textures(&cub);
// 		return (ft_free_map(cub.map));
// 	}
// 	free_textures(&cub);
// 	ft_free_map(cub.map);
// }