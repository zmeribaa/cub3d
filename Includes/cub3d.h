/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:35:26 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/07/01 22:18:16 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <limits.h>
# include "../Includes/keys.h"
# include "../tools/libft.h"
# define TILESIZE 64
// # define FOV_ANGLE (60 * (M_PI / 180))
# define FOV_ANGLE 1.047197551
# define WALL_STRIP_WIDTH 1
# define MINI_MAP_SCALE 0.2
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFF00
# define PURPLE 0xFF00FF
# define CYAN 0x00FFFF
# define MATRIX 0x00ff2b
# define LAVA 0xcf1020
# define VERTICAL 0
# define HORIZONTAL 1
# define NORTH_TEXTURE 0 
# define SOUTH_TEXTURE 1
# define WEST_TEXTURE 2
# define EAST_TEXTURE 3
# define USAGE 0
# define INVALID_MAP 1
# define PLAYER_NOT_FOUND 2
# define TEXTURE_NOT_FOUND 3
# define MULTILPLE_PLAYER 69
# define INVALID_COLOR 420

typedef struct s_texture
{
	char	*file;
	void	*img;
	int		*img_adr;
	int		*dir;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		img_width;
	int		img_height;
}			t_texture;

typedef struct s_map {
	int				map_height;
	unsigned int	map_width;
	int				ceiling_color;
	int				floor_color;
	char			*north_texture;
	int				south_texture;
	int				west_texture;
	int				east_texture;
	char			**map;
	int				error;
	int				lol;
	int				*texture_ptr;
	t_texture		*textures;

}	t_map;

typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
	int		x;
	int		y;
	t_map	map;
	int		width;
	int		height;
}				t_data;

typedef struct s_player {
	double	x;
	double	y;
	double	radius;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotate_speed;
	int		*rays;
	double	ray_angle;
	double	wall_hitx;
	double	wall_hity;
	double	distance;
	double	side_walk;
}	t_player;

typedef struct s_rgb {
	int		red;
	int		green;
	int		blue;
}	t_rgb;

typedef struct s_all
{
	struct s_data	*img;
	struct s_player	*player;
	t_map			map;
	int				num_rays;
	int				width;
	int				height;
}			t_all;

typedef struct s_intersection_point {
	float	x;
	float	y;
	float	distance;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	offset;
	int		found;
}	t_intersection_point;

typedef struct s_coordinates {
	double	x;
	double	y;
	double	width;
	double	height;
}	t_coordinates;

typedef struct s_ray {
	double	ray_angle;
	float	wall_hitx;
	float	wall_hity;
	double	distance;
	int		was_hit_vert;
	int		is_rayfacing_down;
	int		is_rayfacing_up;
	int		is_rayfacing_right;
	int		is_rayfacing_left;
	float	distanceprojplane;
	float	projectedwallheight;
	int		walltoppixel;
	int		wallbottompixel;
}	t_ray;
int						_die(int _type);
int						parse_map(char *map_file, t_all *all);
void					print_map_info(t_map *main_map);
int						add_line(t_map *_map, char *line);
void					grid(int x, int y, int color, t_data *img);
int						key_pressed(int key, t_all *all);
int						key_release(int key, t_all *all);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_player				*init_player(void);
int						update(t_all *all);
int						w_exit(int key);
int						has_wall(float x, float y, t_all *all);
void					refresh(t_all *all);
void					line(t_coordinates c,
							int end_x, int end_y, t_data *img);
void					map_constructor(t_map *main_map);
t_intersection_point	collision_maths(int _type, t_ray *_ray, t_all *all);
void					cast_all_rays(t_all *all);
void					horizon(t_all *all);
double					normalize_angle(double angle);
float					distance(float x1, float y1, float x2, float y2);
void					init_all(t_all *all);
t_intersection_point	find_horizontal_point(t_all *all, t_ray *_ray);
t_intersection_point	find_vertical_point(t_all *all, t_ray *_ray);
void					draw_wall(t_ray _ray, t_coordinates c, t_all *all);
void					draw_ceiling(int walltoppixel, int x, t_all *all);
void					draw_floor(int y, int x, t_all *all);
void					save_ray(t_ray *_ray, t_intersection_point point, \
						float dist, int was_hit_vert);
t_ray					construct_ray(double ray_angle);
int						setplayerpos(t_all *all, char c);
int						read_single_texture(char *line, t_map *_map, int dir);
int						save_map_line(char *line, t_map *_map);
void					save_rgb(char *line, t_map *_map, t_rgb color);
int						is_player(char _p);
int						get_player_pos_loop(t_all *all, int i);
void					getplayerpos(t_all *all);
int						validate_map(t_all *all);
int						is_valid(char c);
#endif