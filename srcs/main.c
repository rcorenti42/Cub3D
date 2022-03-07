#include "cub3d.h"
#include <string.h>
#include <stdlib.h>

void  ft_init(t_cub *cub)
{
  cub->player.pos_x = 3;
  cub->player.pos_y = 3;
  cub->player.dir_x = -1;
  cub->player.dir_y = 0;
  cub->player.plane_x = 0;
  cub->player.plane_y = 0.66;
  cub->player.time = 0;
  cub->player.old_time = 0;
  cub->mlx.y = 0;
}

void  ft_parse(t_cub *cub)
{
  int i;

  i = 0;
  cub->map.tab = (char **)malloc(sizeof(char *) * 100);
  while (i < 100)
  {
    cub->map.tab[i] = (char *)malloc(sizeof(char) * 100);
    i++;
  }
  cub->map.tab[0] = ft_strcpy(cub->map.tab[0], "111111111111111");
  cub->map.tab[1] = ft_strcpy(cub->map.tab[1], "100000010000001");
  cub->map.tab[2] = ft_strcpy(cub->map.tab[2], "100000000000001");
  cub->map.tab[3] = ft_strcpy(cub->map.tab[3], "101000000000011");
  cub->map.tab[4] = ft_strcpy(cub->map.tab[4], "111111111111111");
  cub->map.height = 5;
  cub->map.width = 15;
  cub->mlx.ceiling_color = 0x0000FF;
  cub->mlx.floor_color = 0xFF0000;
}

void  ft_put_font(t_cub *cub)
{
  int  tmp;

  if (cub->mlx.pixel_bits != 32)
  {
    cub->mlx.floor_color = mlx_get_color_value(cub->mlx.ptr, cub->mlx.floor_color);
    cub->mlx.ceiling_color = mlx_get_color_value(cub->mlx.ptr, cub->mlx.ceiling_color);
  }
  tmp = cub->mlx.ceiling_color;
  while (cub->mlx.y < WIN_HEIGHT)
  {
    cub->mlx.x = 0;
    if (cub->mlx.y == WIN_HEIGHT / 2)
      tmp = cub->mlx.floor_color;
    while (cub->mlx.x < WIN_WIDTH)
    {
      cub->mlx.pixel_bits = (cub->mlx.y * cub->mlx.line_bytes) + (cub->mlx.x * 4);
      if (cub->mlx.endian == 1)
      {
        cub->mlx.buffer[cub->mlx.pixel_bits] = tmp >> 24;
        cub->mlx.buffer[cub->mlx.pixel_bits + 1] = (tmp >> 16) & 0xFF;
        cub->mlx.buffer[cub->mlx.pixel_bits + 2] = (tmp >> 8) & 0xFF;
        cub->mlx.buffer[cub->mlx.pixel_bits + 3] = tmp & 0xFF;
      }
      else if (cub->mlx.endian == 0)
      {
        cub->mlx.buffer[cub->mlx.pixel_bits] = tmp & 0xFF;
        cub->mlx.buffer[cub->mlx.pixel_bits + 1] = (tmp >> 8) & 0xFF;
        cub->mlx.buffer[cub->mlx.pixel_bits + 2] = (tmp >> 16) & 0xFF;
        cub->mlx.buffer[cub->mlx.pixel_bits + 3] = tmp >> 24;
      }
      cub->mlx.x++;
    }
    cub->mlx.y++;
  }
}

