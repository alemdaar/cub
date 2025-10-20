#pragma once
#include "../lib/gnl/get_next_line.h"
#include "../lib/libft/libft.h"
#include "parse/parse.h"
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "../lib/mlx42/include/MLX42/MLX42.h"

#define	E_ALLOC				"Memory alocation failed !\n"
#define	E_MAPLS				"Map len is too small !\n"
#define E_MAPLNQ			"Map lens are not equal !\n"
#define E_MAPL0				"Map len is 0 !\n"
#define E_MAPSMB			"Symbol is not correct !\n"
#define	SUCCESSFUL			0
#define	FAILED				1
#define	X					0
#define	Y					1
#define IMAC_WIDTH			5120
#define IMAC_WIDTH_DEBUG	1500
#define IMAC_HEIGHT			2880
#define RED					0xFF0000FF
#define GREEN				0x00FF00FF
#define BLACK				0x000000FF
#define SQUARE_LEN			35
#define PLAYER_LEN			15
#define CENTER_RULE			17
#define MAP2D_LEN			5
// center of the player is [89 , 53]
// the highest pixel of the player is [89 , 46]
// the lowest pixel of the player is [89 , 40]
// the top right pixel of the player is [96 , 53]
// the top left pixel of the player is [82 , 53]
#define CIRCLE_RADIUS	7
#define MAX_SQUARES_2D	7
// 
# define WALL 49
# define EMPTY 48

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
	char **tmp_map;
	unsigned int fcolor;
	unsigned int ccolor;
	int width;
	int height;
	int not_valid;
	
} t_map;

typedef struct s_game {
	mlx_t			*mlx;
	mlx_image_t*	img;
	int				ep_dir[2];
	int				sp_dir[2];
	int				player_pos[2];
	t_map			*map;
} t_game;


t_map *loadmap(char *filename, t_game *game);
