/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziyad <ziyad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:45:00 by ziyad             #+#    #+#             */
/*   Updated: 2022/06/30 22:45:01 by ziyad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 
#include "../tools/libft.h"
#include "../tools/get_next_line.h"

void	save_rgb(char *line, t_map *_map, t_rgb color)
{
	if (line[0] == 'F')
		_map->floor_color = ((color.red & 0xff) << 16)
			+ ((color.green & 0xff) << 8) + (color.blue & 0xff);
	else if (line[0] == 'C')
		_map->ceiling_color = ((color.red & 0xff) << 16)
			+ ((color.green & 0xff) << 8) + (color.blue & 0xff);
}

int	save_map_line(char *line, t_map *_map)
{
	int	i;

	i = 0;
	while (isspace(line[i]))
		i++;
	if (line[i] == '1')
		add_line(_map, line);
	else
		return (0);
	return (1);
}

int	read_single_texture(char *line, t_map *_map, int dir)
{
	int	i;

	i = 2;
	if (line[i] == ' ')
	{
		while (isspace(line[i]))
			i++;
		_map->textures[dir].file = ft_strdup(&line[i]);
		if (_map->textures[dir].file == NULL)
		{
			_map->error = 1;
			return (1);
		}
	}
	else
	{
		_map->error = 1;
		return (1);
	}
	return (0);
}
