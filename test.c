#include "./lib/mlx42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_player {
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_data {
    mlx_t       *mlx;
    t_player    player;
    int         key_w;
    int         key_s;
    int         key_a;
    int         key_d;
    int         key_left;
    int         key_right;
    char        **map;
} t_data;

/* --- ROTATE PLAYER --- */
void rotate_player(t_player *p, double rot)
{
    double old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
    p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);

    double old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
    p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

/* --- MOVEMENT --- */
void move_player(t_data *data)
{
    double move_speed = 0.05;
    double rot_speed = 0.05;

    if (data->key_w)
    {
        if (data->map[(int)(data->player.pos_y)]
                     [(int)(data->player.pos_x + data->player.dir_x * move_speed)] == '0')
            data->player.pos_x += data->player.dir_x * move_speed;
        if (data->map[(int)(data->player.pos_y + data->player.dir_y * move_speed)]
                     [(int)(data->player.pos_x)] == '0')
            data->player.pos_y += data->player.dir_y * move_speed;
    }
    if (data->key_s)
    {
        if (data->map[(int)(data->player.pos_y)]
                     [(int)(data->player.pos_x - data->player.dir_x * move_speed)] == '0')
            data->player.pos_x -= data->player.dir_x * move_speed;
        if (data->map[(int)(data->player.pos_y - data->player.dir_y * move_speed)]
                     [(int)(data->player.pos_x)] == '0')
            data->player.pos_y -= data->player.dir_y * move_speed;
    }
    if (data->key_a)
    {
        if (data->map[(int)(data->player.pos_y)]
                     [(int)(data->player.pos_x - data->player.plane_x * move_speed)] == '0')
            data->player.pos_x -= data->player.plane_x * move_speed;
        if (data->map[(int)(data->player.pos_y - data->player.plane_y * move_speed)]
                     [(int)(data->player.pos_x)] == '0')
            data->player.pos_y -= data->player.plane_y * move_speed;
    }
    if (data->key_d)
    {
        if (data->map[(int)(data->player.pos_y)]
                     [(int)(data->player.pos_x + data->player.plane_x * move_speed)] == '0')
            data->player.pos_x += data->player.plane_x * move_speed;
        if (data->map[(int)(data->player.pos_y + data->player.plane_y * move_speed)]
                     [(int)(data->player.pos_x)] == '0')
            data->player.pos_y += data->player.plane_y * move_speed;
    }
    if (data->key_left)
        rotate_player(&data->player, -rot_speed);
    if (data->key_right)
        rotate_player(&data->player, rot_speed);
}

/* --- INPUT CALLBACKS --- */
void key_press(mlx_key_data_t keydata, void *param)
{
    t_data *data = param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(data->mlx);
    if (keydata.key == MLX_KEY_W)
        data->key_w = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_S)
        data->key_s = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_A)
        data->key_a = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_D)
        data->key_d = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_LEFT)
        data->key_left = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_RIGHT)
        data->key_right = (keydata.action != MLX_RELEASE);
}

/* --- LOOP HOOK --- */
void update(void *param)
{
    t_data *data = param;

    move_player(data);
    printf("Player pos: (%.2f, %.2f)\r", data->player.pos_x, data->player.pos_y);
    fflush(stdout);
}

/* --- MAIN --- */
int main(void)
{
    t_data data;

    static char *map[] = {
        "1111111",
        "1000001",
        "1000001",
        "1000001",
        "1111111",
        NULL
    };
    data.map = map;

    data.mlx = mlx_init(800, 600, "Cub3D Movement (Codam MLX)", true);
    if (!data.mlx)
        return (1);

    data.player.pos_x = 3.5;
    data.player.pos_y = 3.5;
    data.player.dir_x = -1.0;
    data.player.dir_y = 0.0;
    data.player.plane_x = 0.0;
    data.player.plane_y = 0.66;

    data.key_w = data.key_s = data.key_a = data.key_d = 0;
    data.key_left = data.key_right = 0;

    mlx_key_hook(data.mlx, key_press, &data);
    mlx_loop_hook(data.mlx, update, &data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
    return (0);
}
