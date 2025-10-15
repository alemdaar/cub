#include "main.h"
#include "parse/parse.h"
#include <stdio.h>
#include <fcntl.h>

#define DEBUG 1
#define IMAC_WIDTH 5120
#define IMAC_HEIGHT 2880
#define RED     0xFF0000FF
#define GREEN   0x00FF00FF
#define BLACK	0x000000FF
#define SQUARE_LEN	35
#define PLAYER_LEN	15


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
	// printf ("as a start x : %d\n", x);
	// printf ("as a start y : %d\n", y);
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
	    rulex = ((x * SQUARE_LEN) + (x + 1));
	if (y)
	    ruley = ((y * SQUARE_LEN) + (y + 1));
	if (flag == '1')
		color = black;
	else if (flag == '0')
		color = green;
	else if (flag == 'p')
	{
		color = green;
		int tmp_x = x;
		int tmp_y = y;
		uint32_t tmp_color = red;

	}
	printf ("flag : %c\n", flag);
	// printf ("flag nb: %d\n", flag);
	printf ("x : %d\n", x);
	printf ("y : %d\n", y);
	printf ("ruley : %d\n", ruley);
	printf ("rulex : %d\n", rulex);
	// printf ("y + ruley : %d\n", y + ruley);
	// printf ("x + rulex : %d\n", x + rulex);
	int i = 0;
	int j = 0;
	while (i < SQUARE_LEN)
	{
		printf ("1***********************************\n");
		printf ("i : %d   , j = %d\n", i, j);
		int j = 0;
		while (j < SQUARE_LEN)
		{
			printf ("in loop [%d, %d]\n", j + rulex, i + ruley);
			mlx_put_pixel(game->img, j + rulex, i + ruley, color);
			j++;
		}
		i++;
		printf ("2***********************************\n");
	}
}

int draw_2dmap (t_map *map, t_game *game)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// printf ("data passed to the map : %c , %d, i = %d, j = %d\n", map->map[i][j], map->map[i][j], i, j);
			draw_2dsquare(game, map->map[i][j], j, i);
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
		printf("%s\n", map->map[i]);
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
