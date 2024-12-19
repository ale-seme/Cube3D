

#include "cub3D.h"

static int	check_ids_amount(t_count *n_ids)
{
	if (n_ids->count_ceiling != 1
		|| n_ids->count_east != 1
		|| n_ids->count_floor != 1
		|| n_ids->count_nord != 1
		|| n_ids->count_south != 1
		|| n_ids->count_west != 1)
		return (0);
	return (1);
}

static void	initialize_count(t_count *n_ids)
{
	n_ids->count_nord = 0;
	n_ids->count_south = 0;
	n_ids->count_west = 0;
	n_ids->count_east = 0;
	n_ids->count_floor = 0;
	n_ids->count_ceiling = 0;
}

//TODO: another way to check that gnl returned null immediately line 45 return
//TODO: could also check if (!list) line 60 return
int	check_ids_and_get_map_start(t_lst *list, t_game *game)
{
	t_count	n_ids;

	initialize_count(&n_ids);
	game->n_ids = &n_ids;
	if (!list)
		return (printf(ERR_EMPTY_F), 0);
	while (list)
	{
		while (list && (list->map_line[0] == '\n' || list->map_line[0] == '\0'))
			list = list->next;
		if (!list)
			break ;
		if (!check_ids_and_info(list->map_line, game))
			return (0);
		list = list->next;
		if (check_ids_amount(&n_ids))
			break ;
	}
	if (!check_ids_amount(&n_ids))
		return (printf(ERR_BAD_IDS), 0);
	while (list && (list->map_line[0] == '\n' || list->map_line[0] == '\0'))
		list = list->next;
	if (!list)
		return (printf(ERR_NO_INFO), 0);
	return (game->start_map_pointer = list, 1);
}
