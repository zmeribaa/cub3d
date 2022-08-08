/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:03:14 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/07/01 21:09:34 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 
#include "../tools/libft.h"
#include "../tools/get_next_line.h"

void	save_texture(char *line, t_map *_map)
{
	if (strlen(line) < 4)
	{
		_map->error = 1;
		return ;
	}
	if (line[0] == 'N' && line[1] == 'O')
		read_single_texture(line, _map, NORTH_TEXTURE);
	else if (line[0] == 'S' && line[1] == 'O')
		read_single_texture(line, _map, SOUTH_TEXTURE);
	else if (line[0] == 'W' && line[1] == 'E')
		read_single_texture(line, _map, WEST_TEXTURE);
	else if (line[0] == 'E' && line[1] == 'A')
		read_single_texture(line, _map, EAST_TEXTURE);
	else
		_map->error = 1;
}

void	save_color(char *line, t_map *_map)
{
	t_rgb	color;
	int		i;

	i = 1;
	while (isspace(line[i]))
		i++;
	color.red = atoi(&line[i]);
	while (isdigit(line[i]) || isspace(line[i]))
		i++;
	if (line[i] != ',')
	{
		_map->error = INVALID_COLOR;
		return ;
	}
	color.green = atoi(&line[++i]);
	while (isdigit(line[i]) || isspace(line[i]))
		i++;
	if (line[i] != ',')
	{
		_map->error = INVALID_COLOR;
		return ;
	}
	color.blue = atoi(&line[++i]);
	save_rgb(line, _map, color);
}

void	save_map(char *line, t_map *_map, int fd)
{
	int	rt;

	rt = 1;
	while (rt != 0)
	{
		if (!(save_map_line(line, _map)))
			break ;
		free(line);
		rt = get_next_line(fd, &line);
	}
	if (rt == 0)
	{
		save_map_line(line, _map);
		free(line);
		rt = get_next_line(fd, &line);
	}
	free(line);
}

int	parse_map_loop(char *line, t_map *_map, int fd)
{
	int	i;

	i = 0;
	while (isspace(line[i]))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		save_texture(&line[i], _map);
	else if (line[i] == 'F' || line[i] == 'C')
		save_color(&line[i], _map);
	else if (line[i] == '1' || line[i] == '0')
	{
		save_map(line, _map, fd);
		return (1);
	}
	else if (line[i] == '\0')
		return (2);
	else
		return (3);
	return (0);
}

int	parse_map(char *map_file, t_all *all)
{
	int		fd;
	char	*line;
	int		rt;

	all->map.error = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (2);
	while (get_next_line(fd, &line) != 0)
	{
		rt = parse_map_loop(line, &(all->map), fd);
		if (rt == 1)
			break ;
		else if (rt == 3)
			return (3);
		if (all->map.error != 0)
			return (all->map.error);
		free(line);
	}
	return (validate_map(all));
}
