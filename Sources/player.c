/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:36:19 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/07/01 22:17:58 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	is_player(char _p)
{
	return (_p == 'N' || _p == 'S' || _p == 'E' || _p == 'W');
}

int	get_player_pos_loop(t_all *all, int i)
{
	int	j;

	j = 0;
	while (all->map.map[i][j] != '\0')
	{
		if (is_player(all->map.map[i][j]))
		{
			if (all->player->x != 0)
			{
				all->map.error = MULTILPLE_PLAYER;
				return (0);
			}
			setplayerpos(all, all->map.map[i][j]);
			all->player->x = (j + 1) * TILESIZE - (TILESIZE / 2);
			all->player->y = (i + 1) * TILESIZE - (TILESIZE / 2);
		}
		j++;
	}
	return (1);
}

void	getplayerpos(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->map.map_height)
	{
		if (get_player_pos_loop(all, i) == 0)
			return ;
		i++;
	}
	if (all->player->x == 0)
	{
		all->map.error = PLAYER_NOT_FOUND;
		return ;
	}
}

void	move(t_all *all)
{
	int		move_step;
	float	new_x;
	float	new_y;

	move_step = all->player->walk_direction * all->player->move_speed;
	new_x = all->player->x
		+ (cos(all->player->rotation_angle
				+ all->player->side_walk) * move_step);
	new_y = all->player->y
		+ (sin(all->player->rotation_angle
				+ all->player->side_walk) * move_step);
	if (!has_wall(new_x + 5, all->player->y, all)
		&& !has_wall(new_x - 5, all->player->y, all))
		all->player->x = new_x;
	if (!has_wall(all->player->x, new_y + 5, all)
		&& !has_wall(all->player->x, new_y - 5, all))
		all->player->y = new_y;
	all->player->rotation_angle += (all->player->turn_direction
			* all->player->rotate_speed);
}

int	update(t_all *all)
{
	mlx_hook(all->img->mlx_win, 2, 1L << 0, key_pressed, all);
	mlx_hook(all->img->mlx_win, 3, 1L << 1, key_release, all);
	mlx_hook(all->img->mlx_win, 17, 1L << 17, w_exit, all);
	move(all);
	cast_all_rays(all);
	mlx_put_image_to_window(all->img->mlx,
		all->img->mlx_win, all->img->img, 0, 0);
	refresh(all);
	return (0);
}
