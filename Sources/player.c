/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:36:19 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/21 13:36:23 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

void move(t_all *all)
{
	int move_step;
	float new_x;
	float new_y;
	
	move_step = all->player->walkDirection * all->player->moveSpeed;
	new_x = all->player->x + (cos(all->player->rotationAngle) * move_step);
	new_y = all->player->y + (sin(all->player->rotationAngle) * move_step);
	if (!has_wall(new_x,new_y, all))
	{
		all->player->x = new_x;
		all->player->y = new_y;
	}
	all->player->rotationAngle += (all->player->turnDirection * all->player->rotateSpeed); 
}

int update(t_all *all)
{
	mlx_hook(all->img->mlx_win, 2, 1L<<0, key_pressed, all);
	mlx_hook(all->img->mlx_win, 3, 1L<<1, key_release, all);
	move(all);
	draw_map(all);
	draw_player(all);
	mlx_put_image_to_window(all->img->mlx, all->img->mlx_win, all->img->img, 0, 0);
	refresh(all);
	return (0);
}

void draw_player(t_all *all)
{
	circle_binkle(all->player->x, all->player->y, all->player->radius, BLACK, all->img);
	line(all->player->x , all->player->y, (all->player->x + (cos(all->player->rotationAngle)*20)),(all->player->y + (sin(all->player->rotationAngle)*20)), all->img);
}