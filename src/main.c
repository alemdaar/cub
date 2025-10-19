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

int draw_direction2d(t_game *game, int sx, int sy, uint32_t color)
{
    int dx = game->ep_dir[X] - sx;
    int dy = game->ep_dir[Y] - sy;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;
    double x = sx;
    double y = sy;
    for (int i = 0; i <= steps; i++) {
        mlx_put_pixel(game->img, round(x), round(y), color);
		// dprintf (3, "x : %f, y : %f\n", x, y);
        x += Xinc;
        y += Yinc;
    }
	return (0);
}

int pixelize(int x)
{
	if (x)
	    rulex = ((x * SQUARE_LEN) + x);
}
void draw_2dsquare(t_game *game, char flag, int x, int y)
{
	uint32_t	red;
    uint32_t	green;
    uint32_t	black;
	uint32_t	brown;
    uint32_t	color;
	int			rulex;
	int			ruley;
	int tmp_x;
	int tmp_y;

	red   = 0xFF0000FF;
    green = 0x00FF00FF;
    black = 0x000000FF;
	brown  = 0x8B4513FF;
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
	// printf ("initial state : [%d , %d]\n", rulex, ruley);
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
		// color = black;
		x = tmp_x + CENTER_RULE;
		y = tmp_y + CENTER_RULE;
		// dda(game, x, y, color);
		color = red;
		draw_circle(game->img, x, y, color);
	}
}

int draw_2dmap (t_game *game)
{
	t_map *map;

	map = game->map;
	for (int i = 0; i < MAP2D_LEN; i++)
	{
		for (int j = 0; j < MAP2D_LEN; j++)
		{
			// if (game)
			// 	printf ("game yes \n");
			// else
			// 	printf ("game no \n");
			// if (map->map[i][j])
			// 	printf ("map yes \n");
			// else
			// 	printf ("map no \n");
			draw_2dsquare(game, map, (game->player_pos[X] - 2) + j, (game->player_pos[Y] - 2) + i);
		}
	}
	return 0;
}
int right_rotate(t_game *game)
{
	if (game->ep_dir[Y] == 0 && game->ep_dir[X] < 180)
	{
		printf ("its upper !\n");
		game->ep_dir[X] += 1;
	}
	else if (game->ep_dir[X] == 180 && game->ep_dir[Y] < 180)
	{
		printf ("its top right !\n");
		game->ep_dir[Y] += 1;
	}
	else if (game->ep_dir[Y] == 180 && game->ep_dir[X] > 0)
	{
		printf ("its lower !\n");
		game->ep_dir[X] -= 1;
	}
	else
	{
		printf ("its top left !\n");
		game->ep_dir[Y] -= 1;
	}
	printf ("End point : [%d , %d]\n", game->ep_dir[X], game->ep_dir[Y]);
	return (0);
}

int left_rotate(t_game *game)
{
	if (game->ep_dir[Y] == 0 && game->ep_dir[X] > 0)
	{
		printf ("its upper !\n");
		game->ep_dir[X] -= 1;
	}
	else if (game->ep_dir[X] == 0 && game->ep_dir[Y] < 180)
	{
		printf ("its top left !\n");
		game->ep_dir[Y] += 1;
	}
	else if (game->ep_dir[Y] == 180 && game->ep_dir[X] < 180)
	{
		printf ("its lower !\n");
		game->ep_dir[X] += 1;
	}
	else
	{
		printf ("its top right !\n");
		game->ep_dir[Y] -= 1;
	}
	printf ("End point : [%d , %d]\n", game->ep_dir[X], game->ep_dir[Y]);
	return (0);
}

// int go_forward(t_game *game)
// {

// }

// int go_back(t_game *game)
// {

// }

// int go_right(t_game *game)
// {

// }

// int go_left(t_game *game)
// {

// }


void handle_input(void *param1)
{
	t_game *game;

	game = (t_game*)param1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx); // closes the window safely
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		right_rotate(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		left_rotate(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		go_forward(game);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	// 	go_left(game);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	// 	go_back(game);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	// 	go_right(game);
	draw_2dmap(game);
	return ;
}

int main(int ac, char **av) {
	t_map	*map;
	t_game	game;

	if (ac != 2) {
		puts("Usage: ./cub3d <path/to/map.cub>");
		return 1;
	}
	// printf ("start mlx !\n");
	game.map = map;
	map = loadmap(av[1], &game);
	game.mlx = mlx_init(IMAC_WIDTH_DEBUG, IMAC_HEIGHT,"44", true);
	if (!game.mlx)
		ft_error();
	game.img = mlx_new_image(game.mlx, IMAC_WIDTH_DEBUG, IMAC_HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
		ft_error();
	draw_2dmap (&game);
	mlx_loop_hook(game.mlx, handle_input, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
