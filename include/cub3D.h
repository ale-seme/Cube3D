#ifndef CUBE3D_H
# define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "stdbool.h"
#include  "fcntl.h"

#define CARDINALS "NSWE"
#define ELEMENTS "01 "
// typedef struct game_info
// {
// 	int rbgs[2][3];

// 	char **floor_rbg;
// 	char **ceiling_rbg;

	
// }

typedef struct s_lst
{
	char			*map_line;
	struct s_lst 	*next;
} t_lst;

typedef struct s_camera
{
	int		x;
	int		y;
	char	cardinal_point;
} t_camera;

typedef struct s_count
{
	int		count_nord;
	int		count_south;
	int		count_west;
	int		count_east;
	int		count_floor;
	int		count_ceiling;
}	t_count;

typedef struct s_game
{
	t_lst			*start_list_pointer;
	t_lst			*start_map_pointer;
	t_count			*n_ids;
	t_camera		*camera_start_info;
	char			*texture_nord;
	char			*texture_south;
	char			*texture_west;
	char			*texture_east;
	int				*floor_rbg_array; //if i use atoi already I will do a int pointer
	int				*cealing_rbg_array; //same here array of integers maybe instead of char **
	int				n_rows;
	int				n_columns;
	char**			working_map;

	
} t_game;


/*parsing map management*/
int		check_adapt_and_copy_map(t_game *game);
int		map_enclosed_by_walls(t_game *game);

/*parsing_identifiers_functions*/


int	check_ids_and_get_map_start(t_lst *list, t_game *game);
int	check_ids_and_info(char *line, t_game *game);
int	manage_floor_cealing_ids_and_usless_char(char *line, t_game *game);
int	split_store_and_check_rbg_amount(char *temp, int n_id, t_game *game);
void	increment_id_count(t_game *game, int n_id);

/*general_parsing_funcitons*/
char	*get_next_line(int fd);
int		successfull_parsing(int argc, char **argv, t_game *game);

/*free memory functions*/
void	free_list(t_lst *lst);
void	free_split(char **ss);
void	free_rbg_arrays(int *floor, int *cealing);


#endif
