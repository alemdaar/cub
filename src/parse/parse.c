#include "../main.h"
#include <stdint.h>
#include <stdio.h>

int err_msg(const char *msg)
{
	write (2, msg, ft_strlen(msg));
	return (0);
}

static bool settextures(t_map *map, int f) {

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

static bool setcolors(t_map *map, int f) {
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

static bool setmap(t_map *map, int f) {
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



// int is_symbol(char symbol)
// {
// 	if (symbol == '1' || symbol == '0')
// 		return (1);
// 	if (symbol == 'N' || symbol == 'S')
// 		return (1);
// 	if (symbol == 'E' || symbol == 'W')
// 		return (1);
// 	return (0);
// }

// int locken_line(char *str)
// {
// 	int i = 0;

// 	while (str[i] == ' ')
// 	{
		
// 	}
// 	if (!str[i])
// 		return (1);
// }



// void	flood_fill(t_map *map, int y, int x)
// {
// 	if (map->not_valid == 1)
// 		return ;
// 	if (y < 0 || map->map[y] == 0)
// 	{
// 		map->not_valid = 1;
// 		return ;
// 	}
// 	if (x < 0 || map->map[y][x] == 0)
// 	{
// 		map->not_valid = 1;
// 		return ;
// 	}
// 	if (map->map[y][x] == WALL || map->map[y][x] == 'X')
// 		return ;
// 	if (map->map[y][x] == ' ')
// 	{
// 		map->not_valid = 1;
// 		return ;
// 	}
// 	if (map->map[y][x] == '0')
// 		map->map[y][x] = 'X';
// 	flood_fill(map, y + 1, x);
// 	flood_fill(map, y - 1, x);
// 	flood_fill(map, y, x + 1);
// 	flood_fill(map, y, x - 1);
// 	return ;
// }

int is_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

// int copy_map(t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	while (map->map[i])
// 		i++;
// 	map->tmp_map = malloc(sizeof(char *) * i + 1);
// 	if (!map->tmp_map)
// 		return (err_msg(E_ALLOC), /*free_map(map), */exit(1), 1);
// 	i = 0;
// 	int j;
// 	while (map->map[i])
// 	{
// 		map->tmp_map[i] = malloc (ft_strlen(map->map[i]) + 1);
// 		j = 0;
// 		while (map->map[i][j])
// 		{
// 			map->tmp_map[i][j] = map->map[i][j];
// 			j++;
// 		}
// 		map->tmp_map[i][j] = 0;
// 		i++;
// 	}
// 	return (0);
// }

// int	find_player(t_map *map, t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	// copy_map(map);
// 	map->not_valid = 0;
// 	while (map->map[i])
// 	{
// 		j = 0;
// 		while (map->map[i][j])
// 		{
// 			if (is_player(map->map[i][j]))
// 			{
// 				game->player_pos[X] = j;
// 				game->player_pos[Y] = i;
// 				if (game->player_pos[X])
// 	    			game->sp_dir[X] = ((game->player_pos[X] * SQUARE_LEN) + game->player_pos[X]);
// 				if (game->player_pos[Y])
// 	    			game->sp_dir[Y] = ((game->player_pos[Y] * SQUARE_LEN) + game->player_pos[Y]);
// 				game->sp_dir[X] += CENTER_RULE;
// 				game->sp_dir[Y] += CENTER_RULE;
// 				game->player_pos[X] = j;
// 				game->player_pos[Y] = i;
// 				printf ("sp_dir[X] : %d\n", game->sp_dir[X]);
// 				printf ("sp_dir[Y] : %d\n", game->sp_dir[Y]);
// 				printf ("player_pos[X] : %d\n", game->player_pos[X]);
// 				printf ("player_pos[Y] : %d\n", game->player_pos[Y]);
// 				// while (1);
// 				return (0);
// 			}
// 			j ++;
// 		}
// 		i ++;
// 	}
// 	printf ("there is no player !\n");
// 	exit(1);
// 	// return (1);
// }

// static int	check_map(t_map *map, t_game *game)
// {
// 	int i = 0;
// 	int j = 0;
// 	int store = 0;
// 	int sig = 0;
// 	int len = 0;

// 	i = 0;
// 	copy_map(map);
// 	map->not_valid = 0;
// 	find_player(map, game);
// 	flood_fill(map, game->player_pos[Y], game->player_pos[X]);
// 	i = 0;
// 	while (map->tmp_map[i])
// 		printf ("line : %s\n", map->tmp_map[i++]);
// 	while (1);
// 	// while (map->map[i])
// 	// {
// 	// 	len = ft_strlen(map->map[i]);
// 	// 	if (len == 0)
// 	// 		return (err_msg(E_MAPL0), exit(1), 1);
// 	// 	else if (len < 3)
// 	// 		return (err_msg(E_MAPLS), exit(1), 1);
// 	// 	else if (locken_line(map->map[i]))
// 	// 	{
// 	// 		return (err_msg(E_MAPLS), exit(1), 1);
// 	// 	}
// 	// 	store = ft_strlen(map->map[i]);
// 	// 	if (store != map->width)
// 	// 		return (err_msg(E_MAPLNQ), exit (1), 0);
// 	// 	while (map->map[i][j])
// 	// 	{
// 	// 		if (!is_symbol(map->map[i][j]))
// 	// 		{
// 	// 			printf ("symbol : '%c'\n", map->map[i][j]);
// 	// 			if (map->map[i][j] == ' ')
// 	// 			{
// 	// 				while (map->map[i][j] == ' ' && map->map[i][j])
// 	// 				{
// 	// 					if ()
// 	// 				}
// 	// 				sig = 1;
// 	// 			}
// 	// 			return (err_msg(E_MAPSMB), exit (1), 0);
// 	// 		}
// 	// 		j++;
// 	// 	}
// 	// 	i++;
// 	// }
// 	// map->height = i;
// 	// if (map->height < 3)
// 	// {
// 	// 	printf ("height is small !\n");
// 	// 	return (err_msg(E_MAPLS), exit(1), 1);
// 	// }
// 	return (0);
// }


static int map_data(t_game *game, t_map *map)
{
	game->ep_dir[X] = 90;
	game->ep_dir[Y] = 0;
	game->map = map;
	return (0);
}

// TODO need way more verificatiosn and cehcks for the format
// or maybe split into one for parse and one for checks
t_map *loadmap(char *filename, t_game *game)
{
	t_map *map = malloc(sizeof(t_map));
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
	// if (!check_map(map, game))
	// 	return map;
	if (!map_data(game, map))
		return map;
	map->success = true;
	return map;
}
