#pragma once
#include "../lib/gnl/get_next_line.h"
#include "../lib/libft/libft.h"
#include "parse/parse.h"
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "../lib/mlx42/include/MLX42/MLX42.h"

#define	SUCCESSFUL 0
#define	FAILED 1
#define	E_ALLOC "Memory alocation failed !\n"
#define	E_MAPLS "Map len is too small !\n"
#define E_MAPLNQ "Map lens are not equal !\n"
#define E_MAPL0 "Map len is 0 !\n"
#define E_MAPSMB "Symbol is not correct !\n"

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
	char **map;
	unsigned int fcolor;
	unsigned int ccolor;
	int width;
	int height;
} t_map;

typedef struct s_game {
	mlx_t			*mlx;
	mlx_image_t*	img;
} t_game;
