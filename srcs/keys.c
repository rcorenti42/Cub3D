/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:06:38 by rcorenti          #+#    #+#             */
/*   Updated: 2022/03/23 21:15:58 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_key_walk_2(t_cub *cub)
{
	if (cub->key[2])
	{
		if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x
			+ cub->player.plane_x * (cub->player.move_speed * 1.1))] == '0')
			cub->player.pos_x += cub->player.plane_x * cub->player.move_speed;
		if (cub->map[(int)(cub->player.pos_y + cub->player.plane_y
				* (cub->player.move_speed * 1.1))][(int)cub->player.pos_x]
				== '0')
			cub->player.pos_y += cub->player.plane_y * cub->player.move_speed;
	}
	if (cub->key[3])
	{
		if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x
			- cub->player.plane_x * (cub->player.move_speed * 1.1))] == '0')
			cub->player.pos_x -= cub->player.plane_x * cub->player.move_speed;
		if (cub->map[(int)(cub->player.pos_y - cub->player.plane_y
				* (cub->player.move_speed * 1.1))][(int)cub->player.pos_x]
					== '0')
			cub->player.pos_y -= cub->player.plane_y * cub->player.move_speed;
	}
}

void	ft_key_walk(t_cub *cub)
{	
	if (cub->key[0])
	{
		if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x
			+ (cub->player.dir_x * 1.1) * cub->player.move_speed)] == '0')
			cub->player.pos_x += cub->player.dir_x * cub->player.move_speed;
		if (cub->map[(int)(cub->player.pos_y + (cub->player.dir_y * 1.1)
				* cub->player.move_speed)][(int)cub->player.pos_x] == '0')
			cub->player.pos_y += cub->player.dir_y * cub->player.move_speed;
	}
	if (cub->key[1])
	{
		if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x
			- (cub->player.dir_x * 1.1) * cub->player.move_speed)] == '0')
			cub->player.pos_x -= cub->player.dir_x * cub->player.move_speed;
		if (cub->map[(int)(cub->player.pos_y - (cub->player.dir_y * 1.1)
				* cub->player.move_speed)][(int)cub->player.pos_x] == '0')
			cub->player.pos_y -= cub->player.dir_y * cub->player.move_speed;
	}
	ft_key_walk_2(cub);
}

void	ft_key_rot_2(t_cub *cub)
{
	double	tmp;
	
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
	ft_key_rot_2(cub);
}
