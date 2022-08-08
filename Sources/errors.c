/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyad <ziyad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:32:17 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/06/30 20:20:18 by ziyad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	_die(int _type)
{
	printf("Error\n");
	if (_type == USAGE)
		printf("%s", "Usage: ./cub3d [map]");
	else if (_type == INVALID_MAP)
		printf("%s", "Invalid map extension\n");
	else if (_type == PLAYER_NOT_FOUND)
		printf("%s", "Player not found\n");
	else if (_type == TEXTURE_NOT_FOUND)
		printf("%s", "Texture not found\n");
	else if (_type == MULTILPLE_PLAYER)
		printf("%s", "Multiple players\n");
	else if (_type == INVALID_COLOR)
		printf("%s", "Invalid ceiling / floor color\n");
	return (1);
}
