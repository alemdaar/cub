#pragma once
#include "../lib/gnl/get_next_line.h"
#include "../lib/libft/libft.h"
#include "parse/parse.h"
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct s_player {
	double x, y;
	double angle;
} Player;

typedef struct s_map {
	bool success;
	char *npath;
	char *spath;
	char *wpath;
	char *epath;

	unsigned int fcolor;
	unsigned int ccolor;

	char **map;
} Map;
