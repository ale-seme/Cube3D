/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 17:43:06 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/10/30 12:53:17 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	initialize_game(t_game *game)
{
	game->camera_start_info = NULL;
	game->cealing_rbg_array = NULL;
	game->floor_rbg_array = NULL;
	game->n_ids = NULL;
	game->start_list_pointer = NULL;
	game->start_map_pointer = NULL;
	game->texture_east = NULL;
	game->texture_nord = NULL;
	game->texture_south = NULL;
	game->texture_west = NULL;
	game->working_map = NULL;
	game->yes_minimap = 0;
}

static void	prepare_images_buffers(t_mlx_data *mlx_data)
{
	mlx_data->main_image = mlx_new_image(mlx_data->mlx, \
								SCREEN_WIDTH, SCREEN_HEIGHT);
	if (mlx_data->main_image == NULL)
	{
		free_game_parsing(mlx_data->game);
		free_mlx_resources(mlx_data);
		printf(ERR_MLX_IMAGE);
		exit(EXIT_FAILURE);
	}
}

static int	calc_cell_size(int n_rows, int n_columns, t_mlx_data *mlx_data)
{
	int	cell_size;

	cell_size = 16;
	mlx_data->game->minimap_shifts = 0;
	while (cell_size * n_rows > 240 || cell_size * n_columns > 960)
	{
		cell_size = cell_size >> 1;
		if (cell_size < 4)
		{
			cell_size = 4;
			break ;
		}
		mlx_data->game->minimap_shifts++;
	}
	return (cell_size);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_mlx_data	mlx_data;

	game.start_list_pointer = NULL;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	initialize_game(&game);
	if (!successfull_parsing(argc, argv, &game))
		return (free_game_parsing(&game), 1);
	if (!initialize_data_for_mlx(&game, &mlx_data))
		return (free_game_parsing(&game), free_mlx_resources(&mlx_data), 1);
	mlx_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!mlx_data.mlx)
		return (printf(ERR_MLX_INIT), free_game_parsing(&game), 1);
	prepare_images_buffers(&mlx_data);
	if (game.yes_minimap)
		mlx_data.game->mini_cell = \
			calc_cell_size(game.n_rows, game.n_columns, &mlx_data);
	mlx_loop_hook(mlx_data.mlx, draw_everything, &mlx_data);
	mlx_loop_hook(mlx_data.mlx, ft_custom_key, &mlx_data);
	mlx_loop(mlx_data.mlx);
	free_game_parsing(&game);
	free_mlx_resources(&mlx_data);
	return (0);
}
