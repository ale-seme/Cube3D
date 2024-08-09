#include <cub3D.h>

void    convert_spaces_and_copy_map(t_game *game, t_lst *temp)
{
	int i;
	int r;

	i = 0;
	while(game->working_map[i])
	{
		r = 0;
		ft_memset(game->working_map[i], '2', game->n_columns);
		while(temp->map_line[r])
		{
			game->working_map[i][r] = temp->map_line[r];
			r++;
		}
		temp = temp->next;
		i++;
	}
}