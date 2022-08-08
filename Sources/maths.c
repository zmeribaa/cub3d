/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:55:41 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/28 20:54:08 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

t_intersection_point	_vertical(t_ray *_ray, t_all *all)
{
	t_intersection_point	_point;

	_point.found = 0;
	_point.x = floor(all->player->x / TILESIZE) * TILESIZE;
	if (_ray->is_rayfacing_right == 1)
		_point.x += TILESIZE;
	_point.y = all->player->y + (_point.x - all->player->x) * \
	tan(_ray->ray_angle);
	_point.xstep = TILESIZE;
	if (_ray->is_rayfacing_left == 1)
		_point.xstep *= -1;
	_point.ystep = TILESIZE * tan(_ray->ray_angle);
	if (_ray->is_rayfacing_up && _point.ystep > 0)
		_point.ystep *= -1;
	if (_ray->is_rayfacing_down && _point.ystep < 0)
		_point.ystep *= -1;
	return (_point);
}

t_intersection_point	_horizontal(t_ray *_ray, t_all *all)
{
	t_intersection_point	_point;

	_point.found = 0;
	_point.y = floor(all->player->y / TILESIZE) * TILESIZE;
	if (_ray->is_rayfacing_down == 1)
		_point.y += TILESIZE;
	_point.x = all->player->x + (_point.y - all->player->y) / \
	tan(_ray->ray_angle);
	_point.ystep = TILESIZE;
	if (_ray->is_rayfacing_up == 1)
		_point.ystep *= -1;
	_point.xstep = TILESIZE / tan(_ray->ray_angle);
	if (_ray->is_rayfacing_left == 1 && _point.xstep > 0)
		_point.xstep *= -1;
	if (_ray->is_rayfacing_right == 1 && _point.xstep < 0)
		_point.xstep *= -1;
	return (_point);
}

t_intersection_point	collision_maths(int _type, t_ray *_ray, t_all *all)
{
	t_intersection_point	_point;

	if (_type == HORIZONTAL)
		_point = _horizontal(_ray, all);
	else
		_point = _vertical(_ray, all);
	return (_point);
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}
