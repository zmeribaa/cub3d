#include "../Includes/cub3d.h" 

int _die(int _type)
{
	printf("Error\n");
	if (_type == 0)
		printf("%s", "Usage: ./cub3d [map]");
	if (_type == 1)
		printf("%s", "Invalid map extension\n");
	return (1);
}