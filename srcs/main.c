/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:48 by rcorenti          #+#    #+#             */
/*   Updated: 2022/03/27 16:47:38 by sobouatt         ###   ########.fr       */
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
	if (cub->mlx.ea && cub->mlx.ptr)
		mlx_destroy_image(cub->mlx.ptr, cub->mlx.ea);
	if (cub->mlx.we && cub->mlx.ptr)
		mlx_destroy_image(cub->mlx.ptr, cub->mlx.we);
	if (cub->mlx.no && cub->mlx.ptr)
		mlx_destroy_image(cub->mlx.ptr, cub->mlx.no);
	if (cub->mlx.so && cub->mlx.ptr)
		mlx_destroy_image(cub->mlx.ptr, cub->mlx.so);
	if (str)
		ft_putendl_fd(str, 2);
	if (cub->mlx.image)
		mlx_destroy_image(cub->mlx.ptr, cub->mlx.image);
	if (cub->mlx.win)
		mlx_destroy_window(cub->mlx.ptr, cub->mlx.win);
	if (cub->mlx.ptr)
	{
		mlx_destroy_display(cub->mlx.ptr);
		free(cub->mlx.ptr);
	}
	free_textures(cub);
	ft_free_map(cub->map);
	exit(index);
}

int	ft_quit_loop(t_cub *cub)
{
	ft_quit(cub, NULL, 0);
	return (0);
}

int	ft_parser(t_cub *cub, int ac, char **av)
{
	cub->map = store_map(ac, av);
	if (cub->map == NULL)
		return (1);
	if (fill_textures(cub) != 0)
		return (1);
	if (ft_check_map(cub) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	cub.mlx.ptr = mlx_init();
	if (!cub.mlx.ptr)
		return (printf("Error\nMlx_init failed\n"));
	ft_init(&cub);
	if (ft_parser(&cub, argc, argv))
		ft_quit(&cub, NULL, 1);
	cub.mlx.win = mlx_new_window(cub.mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!cub.mlx.win)
		ft_quit(&cub, NULL, 1);
	ft_loop(&cub);
	return (0);
}
