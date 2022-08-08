/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyad <ziyad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:59:15 by ziyad             #+#    #+#             */
/*   Updated: 2022/06/30 22:47:32 by ziyad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	save_ray(t_ray *_ray, t_intersection_point point, \
float dist, int was_hit_vert)
{
	_ray->wall_hitx = point.x;
	_ray->wall_hity = point.y;
	_ray->distance = dist;
	_ray->was_hit_vert = was_hit_vert;
}

t_ray	construct_ray(double ray_angle)
{
	t_ray	_ray;

	_ray.ray_angle = normalize_angle(ray_angle);
	_ray.is_rayfacing_down = 0;
	_ray.is_rayfacing_up = 1;
	if (_ray.ray_angle > 0 && _ray.ray_angle < M_PI)
	{
		_ray.is_rayfacing_down = 1;
		_ray.is_rayfacing_up = 0;
	}
	_ray.is_rayfacing_right = 0;
	_ray.is_rayfacing_left = 1;
	if (_ray.ray_angle < (0.5 * M_PI) || _ray.ray_angle > (1.5 * M_PI))
	{
		_ray.is_rayfacing_right = 1;
		_ray.is_rayfacing_left = 0;
	}
	return (_ray);
}

t_intersection_point	find_horizontal_point(t_all *all, t_ray *_ray)
{
	t_intersection_point	h_p;

	h_p = collision_maths(HORIZONTAL, _ray, all);
	if (has_wall(h_p.x, h_p.y, all))
		h_p.found = 1;
	while (h_p.found != 1 && h_p.x >= 0 && h_p.x <= (all->map.map_width * \
	TILESIZE) && h_p.y >= 0 && h_p.y <= (all->map.map_height * TILESIZE))
	{
		h_p.offset = 0;
		if (_ray->is_rayfacing_up == 1)
			h_p.offset = 1;
		if (has_wall(h_p.x, (h_p.y - h_p.offset), all))
		{
			h_p.found = 1;
			break ;
		}
		else
		{
			h_p.x += h_p.xstep;
			h_p.y += h_p.ystep;
		}
	}
	return (h_p);
}

t_intersection_point	find_vertical_point(t_all *all, t_ray *_ray)
{
	t_intersection_point	v_p;

	v_p = collision_maths(VERTICAL, _ray, all);
	v_p.found = 0;
	if (has_wall(v_p.x, v_p.y, all))
		v_p.found = 1;
	while (v_p.found != 1 && v_p.x >= 0 && v_p.x <= (all->map.map_width * \
	TILESIZE) && v_p.y >= 0 && v_p.y <= (all->map.map_height * TILESIZE))
	{
		v_p.offset = 0;
		if (_ray->is_rayfacing_left == 1)
			v_p.offset = 1;
		if (has_wall((v_p.x - v_p.offset),
				v_p.y, all))
		{
			v_p.found = 1;
			break ;
		}
		else
		{
			v_p.x += v_p.xstep;
			v_p.y += v_p.ystep;
		}
	}
	return (v_p);
}
