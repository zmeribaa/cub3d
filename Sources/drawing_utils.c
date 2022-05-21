/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 20:05:51 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/21 13:36:23 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	// if (x < 0 || x > data->map.map_width || y < 0 || y > data->map.map_height)
	// 	return ;
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void wall(int x, int y, int color1, int Tile_size, t_data *img)
{
	int j;
	int i;

	i = y;
	while (i < Tile_size + y)
	{
		j = x;
		while (j < Tile_size + x)
		{
			my_mlx_pixel_put(img, j, i, color1);
			j++;
		}
		i++;
	}
}

void	circle_binkle(int x, int y, int r, int color, t_data *img)
{
    double i, angle, x1, y1;
	int j = 0;
	while (j < r)
	{
		i = 0;
		while (i < 360)
		{
			angle = i;

			x1 = (j * cos(angle * M_PI / 180))/2;
			y1 = (j * sin(angle * M_PI / 180))/2;

			my_mlx_pixel_put(img, x + x1, y + y1, color);
			i += 0.1;
		}
		j++;
	}
}

void	line(int begin_x, int begin_y, int end_x, int end_y, t_data *img)
{
	double i;
	double j;
	double pixels_x;
	double pixels_y;
	int pixels;

	i = end_x - begin_x;
	j = end_y - begin_y;
	pixels = sqrt((i * i) + (j * j));
	i /= pixels;
	j /= pixels;
	pixels_x = begin_x;
	pixels_y = begin_y;
	while (pixels)
	{
		my_mlx_pixel_put(img, pixels_x, pixels_y, BLACK);
		pixels_x += i;
		pixels_y += j;
		--pixels;
	}
}

