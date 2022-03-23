/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:58:01 by rcorenti          #+#    #+#             */
/*   Updated: 2022/03/23 21:17:50 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_step(t_cub *cub)
{
	if (cub->player.ray_x < 0)
	{
		cub->player.step_x = -1;
		cub->player.side_x = (cub->player.pos_x - cub->player.map_x)
			* cub->player.delta_x;
	}
	else
	{
		cub->player.step_x = 1;
		cub->player.side_x = (cub->player.map_x + 1.0 - cub->player.pos_x)
			* cub->player.delta_x;
	}
	if (cub->player.ray_y < 0)
	{
		cub->player.step_y = -1;
		cub->player.side_y = (cub->player.pos_y - cub->player.map_y)
			* cub->player.delta_y;
	}
	else
	{
		cub->player.step_y = 1;
		cub->player.side_y = (cub->player.map_y + 1.0 - cub->player.pos_y)
			* cub->player.delta_y;
	}
}

void	ft_raycast(t_cub *cub)
{
	cub->mlx.tex_buff_img = mlx_get_data_addr(cub->mlx.texture,
			&(cub->mlx.tex_pixel_bits), &(cub->mlx.tex_line_bytes),
			&(cub->mlx.tex_endian));
	if (cub->player.side == NORTH || cub->player.side == SOUTH)
		cub->player.wall = (cub->player.side_x - cub->player.delta_x);
	else
		cub->player.wall = (cub->player.side_y - cub->player.delta_y);
	cub->mlx.line_height = (int)(WIN_HEIGHT / cub->player.wall);
	cub->mlx.draw_start = -cub->mlx.line_height / 2 + WIN_HEIGHT / 2;
	if (cub->mlx.draw_start < 0)
		cub->mlx.draw_start = 0;
	cub->mlx.draw_end = cub->mlx.line_height / 2 + WIN_HEIGHT / 2;
	if (cub->mlx.draw_end > WIN_HEIGHT)
		cub->mlx.draw_end = WIN_HEIGHT;
	if (cub->player.side == NORTH || cub->player.side == SOUTH)
		cub->mlx.wall_x = cub->player.pos_y + cub->player.wall
			* cub->player.ray_y;
	else
		cub->mlx.wall_x = cub->player.pos_x + cub->player.wall
			* cub->player.ray_x;
	cub->mlx.wall_x -= floor(cub->mlx.wall_x);
	cub->mlx.tex_x = (int)(cub->mlx.wall_x * (double)(cub->mlx.tex_w));
	cub->mlx.y = cub->mlx.draw_start;
}

int	ft_frame(t_cub *cub)
{
	cub->mlx.x = 0;
	cub->mlx.buffer = mlx_get_data_addr(cub->mlx.image, &(cub->mlx.pixel_bits),
			&(cub->mlx.line_bytes), &(cub->mlx.endian));
	ft_put_font(cub);
	ft_key_walk(cub);
	ft_key_rot(cub);
	ft_put_wall(cub);
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->mlx.image, 0, 0);
	return (0);
}

int	ft_press(int code, t_cub *cub)
{
	if (code == UP)
		cub->key[0] = 1;
	if (code == DOWN)
		cub->key[1] = 1;
	if (code == RIGHT)
		cub->key[2] = 1;
	if (code == LEFT)
		cub->key[3] = 1;
	if (code == LEFT_ARROW)
		cub->key[4] = 1;
	if (code == RIGHT_ARROW)
		cub->key[5] = 1;
	if (code == ESC)
		ft_quit(cub, NULL, 0);
	return (0);
}

int	ft_release(int code, t_cub *cub)
{
	if (code == UP)
		cub->key[0] = 0;
	if (code == DOWN)
		cub->key[1] = 0;
	if (code == RIGHT)
		cub->key[2] = 0;
	if (code == LEFT)
		cub->key[3] = 0;
	if (code == LEFT_ARROW)
		cub->key[4] = 0;
	if (code == RIGHT_ARROW)
		cub->key[5] = 0;
	return (0);
}
