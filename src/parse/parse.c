#include "../main.h"
#include <stdint.h>

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
	char **m = map->map;
	int i = 0;
	char *line = get_next_line(f);
	while (line) {
		m[i] = line;
		i++;
		line = get_next_line(f);
	}
	m[i] = NULL;
	return true;
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

	map->success = true;
	return map;
}
