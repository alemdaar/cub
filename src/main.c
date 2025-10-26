#include "main.h"
#include "parse/parse.h"
#include <stdio.h>
#include <fcntl.h>

// #define DEBUG_KTP 1
// #define DEBUG_DS 1
// #define DEBUG_MOVE 1
#define DEBUG_CAST_RAY 1
// #define DEBUG_CAST_RAY_PREV 1
#define DEBUG_RAY_ANGLE 1

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
                int px = (int)cx + x;
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

int get_sqr(double pixel_cord)
{
	return ((int)pixel_cord / SQUARE_LEN);
}

double get_pixel(int square_cord)
{
	return ((double)square_cord * (double)SQUARE_LEN);
}

int draw_direction(t_game *game, uint32_t color)
{
	t_player *player;
	t_map *map;

	player = game->player;
	map = game->map;
	double x = player->sp_dir[X];
	double y = player->sp_dir[Y];
	int i = 0;
	while (i < 70 && map->map[get_sqr(y)][get_sqr(x)] != '1')
	{
        mlx_put_pixel(game->img, round(x), round(y), color);
		x += player->pdx;
		y += player->pdy;
		i++;
	}
	return (0);
}

// int hit_wall(t_game *game, int ind, double x, double y, double pdx, double pdy, int debug)
// int hit_wall(t_game *game, int ind, double x, double y)
int hit_wall(t_game *game, int ind, double x, double y, int debug)
{
	t_map *map;

	map = game->map;
	int sqx = get_sqr (x);
	int sqy = get_sqr (y);
	if (map->map[sqy][sqx] == '1')
	{
		game->ray_hits[ind][X] = x;
		game->ray_hits[ind][Y] = y;
		#ifdef DEBUG_CAST_RAY
		dprintf (debug, "%dx : %d\n", ind, game->ray_hits[ind][X]);
		dprintf (debug, "%dy : %d\n", ind, game->ray_hits[ind][Y]);
		#ifdef DEBUG_CAST_RAY_PREV
		dprintf (debug, "%d prev x : %f\n", ind, ((game->ray_hits[ind][X]) - pdx));
		dprintf (debug, "%d prev y : %f\n", ind, ((game->ray_hits[ind][Y]) - pdy));
		#endif
		#endif
		return (1);
	}
	return (0);
}

int cast_ray2(t_game *game, int ind, double dir, int debug)
// int cast_ray2(t_game *game, int ind, double dir)
{
	t_player *player;

	player = game->player;
	double pdx = cos(dir * M_PI / 180.0);
	double pdy = -sin(dir * M_PI / 180.0);
	double x = player->sp_dir[X];
	double y = player->sp_dir[Y];
	int i = 0;
	while (1)
	{
		// if (hit_wall(game, ind, x, y, pdx, pdy, debug))
		// if (hit_wall(game, ind, x, y))
		if (hit_wall(game, ind, x, y, debug))
			return (0);
        mlx_put_pixel(game->img, round(x), round(y), 0x8B4513FF);
		x += pdx;
		y += pdy;
		i++;
	}
	return (1);
}

int prepare_color(char flag, uint32_t *color)
{
	uint32_t	red;
    uint32_t	green;
    uint32_t	black;
	uint32_t	brown;

	red   = 0xFF0000FF;
    green = 0x00FF00FF;
    black = 0x000000FF;
	brown  = 0x8B4513FF;
	if (flag == '1')
		*color = black;
	else if (flag == '0' || is_player(flag))
		*color = green;
	return (0);
}

