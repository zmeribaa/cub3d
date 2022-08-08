/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyad <ziyad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:29:00 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/30 22:59:47 by ziyad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	setplayerpos(t_all *all, char c)
{
	if (c == 'N')
		all->player->rotation_angle = 90 * (M_PI / 2);
	if (c == 'S')
		all->player->rotation_angle = 270 * (M_PI / 2);
	if (c == 'E')
		all->player->rotation_angle = 0 * (M_PI / 2);
	if (c == 'W')
		all->player->rotation_angle = 180 * (M_PI / 2);
	return (1);
}
