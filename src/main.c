#include "main.h"
#include "parse/parse.h"
#include <stdio.h>

int main(int ac, char **av) {
	if (ac != 2) {
		puts("Usage: ./cub3d <path/to/map.cub>");
		return 1;
	}
	Map *map = loadmap(av[1]);
	#ifdef DEBUG
	printf("NO %s", map->npath);
	printf("SO %s", map->spath);
	printf("WE %s", map->wpath);
	printf("EA %s", map->epath);
	printf("F: %d %d %d\n", map->fcolor >> 16 & 0xff, map->fcolor >> 8 & 0xff,
		   map->fcolor & 0xff);
	printf("C: %d %d %d", map->ccolor >> 16 & 0xff, map->ccolor >> 8 & 0xff,
		   map->ccolor & 0xff);
	for (int i = 0; map->map[i]; i++)
		printf("%s", map->map[i]);
	#endif
}
