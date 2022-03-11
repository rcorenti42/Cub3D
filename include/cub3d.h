#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/include/libft.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

# define WIN_WIDTH 1500
# define WIN_HEIGHT 800

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct  s_player
{
  int     step_x;
  int     step_y;
  int     hit;
  int     side;
  int     map_x;
  int     map_y;
  double  pos_x;
  double  pos_y;
  double  dir_x;
  double  dir_y;
  double  plane_x;
  double  plane_y;
  double  camera_x;
  double  camera_y;
  double  ray_x;
  double  ray_y;
  double  side_x;
  double  side_y;
  double  delta_x;
  double  delta_y;
  double  wall;
  double  time;
  double  old_time;
  double  move_speed;
  double  rot_speed;
}               t_player;

typedef struct  s_mlx
{
  void          *ptr;
  void          *win;
  void          *image;
  void          *no;
  void          *so;
  void          *we;
  void          *ea;
  void          *texture;
  char          *buffer;
  char          *tex_buff_img;
  int           pixel_bits;
  int           tex_pixel_bits;
  int           line_bytes;
  int           tex_line_bytes;
  int           line_height;
  int           draw_start;
  int           draw_end;
  int           endian;
  int           tex_endian;
  int           floor_color;
  int           ceiling_color;
  int           no_w;
  int           no_h;
  int           so_w;
  int           so_h;
  int           we_w;
  int           we_h;
  int           ea_w;
  int           ea_h;
  int           tex_x;
  int           tex_y;
  int           tex_w;
  int           tex_h;
  int           x;
  int           y;
  double        step;
  double        wall_x;
  double        tex_pos;
  int  color;
  char          *tex_buf;
}               t_mlx;

typedef struct  s_map
{
  char  **tab;
  int   height;
  int   width;
}               t_map;

typedef struct  s_cub
{
  t_mlx         mlx;
  t_map         map;
  t_player      player;
}               t_cub;

#endif