void  ft_put_line(t_cub *cub)
{
  int i;

  i = cub->mlx.draw_start;
  while (i < cub->mlx.draw_end)
  {
    cub->mlx.pixel_bits = (i * cub->mlx.line_bytes) + (cub->mlx.x * 4);
    if (cub->mlx.endian == 1)
    {
      cub->mlx.buffer[cub->mlx.pixel_bits] = cub->mlx.color >> 24;
      cub->mlx.buffer[cub->mlx.pixel_bits + 1] = (cub->mlx.color >> 16) & 0xFF;
      cub->mlx.buffer[cub->mlx.pixel_bits + 2] = (cub->mlx.color >> 8) & 0xFF;
      cub->mlx.buffer[cub->mlx.pixel_bits + 3] = cub->mlx.color & 0xFF;
    }
    else if (cub->mlx.endian == 0)
    {
      cub->mlx.buffer[cub->mlx.pixel_bits] = cub->mlx.color & 0xFF;
      cub->mlx.buffer[cub->mlx.pixel_bits + 1] = (cub->mlx.color >> 8) & 0xFF;
      cub->mlx.buffer[cub->mlx.pixel_bits + 2] = (cub->mlx.color >> 16) & 0xFF;
      cub->mlx.buffer[cub->mlx.pixel_bits + 3] = cub->mlx.color >> 24;
    }
    i++;
  }
}

void  ft_put_wall(t_cub *cub)
{
  while (cub->mlx.x < WIN_WIDTH)
  {
    cub->player.camera_x = 2 * cub->mlx.x / (double)WIN_WIDTH - 1;
    cub->player.ray_x = cub->player.dir_x + cub->player.plane_x * cub->player.camera_x;
    cub->player.ray_y = cub->player.dir_y + cub->player.plane_y * cub->player.camera_x;
    cub->player.map_x = cub->player.pos_x;
    cub->player.map_y = cub->player.pos_y;
    if (cub->player.ray_x == 0)
      cub->player.delta_x = 1e30;
    else
      cub->player.delta_x = abs((int)(1 / cub->player.ray_x));
    if (cub->player.ray_y == 0)
      cub->player.delta_y = 1e30;
    else
      cub->player.delta_y = abs((int)(1 / cub->player.ray_y));
    cub->player.hit = 0;
    if (cub->player.ray_x < 0)
    {
      cub->player.step_x = -1;
      cub->player.side_x = (cub->player.pos_x - cub->player.map_x) * cub->player.delta_x;
    }
    else
    {
      cub->player.step_x = 1;
      cub->player.side_x = (cub->player.map_x + 1.0 - cub->player.pos_x) * cub->player.delta_x;
    }
    if (cub->player.ray_y < 0)
    {
      cub->player.step_y = -1;
      cub->player.side_y = (cub->player.pos_y - cub->player.map_y) * cub->player.delta_y;
    }
    else
    {
      cub->player.step_y = 1;
      cub->player.side_y = (cub->player.map_y + 1.0 - cub->player.pos_y) * cub->player.delta_y;
    }
    while (cub->player.hit == 0)
    {
      if (cub->player.side_x < cub->player.side_y)
      {
        cub->player.side_x += cub->player.delta_x;
        cub->player.map_x += cub->player.step_x;
        cub->player.side = 0;
      }
      else
      {
        cub->player.side_y += cub->player.delta_y;
        cub->player.map_y += cub->player.step_y;
        cub->player.side = 1;
      }
      if (cub->map.tab[cub->player.map_x][cub->player.map_y] == '1')
        cub->player.hit = 1;
    }
    if (cub->player.side == 0)
      cub->player.wall = (cub->player.side_x - cub->player.delta_x);
    else
      cub->player.wall = (cub->player.side_y - cub->player.delta_y);
    cub->mlx.line_height = (int)(WIN_HEIGHT / cub->player.wall);
    cub->mlx.draw_start = -cub->mlx.line_height / 2 + WIN_HEIGHT / 2;
    if (cub->mlx.draw_start < 0)
      cub->mlx.draw_start = 0;
    cub->mlx.draw_end = cub->mlx.line_height / 2 + WIN_HEIGHT / 2;
    if (cub->mlx.draw_end >= WIN_HEIGHT)
      cub->mlx.draw_end = WIN_HEIGHT - 1;
    cub->mlx.color = 0x00FF00;
    if (cub->player.side == 1)
      cub->mlx.color = cub->mlx.color / 2;
    ft_put_line(cub);
    cub->mlx.x++;
  }
}

