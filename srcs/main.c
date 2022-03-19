#include "cub3d.h"

void  ft_init(t_cub *cub)
{
  int i;

  i = -1;
  cub->player.pos_x = 10.5;
  cub->player.pos_y = 10.5;
  cub->player.dir_x = -1;
  cub->player.dir_y = 0;
  cub->player.plane_x = 0;
  cub->player.plane_y = 0.66;
  cub->player.time = 0;
  cub->player.old_time = 0;
  cub->mlx.y = 0;
  cub->player.move_speed = 0.25;
  cub->player.rot_speed = 0.15;
  cub->key[0] = 0;
  cub->key[1] = 0;
  cub->key[2] = 0;
  cub->key[3] = 0;
}

int  ft_quit(t_cub *cub)
{
  (void)cub;
  exit(0);
}

void  ft_parse(t_cub *cub)
{
  int i;

  i = 0;
  cub->map = (char **)malloc(sizeof(char *) * 100);
  while (i < 100)
  {
    cub->map[i] = (char *)malloc(sizeof(char) * 100);
    i++;
  }
  cub->map[0] = ft_strcpy(cub->map[0],   "        1111111111111111111111111");
  cub->map[1] = ft_strcpy(cub->map[1],   "        1000000000110000000000001");
  cub->map[2] = ft_strcpy(cub->map[2],   "        1011000001110000000000001");
  cub->map[3] = ft_strcpy(cub->map[3],   "        1001000000000000000000001");
  cub->map[4] = ft_strcpy(cub->map[4],   "111111111011000001110000000000001");
  cub->map[5] = ft_strcpy(cub->map[5],   "100000000011000001110111111111111");
  cub->map[6] = ft_strcpy(cub->map[6],   "11110111111111011100000010001");
  cub->map[7] = ft_strcpy(cub->map[7],   "11110111111111011101010010001");
  cub->map[8] = ft_strcpy(cub->map[8],   "11000000110101011100000010001");
  cub->map[9] = ft_strcpy(cub->map[9],   "10000000000000001100000010001");
  cub->map[10] = ft_strcpy(cub->map[10], "10000000000000001101010010001");
  cub->map[11] = ft_strcpy(cub->map[11], "1100000111010101111101111000111");
  cub->map[12] = ft_strcpy(cub->map[12], "11110111 1110101 101111010001");
  cub->map[13] = ft_strcpy(cub->map[13], "11111111 1111111 111111111111");
  cub->mlx.ceiling_color = 0x0000FF;
  cub->mlx.floor_color = 0xFF0000;
  cub->mlx.no = mlx_xpm_file_to_image(cub->mlx.ptr, "./no_texture.xpm", &(cub->mlx.no_w), &(cub->mlx.no_h));
  cub->mlx.so = mlx_xpm_file_to_image(cub->mlx.ptr, "./so_texture.xpm", &(cub->mlx.so_w), &(cub->mlx.so_h));
  cub->mlx.we = mlx_xpm_file_to_image(cub->mlx.ptr, "./we_texture.xpm", &(cub->mlx.we_w), &(cub->mlx.we_h));
  cub->mlx.ea = mlx_xpm_file_to_image(cub->mlx.ptr, "./ea_texture.xpm", &(cub->mlx.ea_w), &(cub->mlx.ea_h));
  if (cub->mlx.no == NULL || cub->mlx.so == NULL || cub->mlx.we == NULL || cub->mlx.ea == NULL)
  {
    printf("bad textures files\n");
    exit(1);
  }
}

void  ft_put_font(t_cub *cub)
{
  int           x;
  int           y;
  unsigned char *tmp;

  y = 0;
  tmp = (unsigned char *)&(cub->mlx.ceiling_color);
  while (y < WIN_HEIGHT)
  {
    x = 0;
    if (y == WIN_HEIGHT / 2)
      tmp = (unsigned char *)&(cub->mlx.floor_color);
    while (x < WIN_WIDTH)
    {
      cub->mlx.buffer[y * cub->mlx.line_bytes + x * cub->mlx.pixel_bits / 8] = tmp[0];
      cub->mlx.buffer[y * cub->mlx.line_bytes + x * cub->mlx.pixel_bits / 8 + 1] = tmp[1];
      cub->mlx.buffer[y * cub->mlx.line_bytes + x * cub->mlx.pixel_bits / 8 + 2] = tmp[2];
      x++;
    }
    y++;
  }
}

