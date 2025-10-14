#pragma once
#include "../lib/gnl/get_next_line.h"
#include "../lib/libft/libft.h"
#include "parse/parse.h"
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "../lib/mlx42/include/MLX42/MLX42.h"

typedef struct s_player {
	double x, y;
	double angle;
} t_Payer;

typedef struct s_map {
	bool success;
	char *npath;
	char *spath;
	char *wpath;
	char *epath;

	unsigned int fcolor;
	unsigned int ccolor;

	char **map;
} t_map;

typedef struct s_game {
	mlx_t			*mlx;
	mlx_image_t*	img;
} t_game;
