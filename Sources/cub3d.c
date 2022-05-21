#include "../Includes/cub3d.h" 

int main(int argc, char **argv)
{
	t_all *all;

	all = (t_all *)malloc(sizeof(t_all));
	int rt; 
	if (argc != 2)
		return _die(0);
	map_constructor(&all->map);
	if ((rt = parse_map(argv[1], &all->map)) != 0)
		return _die(rt);
	all->height = all->map.map_height * TILESIZE , all->width = all->map.map_width * TILESIZE;
	all->num_rays = all->width / WALL_STRIP_WIDTH;

	all->img = malloc(sizeof(t_data) * 1);
	all->img->mlx = mlx_init();
	all->img->mlx_win = mlx_new_window(all->img->mlx, all->width, all->height, "Map2D");
	all->img->img = mlx_new_image(all->img->mlx, all->width, all->height);
	all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bits_per_pixel, &all->img->line_length,
								&all->img->endian);
	all->player = init_player(all->map.map_width * TILESIZE / 2,all->map.map_height * TILESIZE / 2,10,0,0, M_PI / 2, 3.0, 2 * (M_PI / 180));
	mlx_loop_hook(all->img->mlx, update, all);
	mlx_loop(all->img->mlx);

	return (1);
}