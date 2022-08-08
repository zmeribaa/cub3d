/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyad <ziyad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:18:29 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/30 22:48:17 by ziyad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

t_player	*init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->x = 0;
	player->y = 0;
	player->radius = 10;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = M_PI / 2;
	player->move_speed = 6.0;
	player->rotate_speed = 3 * (M_PI / 180);
	return (player);
}

void	refresh(t_all *all)
{
	mlx_destroy_image(all->img->mlx, all->img->img);
	all->img->img = mlx_new_image(all->img->mlx, all->width, all->height);
	all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bits_per_pixel,
			&all->img->line_length, &all->img->endian);
}

int	has_wall(float x, float y, t_all *all)
{
	float	map_grid_index_x;
	float	map_grid_index_y;

	if (x < 0 || x > (all->map.map_width * TILESIZE)
		|| y < 0 || y > (all->map.map_height * TILESIZE))
		return (1);
	map_grid_index_x = floor(x / TILESIZE);
	map_grid_index_y = floor(y / TILESIZE);
	if (map_grid_index_y >= (all->map.map_height)
		|| map_grid_index_x > strlen(all->map.map[(int)map_grid_index_y]))
		return (1);
	if (ft_isalpha(all->map.map[(int)map_grid_index_y][(int)map_grid_index_x]))
		return (0);
	return (all->map.map[(int)map_grid_index_y][(int)map_grid_index_x]
			!= '0');
}

void	map_constructor(t_map *main_map)
{
	main_map->map_height = 0;
	main_map->ceiling_color = CYAN;
	main_map->floor_color = 0x9b7653;
	main_map->north_texture = NULL;
	main_map->south_texture = -1;
	main_map->west_texture = -1;
	main_map->east_texture = -1;
	main_map->map_width = 0;
	main_map->map = malloc(sizeof(char *));
	main_map->map[0] = NULL;
	main_map->error = 0;
	main_map->textures = malloc(sizeof(t_texture) * 4);
}

void	init_all(t_all *all)
{
	all->width = 1200;
	all->height = 800;
	all->img->mlx = mlx_init();
	all->img->mlx_win = mlx_new_window(all->img->mlx,
			all->width, all->height, "Map2D");
	all->img->img = mlx_new_image(all->img->mlx, all->width, all->height);
	all->img->addr = mlx_get_data_addr(all->img->img,
			&all->img->bits_per_pixel,
			&all->img->line_length, &all->img->endian);
}
