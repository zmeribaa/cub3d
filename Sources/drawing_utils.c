/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyad <ziyad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 20:05:51 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/30 20:54:05 by ziyad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > data->width - 1 || y < 0 || y > data->height - 1)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_dir(t_ray _ray)
{
	if (_ray.is_rayfacing_up && !_ray.was_hit_vert)
		return (NORTH_TEXTURE);
	else if (_ray.is_rayfacing_left && _ray.was_hit_vert)
		return (EAST_TEXTURE);
	else if (_ray.is_rayfacing_down && !_ray.was_hit_vert)
		return (SOUTH_TEXTURE);
	else if (_ray.is_rayfacing_right && _ray.was_hit_vert)
		return (WEST_TEXTURE);
	return (0);
}

void	draw_wall(t_ray _ray, t_coordinates c, t_all *all)
{
	int	offsetx;
	int	offsety;
	int	distance;
	int	dir;

	dir = get_dir(_ray);
	if (_ray.was_hit_vert)
		offsetx = (int)(_ray.wall_hity) % TILESIZE;
	else
		offsetx = (int)(_ray.wall_hitx) % TILESIZE;
	while (c.y < _ray.wallbottompixel)
	{
		distance = (c.y + ((int)_ray.projectedwallheight / 2)
				- (all->height / 2));
		offsety = distance * ((float)TILESIZE / (int)_ray.projectedwallheight);
		my_mlx_pixel_put(all->img, c.x, c.y, \
			all->map.textures[dir].img_adr[TILESIZE * offsety + offsetx]);
		c.y++;
	}
}

void	draw_ceiling(int walltoppixel, int x, t_all *all)
{
	int	y;

	y = 0;
	while (y < walltoppixel)
	{
		my_mlx_pixel_put(all->img, x, y, all->map.ceiling_color);
		y++;
	}
}

void	draw_floor(int y, int x, t_all *all)
{
	while (y < all->height)
	{
		my_mlx_pixel_put(all->img, x, y, all->map.floor_color);
		y++;
	}
}
