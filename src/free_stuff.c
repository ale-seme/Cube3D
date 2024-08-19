# include "cub3D.h"

void	free_split(char **ss)
{
	char **original_ss;
	
	original_ss = ss;
	while(ss && *ss)
	{
		free(*ss);
		ss++;
	}
	free(original_ss);
}

void	free_list(t_lst *lst)
{
	t_lst *temp;

	while(lst)
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

// int main(void)
// {
//     char *hello = "hello,this,is,me";
//     char **ss = ft_split(hello, ',');
//     char **temp = ss;
//     while(*temp)
//     {
//         printf("%s\n", *temp);
//         (temp)++;
//     }
//     free_split(ss);
// }
