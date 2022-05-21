#ifndef _CUB3D_H_
#define _CUB3D_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mlx.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include "../Includes/keys.h"

#define TILESIZE 32
#define FOV_ANGLE 60 * (M_PI / 180) // field of view its 60 degrees multiplied by PI/180 so we can work with radiant
#define WALL_STRIP_WIDTH 1

// colors

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define YELLOW 0xFFFF00
#define PURPLE 0xFF00FF
#define CYAN 0x00FFFF
#define MATRIX 0x00ff2b
#define	LAVA 0xcf1020



typedef struct map {
    int map_height;
    unsigned int map_width; // Max width
    unsigned long ceiling_color;
    unsigned long floor_color;
    int north_texture;
    int south_texture;
    int west_texture;
    int east_texture;
    char **map;
    int error;
    int lol;
} map;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
	int		x;
	int 	y;
    map     map;
}				t_data;

typedef struct s_player {
    int x;
	int y;
	int radius;
	int	turnDirection; // 1 = right, -1 = left
	int walkDirection; // 1 = forward, -1 = backward
	float rotationAngle;
	float moveSpeed;
	float rotateSpeed;
	int		*rays;
	int	rayAngle;
}               t_player;

typedef struct s_all
{
	struct s_data	*img;
	struct s_player	*player;
	struct map		map;

	int				num_rays;
	int				width;
	int				height;
}			t_all;

int _die(int _type);
int parse_map(char *map_file, map *_map);
void    print_map_info(map *main_map);
int add_line(map *_map, char *line);
void    grid(int x , int y, int color, t_data *img);
int key_pressed(int key,t_all *all);
int key_release(int key,t_all *all);
void wall(int x, int y, int color1, int color2, t_data *img);
void    draw_map(t_all *all);
void draw_walls(int x, int y, char wall, int color1, int color2, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_player(t_all *all);
void	circle_binkle(int x, int y, int r, int color, t_data *img);
t_player	*init_player(int x,int y,int radius, int	turnDirection ,int walkDirection, float rotationAngle, float moveSpeed ,float rotateSpeed);
int	update(t_all *all);
int Wexit(int key);
int	has_wall(float x, float y, t_all *all);
void refresh(t_all *all);
void	line(int begin_x, int begin_y, int end_x, int end_y, t_data *img);
void	circle_binkle(int x, int y, int r, int color, t_data *img);
void map_constructor(map *main_map);

#endif