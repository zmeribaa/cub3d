#include "../Includes/cub3d.h" 
#include "../tools/libft.h"
#include "../tools/get_next_line.h"


// To do: Have each texture parsing in a separate function as its repeated
void save_texture(char *line, map *_map)
{
    (void) line;
    (void) _map;
    int i;

    i = 0;

    // Validate texture, if error found save error code in _map->error code
    // Else open texture file, save fd i _map->fd
    // An example of a valid texture line is:
    // "NO ./path_to_the_north_texture"
    if (strlen(line) < 4)
    {
        _map->error = 1;
        return;
    }
    if (line[i] == 'N' && line[i+1] == 'O')
    {
        i += 2; // Skip the direction directive
        if (line[i] == ' ')
        {
            while (isspace(line[i]))
                i++;
            if ((_map->north_texture = open(&line[i], O_RDONLY)) == -1)
            {
                _map->error = 1;
                return;
            }
        }
        else
        {
            _map->error = 1;
            return;
        }
    }
    else if (line[i] == 'S' && line[i+1] == 'O')
    {
        i += 2; // Skip the direction directive
        if (line[i] == ' ')
        {
            while (isspace(line[i]))
                i++;
            if ((_map->south_texture = open(&line[i], O_RDONLY)) == -1)
            {
                _map->error = 1;
                return;
            }
        }
        else
        {
            _map->error = 1;
            return;
        }
    }
    else if (line[i] == 'W' && line[i+1] == 'E')
    {
        i += 2; // Skip the direction directive
        if (line[i] == ' ')
        {
            while (isspace(line[i]))
                i++;
            if ((_map->west_texture = open(&line[i], O_RDONLY)) == -1)
            {
                _map->error = 1;
                return;
            }
        }
        else
        {
            _map->error = 1;
            return;
        }
    }
    else if (line[i] == 'E' && line[i+1] == 'A')
    {
        i += 2; // Skip the direction directive
        if (line[i] == ' ')
        {
            while (isspace(line[i]))
                i++;
            if ((_map->east_texture = open(&line[i], O_RDONLY)) == -1)
            {
                _map->error = 1;
                return;
            }
        }
        else
        {
            _map->error = 1;
            return;
        }
    }
    else
    {
        _map->error = 1;
    }
}

// Check if there's a number before calling atoi
void save_color(char *line, map *_map)
{
    // Validate color, if error found save error code in _map->error code
    // Convert to hexa and save
    char *data;
    int red, green, blue;
    int i = 1;
    while (isspace(line[i]))
        i++;
    red = atoi(&line[i]);
    data = strchr(&line[i], ','); // Find first ',' delimiter
    if (data == NULL)
    {
        _map->error = 1;
        return;
    }
    green = atoi(++data);
    data = strchr(data, ','); // Find next ',' delimiter
    if (data == NULL)
    {
        _map->error = 1;
        return;
    }
    blue = atoi(++data);
    if (line[0] == 'F')
        _map->floor_color = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
    else if (line[0] == 'C')
        _map->ceiling_color = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
    //printf("Red: %d, Green: %d, Blue: %d\n", red, green, blue);
}

// Check if map is valid;
// Each line should start and end with a '1'
// First and last line should be 1's only
// No duplicate player positions are
void validate_map(map *_map)
{
    (void) _map;
}

void save_map(char *line, map *_map, int fd)
{
    int i;
    int rt;

    i = 0;
    rt = 1;
    // this skips the first line; To fix later
    printf("Function called\n");
    while (rt != 0)
    {
        i = 0;
        // Skip whitespaces
        while (isspace(line[i]))
            i++;
        if (line[i] == '1')
            add_line( _map,line);
        else
        {
            break;
        }
        free(line);
        rt = get_next_line(fd, &line);
    }
    if (rt == 0)
    {
        i = 0;
        // Skip whitespaces
        while (isspace(line[i]))
            i++;
        if (line[i] == '1')
            add_line( _map,line);
        free(line);
        rt = get_next_line(fd, &line);
    }
    validate_map(_map);
}

int parse_map(char *map_file, map *_map)
{
    //char *ret;
    int fd;
    char *line;
    int i;
    // To replace with str find
    // Check if extension is .cub
    //ret = strchr(map_file, ".cub"); 
    //if (ret == NULL || strlen(ret) != 4)
    //    return (1);
    // Check if file readable
    _map->error = 0;
    if ((fd = open(map_file, O_RDONLY)) == -1)
        return (2);
    // Check & save content: save textures, map & floor and cieling colors;
    line = NULL;
    while (get_next_line(fd, &line) != 0)
    {
        i = 0;
        // Skip whitespaces
        while (isspace(line[i]))
            i++;
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
            save_texture(&line[i], _map);
        else if (line[i] == 'F' || line[i] == 'C')
            save_color(&line[i], _map);
        else if (line[i] == '1' || line[i] == '0') // Maybe keep only '1' since a map can\t start with a 0 and then it will go directly to the else condition
        {
            save_map(line, _map, fd);
            break; // Skip everything else; As the map is the last thing to be parsed on .cub file;
        }
        else if (line[i] == '\0')
            continue; // Empty line continue
        else
            return (3); // Invalid line
        if (_map->error != 0)
            return (_map->error);
        free(line); // Bring back after double free fix
    }
    return (0);
}