int  ft_key(int code, t_cub *cub)
{
  double  tmp;

  if (code == 119)
  {
    if (cub->map.tab[(int)(cub->player.pos_x + cub->player.dir_x * cub->player.move_speed)][(int)cub->player.pos_x] == '0')
      cub->player.pos_x += cub->player.dir_x * cub->player.move_speed;
    if (cub->map.tab[(int)cub->player.pos_x][(int)(cub->player.pos_y + cub->player.dir_y * cub->player.move_speed)] == '0')
      cub->player.pos_y += cub->player.dir_y * cub->player.move_speed;
  }
  else if (code == 97)
  {
    tmp = cub->player.dir_x;
    cub->player.dir_x = cub->player.dir_x * cos(cub->player.rot_speed) - cub->player.dir_y * sin(cub->player.rot_speed);
    cub->player.dir_y = tmp * sin(cub->player.rot_speed) + cub->player.dir_y * cos(cub->player.rot_speed);
    tmp = cub->player.plane_x;
    cub->player.plane_x = cub->player.plane_x * cos(cub->player.rot_speed) - cub->player.plane_y * sin(cub->player.rot_speed);
    cub->player.plane_y = tmp * sin(cub->player.rot_speed) + cub->player.plane_y * cos(cub->player.rot_speed);
  }
  else if (code == 115)
  {
    if (cub->map.tab[(int)(cub->player.pos_x - cub->player.dir_x * cub->player.move_speed)][(int)cub->player.pos_y] == '0')
      cub->player.pos_x -= cub->player.dir_x * cub->player.move_speed;
    if (cub->map.tab[(int)cub->player.pos_x][(int)(cub->player.pos_y - cub->player.dir_y * cub->player.move_speed)] == '0')
      cub->player.pos_y -= cub->player.dir_y * cub->player.move_speed;
  }
  else if (code == 100)
  {
    tmp = cub->player.dir_x;
    cub->player.dir_x = cub->player.dir_x * cos(-cub->player.rot_speed) - cub->player.dir_y * sin(-cub->player.rot_speed);
    cub->player.dir_y = tmp * sin(-cub->player.rot_speed) + cub->player.dir_y * cos(-cub->player.rot_speed);
    tmp = cub->player.plane_x;
    cub->player.plane_x = cub->player.plane_x * cos(-cub->player.rot_speed) - cub->player.plane_y * sin(-cub->player.rot_speed);
    cub->player.plane_y = tmp * sin(-cub->player.rot_speed) + cub->player.plane_y * cos(-cub->player.rot_speed);
  }
  return (0);
}

void  ft_time(t_cub *cub)
{
  cub->player.move_speed = 5.0;
  cub->player.rot_speed = 3.0;
}

void  ft_cub3d(t_cub *cub)
{
  cub->mlx.image = mlx_new_image(cub->mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
  cub->mlx.buffer = mlx_get_data_addr(cub->mlx.image, &(cub->mlx.pixel_bits), &(cub->mlx.line_bytes), &(cub->mlx.endian));
  ft_put_font(cub);
  cub->mlx.x = 0;
  cub->mlx.y = 0;
  ft_put_wall(cub);
  mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->mlx.image, 0, 0);
  ft_time(cub);
  mlx_hook(cub->mlx.win, 2, 1L<<0, ft_key, cub);
  mlx_destroy_image (cub->mlx.ptr, cub->mlx.image);
  mlx_loop(cub->mlx.ptr);
}

int  main(int argc, char **argv)
{
  t_cub cub;

  (void)argc;
  (void)argv;
  ft_init(&cub);
  ft_parse(&cub);
  cub.mlx.ptr = mlx_init();
  cub.mlx.win = mlx_new_window(cub.mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
  ft_cub3d(&cub);
}
