#include "main.h"
#include "parse/parse.h"
#include <stdio.h>
#include <fcntl.h>

// #define DEBUG_KTP 1
// #define DEBUG_DS 1

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

// int dda(t_game *game, int sx, int sy, uint32_t color)
// {
//     int dx = game->ep_dir[X] - sx;
//     int dy = game->ep_dir[Y] - sy;
//     int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
//     double Xinc = dx / (double)steps;
//     double Yinc = dy / (double)steps;
//     double x = sx;
//     double y = sy;
//     for (int i = 0; i <= steps; i++) {
//         mlx_put_pixel(game->img, round(x), round(y), color);
//         x += Xinc;
//         y += Yinc;
//     }
// 	return (0);
// }
int draw_direction(t_game *game, uint32_t color)
{
	t_player *player;

	player = game->player;
	double x = player->sp_dir[X];
	double y = player->sp_dir[Y];
	int i = 0;
	while (i < 20)
	{
        mlx_put_pixel(game->img, round(x), round(y), color);
		x += player->pdx;
		y += player->pdy;
		i++;
	}
    // int dx = game->ep_dir[X] - sx;
    // int dy = game->ep_dir[Y] - sy;
    // int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    // double Xinc = dx / (double)steps;
    // double Yinc = dy / (double)steps;
    // double x = sx;
    // double y = sy;
    // for (int i = 0; i <= steps; i++) {
    //     mlx_put_pixel(game->img, round(x), round(y), color);
    //     x += Xinc;
    //     y += Yinc;
    // }
	return (0);
}

void draw_2dsquare(t_game *game, t_map *map, int x, int y)
{
	t_player	*player;
	uint32_t	red;
    uint32_t	green;
    uint32_t	black;
	uint32_t	brown;
    uint32_t	color;
	int j;
	int i;
	int			rulex;
	int			ruley;
	int tmp_x;
	int tmp_y;
	char flag;


	#ifdef DEBUG_DS
	printf ("x : %d\n", x);
	printf ("y : %d\n", y);
	printf ("map flag %c | nb = %d\n", map->map[y][x], map->map[y][x]);
	#endif
	player = game->player;
	red   = 0xFF0000FF;
    green = 0x00FF00FF;
    black = 0x000000FF;
	brown  = 0x8B4513FF;
	rulex = 0;
	ruley = 0;
	#ifdef DEBUG_KTP
	printf (".....\n");
	#endif
	flag = map->map[y][x];
	if (x)
	    rulex = (x * SQUARE_LEN);
	if (y)
	    ruley = (y * SQUARE_LEN);
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
	#ifdef DEBUG_DS
	printf ("rulex : %d\n", rulex);
	printf ("ruley : %d\n", ruley);
	#endif
	i = 0;
	while (i < 35)
	{
		j = 0;
		while (j < 35)
		{
			mlx_put_pixel(game->img, (j + rulex), (i + ruley), color);
			j++;
		}
		#ifdef DEBUG_DS
		// printf ("i : %d\n", i); // 34
		// printf ("j : %d\n", j); // 35
		#endif
		i++;
		
	}
	if (flag == 'P' || flag == 'N')
	{
		color = red;
		x = player->sp_dir[X];
		y = player->sp_dir[Y];
		draw_direction(game, color);
		draw_circle(game->img, x, y, color);
	}
}

int draw_2dmap (t_game *game)
{
	t_map *map;

	map = game->map;
	int i = 0;
	int j;
	while (i < 4)
	{
		j = 0;
		while (j < 18)
		{
			draw_2dsquare(game, map, j, i);
			j++;
		}
		i++;
	}
	return 0;
}
int right_rotate(t_player *player)
{
	player->pa -= 2;
	if (player->pa < 0)
	    player->pa += 360;
	player->pdx = cos(player->pa * M_PI / 180.0);
	player->pdy = -sin(player->pa * M_PI / 180.0);
	return (0);
}

int left_rotate(t_player *player)
{
	player->pa += 2;
	if (player->pa >= 360)
	    player->pa -= 360;
	player->pdx = cos(player->pa * M_PI / 180.0);
	player->pdy = -sin(player->pa * M_PI / 180.0);
	return (0);
}

int get_sqr(double pixel_cord)
{
	return ((int)pixel_cord / SQUARE_LEN);
}

int go_forward(t_game *game)
{
	t_player *player;
	t_map *map;
	int tmp1;
	int tmp2;

	player = game->player;
	map = game->map;
	map->map[player->sp_dir[Y]][player->sp_dir[X]]= '0';
	tmp1 = get_sqr(player->sp_dir[Y]);
	tmp2 = get_sqr(player->sp_dir[X] + player->pdx);
	if (map->map[tmp1][tmp2] != '1')
		player->sp_dir[X] += player->pdx;
	tmp1 = get_sqr(player->sp_dir[Y] + player->pdy);
	tmp2 = get_sqr(player->sp_dir[X]);
	if (map->map[tmp1][tmp2] != '1')
		player->sp_dir[Y] += player->pdy;
	player->player_pos[X] = get_sqr(player->sp_dir[X]);
	player->player_pos[Y] = get_sqr(player->sp_dir[Y]);
	map->map[player->sp_dir[Y]][player->sp_dir[X]]= 'P';

	return (0);
}

int go_back(t_game *game)
{
	t_player *player;

	player = game->player;
	// move backward (S key)
	player->sp_dir[X] -= player->pdx;
	player->sp_dir[Y] -= player->pdy;
	player->player_pos[X] = player->sp_dir[X] / SQUARE_LEN;
	player->player_pos[Y] = player->sp_dir[Y] / SQUARE_LEN;
	return (0);
}

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
		right_rotate(game->player);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		left_rotate(game->player);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		go_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		go_back(game);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	// 	go_left(game);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	// 	go_right(game);
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, IMAC_WIDTH_DEBUG, IMAC_HEIGHT);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	draw_2dmap(game);
	return ;
}

int main(int ac, char **av) {
	t_map		*map;
	t_game		game;
	t_player	player;

	if (ac != 2) {
		puts("Usage: ./cub3d <path/to/map.cub>");
		return 1;
	}
	// printf ("start !\n");
	// while (1);
	map = loadmap(av[1], &game, &player);
	printf ("11111\n");
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
