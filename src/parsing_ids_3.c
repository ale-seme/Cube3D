/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_ids_3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 17:51:59 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/10/22 18:53:52 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	increment_id_count(t_game *game, int n_id)
{
	if (n_id == 0)
		game->n_ids->count_nord++;
	else if (n_id == 1)
		game->n_ids->count_south++;
	else if (n_id == 2)
		game->n_ids->count_west++;
	else if (n_id == 3)
		game->n_ids->count_east++;
	else if (n_id == 4)
		game->n_ids->count_floor++;
	else if (n_id == 5)
		game->n_ids->count_ceiling++;
}

static int	check_convert_and_store_rbgs(char *line, int n_id, t_game *game)
{
	char	*temp;

	temp = line + 1;
	if (!temp || !temp[0] || !ft_isspace(temp[0]))
		return (printf(ERR_FAKE_ID), 0);
	increment_id_count(game, n_id);
	while ((*temp >= 9 && *temp <= 13) || *temp == ' ')
		temp++;
	if (!(*temp))
		return (printf(ERR_NO_RBGS), 0);
	if (!split_store_and_check_rbg_amount(temp, n_id, game))
		return (0);
	return (1);
}

int	manage_floor_cealing_ids_and_usless_char(char *line, t_game *game)
{
	if (line[0] == 'F')
	{
		if (!check_convert_and_store_rbgs(line, 4, game))
			return (0);
	}
	else if (line[0] == 'C')
	{
		if (!check_convert_and_store_rbgs(line, 5, game))
			return (0);
	}
	else if (!line || (line[0] && line[0] != '\n'))
	{
		return (printf(ERR_USLESS_C), 0);
	}
	return (1);
}
