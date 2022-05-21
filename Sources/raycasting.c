/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:50:03 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/21 13:36:23 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	function_ray(t_all *all, int rayAngle)
{
		all->player->rayAngle = rayAngle;
		return (rayAngle);
}

void	cast_all_rays(t_all *all)
{
	int i;
	int ray;
	int	clomunID;


	clomunID = 0;
	i = 0;
	// start first ray substracting half of the FOV laykhlef 3la pikuma
	all->player->rays = (int *)malloc(sizeof(int) * all->num_rays);
	all->player->rayAngle = all->player->rotationAngle - (FOV_ANGLE / 2);
	// loop all columns casting rays
	while (i < all->num_rays)
	{
		ray = function_ray(all,all->player->rayAngle);
		all->player->rayAngle += FOV_ANGLE / all->num_rays;
		clomunID ++;
		i++;
	}
}