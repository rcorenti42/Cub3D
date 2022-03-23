/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:25 by rcorenti          #+#    #+#             */
/*   Updated: 2022/03/23 02:53:00 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_font(t_cub *cub)
{
	int				x;
	int				y;
	unsigned char	*tmp;

	y = 0;
	tmp = (unsigned char *)&(cub->C);
	while (y < WIN_HEIGHT)
	{
		x = 0;
		if (y == WIN_HEIGHT / 2)
			tmp = (unsigned char *)&(cub->F);
		while (x < WIN_WIDTH)
		{
			cub->mlx.buffer[y * cub->mlx.line_bytes + x
				* cub->mlx.pixel_bits / 8] = tmp[0];
			cub->mlx.buffer[y * cub->mlx.line_bytes + x
				* cub->mlx.pixel_bits / 8 + 1] = tmp[1];
			cub->mlx.buffer[y * cub->mlx.line_bytes + x
				* cub->mlx.pixel_bits / 8 + 2] = tmp[2];
			x++;
		}
		y++;
	}
}

static void	ft_put_line(t_cub *cub)
{
	long	tmp;

	tmp = cub->mlx.y * cub->mlx.tex_line_bytes - WIN_HEIGHT / 2
		* cub->mlx.tex_line_bytes + cub->mlx.line_height / 2
		* cub->mlx.tex_line_bytes;
	cub->mlx.tex_y = tmp * cub->mlx.tex_h / cub->mlx.line_height
		/ cub->mlx.tex_line_bytes;
	cub->mlx.buffer[cub->mlx.y * cub->mlx.line_bytes + cub->mlx.x
		* (cub->mlx.pixel_bits / 8)] = cub->mlx.tex_buff_img[cub->mlx.tex_y
		* cub->mlx.tex_line_bytes + cub->mlx.tex_x * (cub->mlx.tex_pixel_bits
			/ 8)];
	cub->mlx.buffer[cub->mlx.y * cub->mlx.line_bytes + cub->mlx.x
		* (cub->mlx.pixel_bits / 8) + 1] = cub->mlx.tex_buff_img[cub->mlx.tex_y
		* cub->mlx.tex_line_bytes + cub->mlx.tex_x * (cub->mlx.tex_pixel_bits
			/ 8) + 1];
	cub->mlx.buffer[cub->mlx.y * cub->mlx.line_bytes + cub->mlx.x
		* (cub->mlx.pixel_bits / 8) + 2] = cub->mlx.tex_buff_img[cub->mlx.tex_y
		* cub->mlx.tex_line_bytes + cub->mlx.tex_x * (cub->mlx.tex_pixel_bits
			/ 8) + 2];
}

void	ft_put_wall(t_cub *cub)
{
	while (cub->mlx.x < WIN_WIDTH)
	{
		init_player_val(cub);
		ft_step(cub);
		cub->player.hit = 0;
		while (cub->player.hit == 0)
		{
			if (cub->player.side_x < cub->player.side_y)
				if_y_side(cub);
			else
				if_x_side(cub);
			if (cub->map[cub->player.map_y][cub->player.map_x] != '0')
				cub->player.hit = 1;
		}
		ft_raycast(cub);
		while (cub->mlx.y < cub->mlx.draw_end)
		{
			ft_put_line(cub);
			cub->mlx.y++;
		}
		cub->mlx.x++;
	}
}

void	ft_key_walk(t_cub *cub)
{	
	if (cub->key[0])
	{
		if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x + (cub->player.dir_x * 1.1) * cub->player.move_speed)] == '0')
			cub->player.pos_x += cub->player.dir_x * cub->player.move_speed;
		if (cub->map[(int)(cub->player.pos_y + (cub->player.dir_y * 1.1) * cub->player.move_speed)][(int)cub->player.pos_x] == '0')
			cub->player.pos_y += cub->player.dir_y * cub->player.move_speed;
	}
	if (cub->key[1])
	{
		if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x - (cub->player.dir_x * 1.1) * cub->player.move_speed)] == '0')
			cub->player.pos_x -= cub->player.dir_x * cub->player.move_speed;
		if (cub->map[(int)(cub->player.pos_y - (cub->player.dir_y * 1.1) * cub->player.move_speed)][(int)cub->player.pos_x] == '0')
			cub->player.pos_y -= cub->player.dir_y * cub->player.move_speed;
	}
	if (cub->key[2])
	{
		if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x + cub->player.plane_x * (cub->player.move_speed * 1.1))] == '0')
			cub->player.pos_x += cub->player.plane_x * cub->player.move_speed;
		if (cub->map[(int)(cub->player.pos_y + cub->player.plane_y * (cub->player.move_speed * 1.1))][(int)cub->player.pos_x] == '0')
			cub->player.pos_y += cub->player.plane_y * cub->player.move_speed;
	}
	if (cub->key[3])
	{
		if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x - cub->player.plane_x * (cub->player.move_speed * 1.1))] == '0')
			cub->player.pos_x -= cub->player.plane_x * cub->player.move_speed;
		if (cub->map[(int)(cub->player.pos_y - cub->player.plane_y * (cub->player.move_speed * 1.1))][(int)cub->player.pos_x] == '0')
			cub->player.pos_y -= cub->player.plane_y * cub->player.move_speed;
	}
}

void	ft_key_rot(t_cub *cub)
{
	double	tmp;

	if (cub->key[4])
	{
		tmp = cub->player.dir_x;
		cub->player.dir_x = cub->player.dir_x * cos(-cub->player.rot_speed)
			- cub->player.dir_y * sin(-cub->player.rot_speed);
		cub->player.dir_y = tmp * sin(-cub->player.rot_speed)
			+ cub->player.dir_y * cos(-cub->player.rot_speed);
		tmp = cub->player.plane_x;
		cub->player.plane_x = cub->player.plane_x * cos(-cub->player.rot_speed)
			- cub->player.plane_y * sin(-cub->player.rot_speed);
		cub->player.plane_y = tmp * sin(-cub->player.rot_speed)
			+ cub->player.plane_y * cos(-cub->player.rot_speed);
	}
	if (cub->key[5])
	{
		tmp = cub->player.dir_x;
		cub->player.dir_x = cub->player.dir_x * cos(cub->player.rot_speed)
			- cub->player.dir_y * sin(cub->player.rot_speed);
		cub->player.dir_y = tmp * sin(cub->player.rot_speed) + cub->player.dir_y
			* cos(cub->player.rot_speed);
		tmp = cub->player.plane_x;
		cub->player.plane_x = cub->player.plane_x * cos(cub->player.rot_speed)
			- cub->player.plane_y * sin(cub->player.rot_speed);
		cub->player.plane_y = tmp * sin(cub->player.rot_speed)
			+ cub->player.plane_y * cos(cub->player.rot_speed);
	}
}
