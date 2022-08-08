/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyad <ziyad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:50:03 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/30 20:30:45 by ziyad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

/*void	render_cast(t_ray _ray, t_all *all)
{
	t_coordinates	c;

	c.x = MINI_MAP_SCALE * all->player->x;
	c.y = MINI_MAP_SCALE * all->player->y;
	if (_ray.wall_hitx > 0 && _ray.wall_hity > 0)
		line(c, MINI_MAP_SCALE * _ray.wall_hitx, MINI_MAP_SCALE
			* _ray.wall_hity, all->img);
}*/

t_ray	cast( t_ray *_ray, t_all *all)
{
	t_intersection_point	vertical_point;
	t_intersection_point	horizontal_point;
	float					horz_dist;
	float					vert_dist;

	horizontal_point = find_horizontal_point(all, _ray);
	vertical_point = find_vertical_point(all, _ray);
	vert_dist = INT_MAX;
	if (vertical_point.found)
		vert_dist = distance(all->player->x, all->player->y, \
		vertical_point.x, vertical_point.y);
	horz_dist = INT_MAX;
	if (horizontal_point.found)
		horz_dist = distance(all->player->x, all->player->y, \
		horizontal_point.x, horizontal_point.y);
	if (horz_dist < vert_dist)
		save_ray(_ray, horizontal_point, horz_dist, 0);
	else
		save_ray(_ray, vertical_point, vert_dist, 1);
	return (*_ray);
}

void	render_walls(t_ray _ray, int x, t_all *all)
{
	t_coordinates	c;

	_ray.distanceprojplane = (all->width / 2) / tan(FOV_ANGLE / 2);
	_ray.projectedwallheight = (TILESIZE / ((double)_ray.distance * \
	cos(_ray.ray_angle - all->player->rotation_angle)))
		* _ray.distanceprojplane;
	_ray.walltoppixel = (all->height / 2)
		- ((int)(_ray.projectedwallheight) / 2);
	if (_ray.walltoppixel < 0)
		_ray.walltoppixel = 0;
	_ray.wallbottompixel = (all->height / 2)
		+ ((int)(_ray.projectedwallheight) / 2);
	if (_ray.wallbottompixel > all->height)
		_ray.wallbottompixel = all->height;
	c.y = _ray.walltoppixel;
	c.x = x;
	draw_ceiling(_ray.walltoppixel, x, all);
	draw_wall(_ray, c, all);
	draw_floor(_ray.wallbottompixel, x, all);
}

void	cast_all_rays(t_all *all)
{
	int		i;
	t_ray	*_rays;
	double	ray_angle;

	ray_angle = all->player->rotation_angle - (FOV_ANGLE / 2);
	_rays = malloc(sizeof(t_ray) * all->num_rays);
	i = 0;
	while (i < all->num_rays)
	{
		_rays[i] = construct_ray(ray_angle);
		_rays[i] = cast(&_rays[i], all);
		render_walls(_rays[i], i, all);
		ray_angle += FOV_ANGLE / all->num_rays;
		i++;
	}
	free(_rays);
}
