#include "../Includes/cub3d.h"
#include "libft.h"

char *no_white_space_strcpy(char *src)
{
    int i = 0;
    int j = 0;
    char *dst;

    while (src[i] != '\0')
    {
        if (ft_isspace(src[i]) == 0)
            j++;
        i++;
    }
    dst = malloc((j + 1) * sizeof(char));
    i = 0;
    j = 0;
    while (src[i] != '\0')
    {
        if (isspace(src[i]) == 0)
        {
            dst[j] = src[i];
            j++; 
        }
        i++;
    }
    dst[j] = '\0';
    return dst;
}

// Helper functions to use a string in a dynamic array to use to same map;

// Add line: Adds another line to map 2d array
// Makes a copy, frees the old map and points to the new copy with an extra line
int add_line(map *_map, char *line)
{
    char **new_map;
    int i;
    (void)line;

    i = 0;
    _map->map_height++;
    new_map = malloc((sizeof(char *) * (_map->map_height + 1)));
    while(_map->map[i] != NULL)
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
    return 0;
}