/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:49:53 by ziyad             #+#    #+#             */
/*   Updated: 2022/07/01 21:10:35 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"
#include "libft.h"

int	is_valid(char c)
{
	if (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	validate_map(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < all->map.map_height)
	{
		j = 0;
		while (all->map.map[i][j] != '\0')
		{
			if (is_valid(all->map.map[i][j]) == 0)
			{
				all->map.error = INVALID_MAP;
				return (all->map.error);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*no_white_space_strcpy(char *src)
{
	int		i;
	int		j;
	char	*dst;

	i = -1;
	j = 0;
	while (src[++i] != '\0')
	{
		if (ft_isspace(src[i]) == 0)
			j++;
	}
	dst = malloc((j + 1) * sizeof(char));
	i = -1;
	j = -1;
	while (src[++i] != '\0')
	{
		if (isspace(src[i]) == 0)
			dst[++j] = src[i];
	}
	dst[++j] = '\0';
	return (dst);
}

int	add_line(t_map *_map, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	_map->map_height++;
	new_map = malloc((sizeof(char *) * (_map->map_height + 1)));
	while (_map->map[i] != NULL)
	{
		new_map[i] = _map->map[i];
		i++;
	}
	new_map[i] = no_white_space_strcpy(line);
	if (strlen(new_map[i]) > _map->map_width)
		_map->map_width = strlen(new_map[i]);
	i++;
	new_map[i] = NULL;
	free(_map->map);
	_map->map = new_map;
	return (0);
}