void draw_2dsquare(t_game *game, t_map *map, int x, int y)
{
	t_player	*player;
    uint32_t	color;
	int j;
	int i;
	int			rulex;
	int			ruley;
	char flag;

	#ifdef DEBUG_DS
	printf ("x : %d\n", x);
	printf ("y : %d\n", y);
	printf ("map flag %c | nb = %d\n", map->map[y][x], map->map[y][x]);
	#endif
	player = game->player;
	rulex = 0;
	ruley = 0;
	#ifdef DEBUG_KTP
	printf (".....\n");
	#endif
	flag = map->map[y][x];
	rulex = get_pixel(x);
	ruley = get_pixel(y);
	prepare_color(flag, &color);
	#ifdef DEBUG_DS
	printf ("rulex : %d\n", rulex);
	printf ("ruley : %d\n", ruley);
	#endif
	i = 0;
	while (i < SQUARE_LEN)
	{
		j = 0;
		while (j < SQUARE_LEN)
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
}

int draw_payer2d(t_game *game)
{
	t_player	*player;
	uint32_t	color;

	color = 0xFF0000FF;
	player = game->player;
	double x = player->sp_dir[X];
	double y = player->sp_dir[Y];
	draw_direction(game, color);
	draw_circle(game->img, (int)x, (int)y, color);
	return (0);
}
int cast_ray(t_game *game)
{
	t_player	*player;
	int			ray;

	player = game->player;
	ray = 0;
	int debug = open ("debug", O_RDWR);
	if (debug == -1)
	{
		printf ("error debug file\n");
		return (1);
	}
	while (ray < IMAC_WIDTH)
	{
	    double ray_angle = player->pa - (FOV / 2) + ((double)ray / IMAC_WIDTH) * FOV;
		#ifdef DEBUG_RAY_ANGLE
		dprintf (debug, "angle : %f\n", ray_angle);
		#endif
		cast_ray2(game, ray, ray_angle, debug);
		// cast_ray2(game, ray, ray_angle);
		ray++;
	}
	return (0);
}

int draw_2dmap (t_game *game)
{
	t_map		*map;

	map = game->map;
	int i = 0;
	int j;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			draw_2dsquare(game, map, j, i);
			j++;
		}
		i++;
	}
	draw_payer2d(game);
	cast_ray(game);
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

int go_forward(t_game *game)
{
	t_player *player;
	t_map *map;
	int tmp1;
	int tmp2;

	player = game->player;
	map = game->map;
	tmp1 = get_sqr(player->sp_dir[Y]);
	tmp2 = get_sqr(player->sp_dir[X] + player->pdx);
	if (map->map[tmp1][tmp2] != '1')
		player->sp_dir[X] += player->pdx;
	tmp1 = get_sqr(player->sp_dir[Y] + player->pdy);
	tmp2 = get_sqr(player->sp_dir[X]);
	if (map->map[tmp1][tmp2] != '1')
		player->sp_dir[Y] += player->pdy;
	map->map[player->player_pos[Y]][player->player_pos[X]] = '0';
	player->player_pos[X] = get_sqr(player->sp_dir[X]);
	player->player_pos[Y] = get_sqr(player->sp_dir[Y]);
	map->map[player->player_pos[Y]][player->player_pos[X]] = 'P';
	#ifdef DEBUG_MOVE
	int i = 0;
	while (map->map[i])
	{
		printf ("map : %s\n", map->map[i]);
		i++;
	}
	printf ("sqx : %d\n", player->player_pos[X]);
	printf ("sqy : %d\n", player->player_pos[Y]);
	printf ("px : %f\n", player->sp_dir[X]);
	printf ("py : %f\n", player->sp_dir[Y]);
	printf ("-------\n");
	#endif
	return (0);
}

int go_back(t_game *game)
{
	t_player *player;
	t_map *map;
	int tmp1;
	int tmp2;

	player = game->player;
	map = game->map;
	tmp1 = get_sqr(player->sp_dir[Y]);
	tmp2 = get_sqr(player->sp_dir[X] - player->pdx);
	if (map->map[tmp1][tmp2] != '1')
		player->sp_dir[X] -= player->pdx;
	tmp1 = get_sqr(player->sp_dir[Y] - player->pdy);
	tmp2 = get_sqr(player->sp_dir[X]);
	if (map->map[tmp1][tmp2] != '1')
		player->sp_dir[Y] -= player->pdy;
	map->map[player->player_pos[Y]][player->player_pos[X]] = '0';
	player->player_pos[X] = get_sqr(player->sp_dir[X]);
	player->player_pos[Y] = get_sqr(player->sp_dir[Y]);
	map->map[player->player_pos[Y]][player->player_pos[X]] = 'P';
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
	map = loadmap(av[1], &game, &player);
	game.mlx = mlx_init(IMAC_WIDTH, IMAC_HEIGHT,"44", true);
	if (!game.mlx)
		ft_error();
	game.img = mlx_new_image(game.mlx, IMAC_WIDTH, IMAC_HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
		ft_error();
	draw_2dmap (&game);
	mlx_loop_hook(game.mlx, handle_input, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
