/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyad <ziyad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:19:56 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/30 22:54:28 by ziyad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	w_exit(int key)
{
	key = 0;
	exit(0);
	return (0);
}

int	key_pressed(int key, t_all *all)
{
	if (key == K_ESCAPE)
		exit(0);
	if (key == K_W)
		all->player->walk_direction = 1;
	else if (key == K_S)
		all->player->walk_direction = -1;
	else if (key == K_RIGHT)
		all->player->turn_direction = 1;
	else if (key == K_LEFT)
		all->player->turn_direction = -1;
	else if (key == K_D)
	{
		all->player->walk_direction = 1;
		all->player->side_walk = 1.57;
	}
	else if (key == K_A)
	{
		all->player->walk_direction = 1;
		all->player->side_walk = -1.57;
	}
	return (0);
}

int	key_release(int key, t_all *all)
{
	if (key == K_W)
		all->player->walk_direction = 0;
	else if (key == K_S)
		all->player->walk_direction = 0;
	else if (key == K_RIGHT)
		all->player->turn_direction = 0;
	else if (key == K_LEFT)
		all->player->turn_direction = 0;
	else if (key == K_D)
	{
		all->player->walk_direction = 0;
		all->player->side_walk = 0;
	}
	else if (key == K_A)
	{
		all->player->walk_direction = 0;
		all->player->side_walk = 0;
	}
	return (0);
}
