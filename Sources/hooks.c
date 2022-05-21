/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:19:56 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/21 13:36:23 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int Wexit(int key)
{
	if (key == K_ESCAPE)
		exit(0);
	return (0);
}

int	key_pressed(int key, t_all *all)
{
	if (key == K_ESCAPE)
		exit(0);
	if (key == K_UP)
		all->player->walkDirection = 1;
	else if (key == K_DOWN)
		all->player->walkDirection = -1;
	else if (key == K_RIGHT)
		all->player->turnDirection = 1;
	else if (key == K_LEFT)
		all->player->turnDirection = -1;
	return (0);
}

int	key_release(int key, t_all *all)
{
	if (key == K_UP)
		all->player->walkDirection = 0;
	else if (key == K_DOWN)
		all->player->walkDirection = 0;
	else if (key == K_RIGHT)
		all->player->turnDirection = 0;
	else if (key == K_LEFT)
		all->player->turnDirection = 0;
	return (0);
}