void  ft_put_line(t_cub *cub)
{
  long tmp;

  tmp = cub->mlx.y * cub->mlx.tex_line_bytes - WIN_HEIGHT / 2 * cub->mlx.tex_line_bytes + cub->mlx.line_height / 2 * cub->mlx.tex_line_bytes;
  cub->mlx.tex_y = tmp * cub->mlx.tex_h / cub->mlx.line_height / cub->mlx.tex_line_bytes;
  cub->mlx.buffer[cub->mlx.y * cub->mlx.line_bytes + cub->mlx.x * (cub->mlx.pixel_bits / 8)] = cub->mlx.tex_buff_img[cub->mlx.tex_y * cub->mlx.tex_line_bytes + cub->mlx.tex_x * (cub->mlx.tex_pixel_bits / 8)];
  cub->mlx.buffer[cub->mlx.y * cub->mlx.line_bytes + cub->mlx.x * (cub->mlx.pixel_bits / 8) + 1] = cub->mlx.tex_buff_img[cub->mlx.tex_y * cub->mlx.tex_line_bytes + cub->mlx.tex_x * (cub->mlx.tex_pixel_bits / 8) + 1];
  cub->mlx.buffer[cub->mlx.y * cub->mlx.line_bytes + cub->mlx.x * (cub->mlx.pixel_bits / 8) + 2] = cub->mlx.tex_buff_img[cub->mlx.tex_y * cub->mlx.tex_line_bytes + cub->mlx.tex_x * (cub->mlx.tex_pixel_bits / 8) + 2];
}

void  ft_key(t_cub *cub)
{
  double  tmp;

  if (cub->key[0])
  {
    if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x + (cub->player.dir_x * 1.1) * cub->player.move_speed)] == '0')
      cub->player.pos_x += cub->player.dir_x * cub->player.move_speed;
    if (cub->map[(int)(cub->player.pos_y + (cub->player.dir_y * 1.1) * cub->player.move_speed)][(int)cub->player.pos_x] == '0')
      cub->player.pos_y += cub->player.dir_y * cub->player.move_speed;
  }
  if (cub->key[3])
  {
    tmp = cub->player.dir_x;
    cub->player.dir_x = cub->player.dir_x * cos(cub->player.rot_speed) - cub->player.dir_y * sin(cub->player.rot_speed);
    cub->player.dir_y = tmp * sin(cub->player.rot_speed) + cub->player.dir_y * cos(cub->player.rot_speed);
    tmp = cub->player.plane_x;
    cub->player.plane_x = cub->player.plane_x * cos(cub->player.rot_speed) - cub->player.plane_y * sin(cub->player.rot_speed);
    cub->player.plane_y = tmp * sin(cub->player.rot_speed) + cub->player.plane_y * cos(cub->player.rot_speed);
  }
  if (cub->key[1])
  {
    if (cub->map[(int)cub->player.pos_y][(int)(cub->player.pos_x - cub->player.dir_x * cub->player.move_speed)] == '0')
      cub->player.pos_x -= cub->player.dir_x * cub->player.move_speed;
    if (cub->map[(int)(cub->player.pos_y - cub->player.dir_y * cub->player.move_speed)][(int)cub->player.pos_x] == '0')
      cub->player.pos_y -= cub->player.dir_y * cub->player.move_speed;
  }
  if (cub->key[2])
  {
    tmp = cub->player.dir_x;
    cub->player.dir_x = cub->player.dir_x * cos(-cub->player.rot_speed) - cub->player.dir_y * sin(-cub->player.rot_speed);
    cub->player.dir_y = tmp * sin(-cub->player.rot_speed) + cub->player.dir_y * cos(-cub->player.rot_speed);
    tmp = cub->player.plane_x;
    cub->player.plane_x = cub->player.plane_x * cos(-cub->player.rot_speed) - cub->player.plane_y * sin(-cub->player.rot_speed);
    cub->player.plane_y = tmp * sin(-cub->player.rot_speed) + cub->player.plane_y * cos(-cub->player.rot_speed);
  }
}

