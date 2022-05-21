/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:15:56 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/21 13:36:23 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

void    draw_map(t_all *all)
{
	int i;
	unsigned int j;
	int tile_x;
	int tile_y;
	
	i = 0;
	while (i < all->map.map_height)
	{
		j = 0;
		while (all->map.map[i][j] != '\0') // map_width is the width of the biggest line so better iterate on each line using this instead of size of width
		{
			tile_x = j * TILESIZE;
			tile_y = i * TILESIZE;
				if (all->map.map[i][j] == '1')
					wall(tile_x, tile_y, WHITE, TILESIZE, all->img);
				else if (all->map.map[i][j] == '0')
					wall(tile_x, tile_y, BLACK, TILESIZE, all->img);
			j++;
		}
		while (j < all->map.map_width) // Fill empty zones with a wall
		{
			tile_x = j * TILESIZE;
			tile_y = i * TILESIZE;
			wall(tile_x, tile_y, BLACK, TILESIZE, all->img);
			j++;
		}
		i++;
	}
}

