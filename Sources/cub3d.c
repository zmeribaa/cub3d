/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmeribaa <zmeribaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:05:06 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/07/01 21:17:42 by zmeribaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h" 

int	save_single_texture(t_all *all, int direction)
{
	all->map.textures[direction].img = \
	mlx_xpm_file_to_image(all->img->mlx, all->map.textures[direction].file, \
	&all->map.textures[direction].img_width, \
	&all->map.textures[direction].img_height);
	if (all->map.textures[direction].img == NULL)
		return (1);
	all->map.textures[direction].img_adr = \
	(int *)mlx_get_data_addr(all->map.textures[direction].img, \
	&all->map.textures[direction].pixel_bits, \
	&all->map.textures[direction].line_bytes, \
	&all->map.textures[direction].endian);
	return (0);
}

int	save_textures(t_all *all)
{
	int	rt;

	rt = 0;
	rt += save_single_texture(all, NORTH_TEXTURE);
	rt += save_single_texture(all, SOUTH_TEXTURE);
	rt += save_single_texture(all, EAST_TEXTURE);
	rt += save_single_texture(all, WEST_TEXTURE);
	if (rt > 0)
		return (1);
	return (0);
}

/*void    print_map_info(t_map *main_map)
{
    printf("Map height: %d\n", main_map->map_height);
    printf("Map width: %d\n", main_map->map_width);
    printf("ceiling_colort: %d\n", main_map->ceiling_color);
    printf("floor_color: %d\n", main_map->floor_color);
    printf("north_texturet: %s\n", main_map->north_texture);
    printf("south_texture: %d\n", main_map->south_texture);
    printf("west_texture: %d\n", main_map->west_texture);
    printf("east_texture: %d\n", main_map->east_texture);
    printf("Map: \n");
    while (*(main_map->map) != NULL)
    {
       printf("%s\n", *(main_map->map));
        main_map->map++;
    }
    printf("Error code: %d\n",  main_map->error);
}*/

int	main(int argc, char **argv)
{
	t_all	*all;
	int		rt;

	all = (t_all *)malloc(sizeof(t_all));
	if (argc != 2)
		return (_die(USAGE));
	map_constructor(&all->map);
	rt = parse_map(argv[1], all);
	if (rt != 0)
		return (_die(all->map.error));
	all->img = malloc(sizeof(t_data) * 1);
	all->player = init_player();
	getplayerpos(all);
	if (all->map.error != 0)
		return (_die(all->map.error));
	init_all(all);
	rt = save_textures(all);
	if (rt != 0)
		return (_die(TEXTURE_NOT_FOUND));
	all->num_rays = all->width;
	all->img->width = all->width;
	all->img->height = all->height;
	mlx_loop_hook(all->img->mlx, update, all);
	mlx_loop(all->img->mlx);
	return (1);
}
