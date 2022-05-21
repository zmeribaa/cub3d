/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:18:29 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/21 13:36:23 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

t_player	*init_player(int x,int y,int radius, int turnDirection ,int walkDirection,
						float rotationAngle, float moveSpeed ,float rotateSpeed)
{
	t_player *player;
	
	player = malloc(sizeof(t_player));
	player->x = x;
	player->y = y;
	player->radius = radius;
	player->turnDirection = turnDirection;
	player->walkDirection = walkDirection;
	player->rotationAngle = rotationAngle;
	player->moveSpeed = moveSpeed;
	player->rotateSpeed = rotateSpeed;
	
	return (player);
}

void refresh(t_all *all)
{
	
	mlx_destroy_image(all->img->mlx, all->img->img);
	all->img->img = mlx_new_image(all->img->mlx, all->width, all->height);
	all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bits_per_pixel, &all->img->line_length,
								&all->img->endian);
}

int	has_wall(float x, float y, t_all *all)
{
	float map_grid_index_x;
	float map_grid_index_y; 

	if (x < 0 || x > all->width || y < 0 || y > all->height)
		return (1);
	map_grid_index_x = floor(x / TILESIZE);
	map_grid_index_y = floor(y / TILESIZE);
	
	return (all->map.map[(int)map_grid_index_y][(int)map_grid_index_x] != '0');
}

void map_constructor(map *main_map)
{
	main_map->map_height = 0;
	main_map->ceiling_color = -1;
	main_map->floor_color = -1;
	main_map->north_texture = -1;
	main_map->south_texture = -1;
	main_map->west_texture = -1;
	main_map->east_texture = -1;
	main_map->map_width = 0;
	main_map->map = malloc(sizeof(char *));
	main_map->map[0] = NULL;
	main_map->error = 0;
}
