#include "../main.h"
#include <stdint.h>
#include <stdio.h>

int err_msg(const char *msg)
{
	write (2, msg, ft_strlen(msg));
	return (0);
}

static bool settextures(Map *map, int f) {

	for (int i = 0; i < 4; i++) {
		char *line = get_next_line(f);
		if (!line) {
			return false;
		}
		char **split = ft_split(line, ' ');
		// if (!split || !split[0]) {
		// 	close(f);
		// 	free(line);
		// 	free(split);
		// 	return map;
		// } else if (!split[1]) {
		// 	close(f);
		// 	free(line);
		// 	free(split[0]);
		// 	free(split);
		// 	return map;
		// }

		switch (split[0][0]) {
		case 'N':
			map->npath = split[1];
			break;
		case 'S':
			map->spath = split[1];
			break;
		case 'W':
			map->wpath = split[1];
			break;
		case 'E':
			map->epath = split[1];
			break;
		}
		free(split[0]);
		free(split);
	}

	return true;
}

static void freesplit(char **split) {
	for (int i = 0; split[i]; i++)
		free(split[i]);
	free(split);
}

static bool setcolors(Map *map, int f) {
	for (int i = 0; i < 2; i++) {
		char *line = get_next_line(f);
		if (!line)
			return false;
		char **split = ft_split(line, ' ');
		free(line);
		char **clrs = ft_split(split[1], ',');
		unsigned int c = (ft_atoi(clrs[0]) << 16) | (ft_atoi(clrs[1]) << 8) |
						 (ft_atoi(clrs[2]));
		switch (split[0][0]) {
		case 'F':
			map->fcolor = c;
			break;
		case 'C':
			map->ccolor = c;
			break;
		}
		freesplit(split);
		freesplit(clrs);
	}
	return true;
}

static bool setmap(Map *map, int f) {
	map->map = malloc(sizeof(char *) * 1024);
	if (!map->map)
		return (err_msg(E_ALLOC), exit(1), 1);
	char **m = map->map;
	int i = 0;
	int j;
	char *line = get_next_line(f);
	while (line)
	{
		m[i] = line;
		j = 0;
		while (m[i][j])
		{
			if (m[i][j] == '\n')
				m[i][j] = 0;
			j++;
		}
		i++;
		line = get_next_line(f);
	}
	m[i] = NULL;
	return true;
}



int is_symbol(char symbol)
{
	if (symbol == '1' || symbol == '0')
		return (1);
	if (symbol == 'N' || symbol == 'S')
		return (1);
	if (symbol == 'E' || symbol == 'W')
		return (1);
	return (0);
}

int	check_map(t_map *map)
{
	int i = 0;
	int j = 0;
	int store = 0;
	// int sig = 0;

	map->width = ft_strlen(map->map[i]);
	if (map->width == 0)
		return (err_msg(E_MAPL0), exit(1), 1);
	else if (map->width < 3)
	{
		return (err_msg(E_MAPLS), exit(1), 1);
	}
	while (map->map[i])
	{
		store = ft_strlen(map->map[i]);
		if (store != map->width)
			return (err_msg(E_MAPLNQ), exit (1), 0);
		while (map->map[i][j])
		{
			if (!is_symbol(map->map[i][j]))
			{
				printf ("symbol : '%c'\n", map->map[i][j]);
				// if (map->map[i][j] == ' ')
				// {
				// 	while (map->map[i][j] == ' ' && map->map[i][j])
				// 	{
				// 		if ()
				// 	}
				// 	sig = 1;
				// }
				return (err_msg(E_MAPSMB), exit (1), 0);
			}
			j++;
		}
		i++;
	}
	map->height = i;
	if (map->height < 3)
	{
		printf ("height is small !\n");
		return (err_msg(E_MAPLS), exit(1), 1);
	}
	return (0);
}

// TODO need way more verificatiosn and cehcks for the format
// or maybe split into one for parse and one for checks
Map *loadmap(char *filename) {
	Map *map = malloc(sizeof(Map));
	map->success = false;

	int f = open(filename, O_RDONLY);
	if (f < 0)
		return map;

	if (!settextures(map, f))
		return map;
	if (!setcolors(map, f))
		return map;
	if (!setmap(map, f))
		return map;
	if (!check_map(map))
		return map;
	// if (!map_data(map))
	// 	return 1;

	map->success = true;
	return map;
}
