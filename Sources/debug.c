#include "../Includes/cub3d.h" 


/**
 * @brief 
 * Use this function to to print everything parsed from the input file
 * @param map 
 */
void    print_map_info(map *main_map)
{
    printf("Map height: %d\n", main_map->map_height);
    printf("Map width: %d\n", main_map->map_width);
    printf("ceiling_colort: %lu\n", main_map->ceiling_color);
    printf("floor_color: %lu\n", main_map->floor_color);
    printf("north_texturet: %d\n", main_map->north_texture);
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
}