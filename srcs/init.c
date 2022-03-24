/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:34 by rcorenti          #+#    #+#             */
/*   Updated: 2022/03/24 22:43:13 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_loop(t_cub *cub)
{
	cub->mlx.no = mlx_xpm_file_to_image(cub->mlx.ptr, cub->path_to_north,
			&(cub->mlx.no_w), &(cub->mlx.no_h));
	cub->mlx.so = mlx_xpm_file_to_image(cub->mlx.ptr, cub->path_to_south,
			&(cub->mlx.so_w), &(cub->mlx.so_h));
	cub->mlx.we = mlx_xpm_file_to_image(cub->mlx.ptr, cub->path_to_west,
			&(cub->mlx.we_w), &(cub->mlx.we_h));
	cub->mlx.ea = mlx_xpm_file_to_image(cub->mlx.ptr, cub->path_to_east,
			&(cub->mlx.ea_w), &(cub->mlx.ea_h));
	if (cub->mlx.no == NULL || cub->mlx.so == NULL || cub->mlx.we == NULL
		|| cub->mlx.ea == NULL)
		ft_quit(cub, "bad textures files", 1);
	mlx_hook(cub->mlx.win, 2, 1L << 0, ft_press, cub);
	mlx_hook(cub->mlx.win, 3, 1L << 1, ft_release, cub);
	mlx_loop_hook(cub->mlx.ptr, ft_frame, cub);
	mlx_hook(cub->mlx.win, 17, 0L, ft_quit_loop, cub);
	mlx_loop(cub->mlx.ptr);
}

void	ft_init(t_cub *cub)
{
	cub->mlx.y = 0;
	cub->mlx.win = NULL;
	cub->player.move_speed = WALKING_SPEED;
	if (cub->player.move_speed > 1)
		cub->player.move_speed = 1;
	cub->player.rot_speed = ROTATION_SPEED;
	cub->key[0] = 0;
	cub->key[1] = 0;
	cub->key[2] = 0;
	cub->key[3] = 0;
	cub->key[4] = 0;
	cub->key[5] = 0;
	cub->mlx.image = mlx_new_image(cub->mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
	cub->path_to_east = NULL;
	cub->path_to_west = NULL;
	cub->path_to_north = NULL;
	cub->path_to_south = NULL;
	cub->map = NULL;
	cub->mlx.ea = NULL;
	cub->mlx.we = NULL;
	cub->mlx.no = NULL;
	cub->mlx.so = NULL;
}

void	init_player_val(t_cub *cub)
{
	cub->player.camera_x = 2 * cub->mlx.x / (double)WIN_WIDTH - 1;
	cub->player.ray_x = cub->player.dir_x + cub->player.plane_x
		* cub->player.camera_x;
	cub->player.ray_y = cub->player.dir_y + cub->player.plane_y
		* cub->player.camera_x;
	cub->player.map_x = (int)(cub->player.pos_x);
	cub->player.map_y = (int)(cub->player.pos_y);
	cub->player.delta_x = fabs(1 / cub->player.ray_x);
	cub->player.delta_y = fabs(1 / cub->player.ray_y);
}

void	if_x_side(t_cub *cub)
{
	cub->player.side_y += cub->player.delta_y;
	cub->player.map_y += cub->player.step_y;
	if (cub->player.step_y == 1)
	{
		cub->player.side = EAST;
		cub->mlx.tex_h = cub->mlx.ea_h;
		cub->mlx.tex_w = cub->mlx.ea_w;
		cub->mlx.texture = cub->mlx.ea;
	}
	else
	{
		cub->player.side = WEST;
		cub->mlx.tex_h = cub->mlx.we_h;
		cub->mlx.tex_w = cub->mlx.we_w;
		cub->mlx.texture = cub->mlx.we;
	}
}

void	if_y_side(t_cub *cub)
{
	cub->player.side_x += cub->player.delta_x;
	cub->player.map_x += cub->player.step_x;
	if (cub->player.step_x == 1)
	{
		cub->player.side = SOUTH;
		cub->mlx.tex_h = cub->mlx.so_h;
		cub->mlx.tex_w = cub->mlx.so_w;
		cub->mlx.texture = cub->mlx.so;
	}
	else
	{
		cub->player.side = NORTH;
		cub->mlx.tex_h = cub->mlx.no_h;
		cub->mlx.tex_w = cub->mlx.no_w;
		cub->mlx.texture = cub->mlx.no;
	}
}
