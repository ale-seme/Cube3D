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
	bool			utility_bool;

	
} t_game;


/*parsing map management*/
void	convert_spaces_and_copy_map(t_game *game, t_lst *temp);

/*identifiers management*/
int		check_convert_and_store_rbgs(char *line, int n_id, t_game *game);
int		check_and_store_texture(char *line, int n_id, t_game *game);

/*parsing funcitons*/
char	*get_next_line(int fd);
int		check_and_atoi(char *str);

#endif
