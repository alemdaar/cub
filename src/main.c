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
	uint32_t	red;
    uint32_t	green;
    uint32_t	black;
    uint32_t	color;
	int			rulex;
	int			ruley;

	red   = 0xFF0000FF;
    green = 0x00FF00FF;
    black = 0x000000FF;
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
	int i = 0;
	int j = 0;
	while (i < SQUARE_LEN)
	{
		int j = 0;
		while (j < SQUARE_LEN)
		{
			mlx_put_pixel(game->img, j + rulex, i + ruley, color);
			j++;
		}
		i++;
	}
}

int draw_2dmap (t_map *map, t_game *game)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			draw_2dsquare(game, map->map[i][j], j, i);
		}
	}
	return 0;
}

void handle_input(void* param)
{
    mlx_t* mlx = (mlx_t*)param;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx); // closes the window safely
}

int main(int ac, char **av) {
	t_map	*map;
	t_game	game;

	if (ac != 2) {
		puts("Usage: ./cub3d <path/to/map.cub>");
		return 1;
	}
	map = loadmap(av[1]);
	printf ("start mlx !\n");
	game.mlx = mlx_init(IMAC_WIDTH, IMAC_HEIGHT,"44", true);
	if (!game.mlx)
		ft_error();
	game.img = mlx_new_image(game.mlx, IMAC_WIDTH, IMAC_HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
		ft_error();
	draw_2dmap (map, &game);
	mlx_loop_hook(game.mlx, handle_input, game.mlx);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
