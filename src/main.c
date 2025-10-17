#include "main.h"
#include "parse/parse.h"
#include <stdio.h>
#include <fcntl.h>

#define DEBUG 1




static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void draw_circle(mlx_image_t *img, int cx, int cy, uint32_t color)
{
	int	radius;

	radius = CIRCLE_RADIUS;
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                int px = cx + x;
                int py = cy + y;
                if (px >= 0 && px < (int)img->width && py >= 0 && py < (int)img->height)
                    mlx_put_pixel(img, px, py, color);
            }
        }
    }
}

// int draw_direction2d(t_game *game, int sx, int sy, uint32_t color)
// {
// 	int i = 0;
// 	int j = 0;
// 	int deltay = 0;
// 	int deltax = 0;
// 	// int m = 0;
// 	int steps = 0;
// 	double xinc = 0;
// 	double yinc = 0;

// 	deltax = game->cord[X] - sx;
// 	deltay = game->cord[Y] - sy;
// 	if (deltax > deltay)
// 		steps = deltax;
// 	else
// 		steps = deltay;
// 	while (i < SQUARE_LEN)
// 	{
// 		int j = 0;
// 		while (j < SQUARE_LEN)
// 		{
// 			mlx_put_pixel(game->img, j + rulex, i + ruley, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

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
	int tmp_x;
	int tmp_y;

	red   = 0xFF0000FF;
    green = 0x00FF00FF;
    black = 0x000000FF;
	rulex = 0;
	ruley = 0;
	if (x)
	    rulex = ((x * SQUARE_LEN) + x);
	if (y)
	    ruley = ((y * SQUARE_LEN) + y);
	if (flag == '1')
		color = black;
	else if (flag == '0')
		color = green;
	else if (flag == 'p' || flag == 'N')
	{
		color = green;
		tmp_x = rulex;
		tmp_y = ruley;

	}
	printf ("initial state : [%d , %d]\n", rulex, ruley);
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
	if (flag == 'p' || flag == 'N')
	{
		color = black;
		x = tmp_x + CENTER_RULE;
		y = tmp_y + CENTER_RULE;
		// draw_direction2d(game, x, y, color);
		color = red;
		draw_circle(game->img, x, y, color);
	}
}

int draw_2dmap (t_map *map, t_game *game)
{
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			draw_2dsquare(game, map->map[i][j], j, i);
		}
	}
	return 0;
}
// int right_rotate(t_game *game, t_map *map)
// {
	
// }

// int left_rotate(t_game *game, t_map *map)
// {

// }

void handle_input(void *param)
{
	t_game *game;

	game = (t_game*)param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx); // closes the window safely
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	right_rotate();
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	left_rotate();
	
}

int main(int ac, char **av) {
	t_map	*map;
	t_game	game;

	if (ac != 2) {
		puts("Usage: ./cub3d <path/to/map.cub>");
		return 1;
	}
	map = loadmap(av[1]);
	game.cord[X] = 90;
	game.cord[Y] = 0;
	// printf ("start mlx !\n");
	game.mlx = mlx_init(IMAC_WIDTH, IMAC_HEIGHT,"44", true);
	if (!game.mlx)
		ft_error();
	game.img = mlx_new_image(game.mlx, IMAC_WIDTH, IMAC_HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
		ft_error();
	draw_2dmap (map, &game);
	mlx_loop_hook(game.mlx, handle_input, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
