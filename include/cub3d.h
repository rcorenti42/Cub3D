/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:04:59 by rcorenti          #+#    #+#             */
/*   Updated: 2022/03/25 16:37:22 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/include/libft.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define ESC 65307

# define WALKING_SPEED 0.25
# define ROTATION_SPEED 0.15

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define BUFFER_SIZE 8

typedef struct s_player
{
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	camera_y;
	double	ray_x;
	double	ray_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	wall;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	void	*image;
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
	void	*texture;
	char	*buffer;
	char	*tex_buff_img;
	int		pixel_bits;
	int		tex_pixel_bits;
	int		line_bytes;
	int		tex_line_bytes;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		endian;
	int		tex_endian;
	int		no_w;
	int		no_h;
	int		so_w;
	int		so_h;
	int		we_w;
	int		we_h;
	int		ea_w;
	int		ea_h;
	int		tex_x;
	int		tex_y;
	int		tex_w;
	int		tex_h;
	int		x;
	int		y;
	double	step;
	double	wall_x;
	double	tex_pos;
	int		color;
	char	*tex_buf;
}	t_mlx;

typedef struct s_cub
{
	t_mlx			mlx;
	char			**map;
	t_player		player;
	int				key[6];
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	char			*path_to_north;
	char			*path_to_south;
	char			*path_to_west;
	char			*path_to_east;
}	t_cub;

void			ft_init(t_cub *cub);
void			init_player_val(t_cub *cub);
void			ft_loop(t_cub*cub);
void			if_x_side(t_cub *cub);
void			if_y_side(t_cub *cub);
void			ft_step(t_cub *cub);
void			ft_raycast(t_cub *cub);
void			ft_put_font(t_cub *cub);
void			ft_put_wall(t_cub *cub);
void			ft_key_walk(t_cub *cub);
void			ft_key_rot(t_cub *cub);
void			ft_quit(t_cub *cub, char *str, int index);
int				ft_frame(t_cub *cub);
int				ft_press(int code, t_cub *cub);
int				ft_release(int code, t_cub *cub);
int				ft_quit_loop(t_cub *cub);
int				ft_parser(t_cub *cub, int ac, char **av);
int				get_next_line(int fd, char **line);
char			*ft_substr(char const *s, unsigned int start, int len, int f);
void			fill_player(t_cub *cub, char c);
int				is_player(char c);
int				ft_check_file_name(char *str);
char			*ft_strjoin2(char *s1, char *s2, int i, int j);
char			**ft_store_map(int fd);
int				check_around(char **map, int i, int j);
int				check_open_map(char **map);
int				is_charset(char c);
int				check_chars(char **map, int *x, int *y, int p_count);
int				ft_check_map(t_cub *cub);
int				ft_free_map(char **map);
char			**store_map(int ac, char **av);
int				ft_skip_spaces(char *str, int i);
int				check_spaces(char *str);
int				free_textures(t_cub *cub);
int				get_texture(t_cub *cub, char *str, int i);
int				get_color(char *str, char **C, char **F);
int				fill_txt(t_cub *cub);
int				ft_is_digit(char c);
unsigned int	get_hex(char *color, unsigned int r, unsigned int g,
					unsigned int b);
void			free_either(void *F, void *C);
int				fill_colors(t_cub *cub);
int				fill_textures(t_cub *cub);
int				ft_parser(t_cub *cub, int ac, char **av);
void			gain_space(int *i, char **line, char **tmp_map);
int				free_textures(t_cub *cub);

#endif
