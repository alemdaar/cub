#include "main.h"
#include "parse/parse.h"
#include <stdio.h>
#include <fcntl.h>

#define DEBUG 1
#define IMAC_WIDTH 5120
#define IMAC_HEIGHT 2880
#define RED     0xFF0000FF
#define GREEN   0x00FF00FF
#define BLACK   0x000000FF
#define SQUARE_LEN   200


static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
void draw_2dsquare(t_game *game, char flag, int x, int y)
{
	int debug = open ("debug", O_CREAT | O_RDWR, 0777) ;
	if (debug == -1)
	{
		fprintf (stderr, "err debug file");
		exit (1);
	}
	uint32_t	red;
    uint32_t	green;
    uint32_t	black;
    uint32_t	color;
	int			rulex;
	int			ruley;

	red   = 0xFF0000FF; // Red (RGBA)
    green = 0x00FF00FF; // Green (RGBA)
    black = 0x000000FF; // Black (RGBA)
	rulex = 0;
	ruley = 0;
	if (x)
	    rulex = ((x * SQUARE_LEN) + (x + 10));
	if (y)
	    ruley = ((y * SQUARE_LEN) + (y + 10));
	if (flag == '1')
		color = black;
	else if (flag == '0')
		color = green;
	else
		color = red;
	printf ("flag : %c\n", flag);
	printf ("x : %d\n", x);
	printf ("y : %d\n", y);
	printf ("y + ruley : %d\n", ruley);
	printf ("y + rulex : %d\n", rulex);
	// while (1);
	for (int i = 0; i < SQUARE_LEN; i++)
	{
		for (int j = 0; j < SQUARE_LEN; j++)
		{
			mlx_put_pixel(game->img, x + rulex, j + ruley, color);
			
		}
	}
}

int draw_2dmap (t_map *map, t_game *game)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			draw_2dsquare(game, map->map[i][j], i, j);
		}
		printf (".................\n");
	}
	return 0;
}

int main(int ac, char **av) {
	t_map	*map;
	t_game	game;

	if (ac != 2) {
		puts("Usage: ./cub3d <path/to/map.cub>");
		return 1;
	}
	map = loadmap(av[1]);
	#ifdef DEBUG
	printf("NO %s", map->npath);
	printf("SO %s", map->spath);
	printf("WE %s", map->wpath);
	printf("EA %s", map->epath);
	printf("F: %d %d %d\n", map->fcolor >> 16 & 0xff, map->fcolor >> 8 & 0xff,
		   map->fcolor & 0xff);
	printf("C: %d %d %d", map->ccolor >> 16 & 0xff, map->ccolor >> 8 & 0xff,
		   map->ccolor & 0xff);
	for (int i = 0; map->map[i]; i++)
		printf("%s", map->map[i]);
	#endif
	game.mlx = mlx_init(IMAC_WIDTH, IMAC_HEIGHT,"44", true);
	if (!game.mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	game.img = mlx_new_image(game.mlx, IMAC_WIDTH, IMAC_HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	draw_2dmap (map, &game);
	// mlx_put_pixel(game.img, 0, 0, 0xFF0000FF);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(game.mlx, ft_hook, NULL);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