void  ft_put_wall(t_cub *cub)
{
  while (cub->mlx.x < WIN_WIDTH)
  {
    cub->player.camera_x = 2 * cub->mlx.x / (double)WIN_WIDTH - 1;
    cub->player.ray_x = cub->player.dir_x + cub->player.plane_x * cub->player.camera_x;
    cub->player.ray_y = cub->player.dir_y + cub->player.plane_y * cub->player.camera_x;
    cub->player.map_x = (int)(cub->player.pos_x);
    cub->player.map_y = (int)(cub->player.pos_y);
    cub->player.delta_x = fabs(1 / cub->player.ray_x);
    cub->player.delta_y = fabs(1 / cub->player.ray_y);
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
    cub->player.hit = 0;
    while (cub->player.hit == 0)
    {
      if (cub->player.side_x < cub->player.side_y)
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
      else
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
      if (cub->map[cub->player.map_y][cub->player.map_x] != '0')
        cub->player.hit = 1;
    }
    cub->mlx.tex_buff_img = mlx_get_data_addr(cub->mlx.texture, &(cub->mlx.tex_pixel_bits), &(cub->mlx.tex_line_bytes), &(cub->mlx.tex_endian));
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
      cub->mlx.wall_x = cub->player.pos_y + cub->player.wall * cub->player.ray_y;
    else
      cub->mlx.wall_x = cub->player.pos_x + cub->player.wall * cub->player.ray_x;
    cub->mlx.wall_x -= floor(cub->mlx.wall_x);
    cub->mlx.tex_x = (int)(cub->mlx.wall_x * (double)(cub->mlx.tex_w));
    cub->mlx.y = cub->mlx.draw_start;
    while (cub->mlx.y < cub->mlx.draw_end)
    {
      ft_put_line(cub);
      cub->mlx.y++;
    }
    cub->mlx.x++;
  }
}

int   ft_frame(t_cub *cub)
{
  cub->mlx.image = mlx_new_image(cub->mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
  cub->mlx.buffer = mlx_get_data_addr(cub->mlx.image, &(cub->mlx.pixel_bits), &(cub->mlx.line_bytes), &(cub->mlx.endian));
  ft_put_font(cub);
  cub->mlx.x = 0;
  ft_key(cub);
  ft_put_wall(cub);
  mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->mlx.image, 0, 0);
  mlx_destroy_image(cub->mlx.ptr, cub->mlx.image);
  return (0);
}

int   ft_press(int code, t_cub *cub)
{
  if (code == UP)
    cub->key[0] = 1;
  if (code == DOWN)
    cub->key[1] = 1;
  if (code == RIGHT)
    cub->key[2] = 1;
  if (code == LEFT)
    cub->key[3] = 1;
  if (code == ESC)
    ft_quit(cub);
  return (0);
}

int   ft_release(int code, t_cub *cub)
{
    if (code == UP)
    cub->key[0] = 0;
  if (code == DOWN)
    cub->key[1] = 0;
  if (code == RIGHT)
    cub->key[2] = 0;
  if (code == LEFT)
    cub->key[3] = 0;
  return (0);
}

void  ft_cub3d(t_cub *cub)
{
  mlx_loop_hook(cub->mlx.ptr, ft_frame, cub);
  mlx_hook(cub->mlx.win, 2, 1L<<0, ft_press, cub);
  mlx_hook(cub->mlx.win, 3, 1L<<1, ft_release, cub);
  mlx_hook(cub->mlx.win, 17, 0L, ft_quit, cub);
  mlx_loop(cub->mlx.ptr);
}

int  main(int argc, char **argv)
{
  t_cub cub;

  (void)argc;
  (void)argv;
  cub.mlx.ptr = mlx_init();
  ft_init(&cub);
  ft_parse(&cub);
  cub.mlx.win = mlx_new_window(cub.mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
  ft_cub3d(&cub);
  return (0);
}
