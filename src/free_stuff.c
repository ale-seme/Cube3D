

#include "cub3D.h"

void	free_split(char **ss)
{
	char	**original_ss;

	original_ss = ss;
	while (ss && *ss)
	{
		free(*ss);
		ss++;
	}
	free(original_ss);
}

void	free_list(t_lst *lst)
{
	t_lst	*temp;

	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		free(temp->map_line);
		free(temp);
	}
}

void	free_game(t_game *game)
{
	if (game->camera_start_info)
		free(game->camera_start_info);
	if (game->working_map)
	{
		free_split(game->working_map);
	}
	if (game->cealing_rbg_array)
	{
		free(game->cealing_rbg_array);
	}
	if (game->floor_rbg_array)
	{
		free(game->floor_rbg_array);
	}
}

void	free_game_parsing(t_game *game)
{
	free_list(game->start_list_pointer);
	free_game(game);
}

void	free_mlx_resources(t_mlx_data *mlx_data)
{
	if (mlx_data->ray && mlx_data->ray->bresenham)
		free(mlx_data->ray->bresenham);
	if (mlx_data->ray)
		free(mlx_data->ray);
	if (mlx_data->north)
		mlx_delete_texture(mlx_data->north);
	if (mlx_data->south)
		mlx_delete_texture(mlx_data->south);
	if (mlx_data->east)
		mlx_delete_texture(mlx_data->east);
	if (mlx_data->west)
		mlx_delete_texture(mlx_data->west);
	if (mlx_data->mlx)
		mlx_close_window(mlx_data->mlx);
	if (mlx_data->mlx)
		mlx_terminate(mlx_data->mlx);
}
