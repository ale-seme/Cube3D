#ifndef CUBE3D_H
# define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "stdbool.h"
#include  "fcntl.h"
#include "../MLX42/include/MLX42/MLX42.h"

#define CARDINALS "NSWE"
#define ELEMENTS "01 "

/*error messages*/
# define ERR_NODE      "Error\nFailed malloc in new node\n"
# define ERR_STRDUP    "Error\nStrdup failed during initial parsing\n"
# define ERR_NO_ARG    "Error\nNo argv provided\n"
# define ERR_NO_CUB    "Error\nargv is not a .cub file\n" 
# define ERR_ARG_DIR   "Error\nThe arg provided is a directory\n"
# define ERR_ARG_OPEN  "Error\nFailed to open the argument provided\n"
# define ERR_EMPTY_F   "Error\nGiven file is empty\n"
# define ERR_BAD_IDS   "Error\nBad or incomplete identifiers given\n"
# define ERR_NO_INFO   "Error\nReached end of map with not enough info\n"
# define ERR_FAKE_ID   "Error\nFake identifier detected\n"
# define ERR_TX_DIR    "Error\nAn identifier has a directory as path\n"
# define ERR_TX_OPEN   "Error\nFailed to open an id texture\n"
# define ERR_USLESS_C  "Error\nPesence of a usless char before the map\n"
# define ERR_NO_RBGS   "Error\nFloor/Cealing has empty rbg values\n"
# define ERR_NO_RBG    "Error\nOne of the rbgs is empty/contains only spaces\n"
# define ERR_BAD_RBG   "Error\nOnly digit after spaces as RBG codes\n"
# define ERR_OVFL_RBG  "Error\nNumber given as RBG parameter should be max 255\n"
# define ERR_ARRAY     "Error\nFailed to malloc the int array for RBGs\n"
# define ERR_SPL_RBG   "Error\nFailed to split the rgb values for an id"
# define ERR_NUM_RGBS  "Error\nThe program accepts 3 and only 3 ids' RBGs"
# define ERR_EMPTY_LN  "Error\nEmpty lines in the map are no allowed\n"
# define ERR_NO_CARDI  "Error\nOne cardinal is needed for player starting pos\n"
# define ERR_BAD_WALLS "Error\nThe map is NOT sourrounded by walls!\n"
# define ERR_CAM_MEM   "Error\nFailed malloc for camera info\n"
# define ERR_2D_ARRAY  "Error\nFailed malloc for 2d array\n"
# define ERR_2D_LINE   "Error\nFailed malloc for a single line in 2D array\n"
# define ERR_NO_ALLOW  "Error\nMap contains a forbidded element or an element not allowed more than once\n"
//#define

typedef struct s_multi
{
	mlx_image_t *image;
	int			x;
	int			y;
}t_multi;

typedef struct s_images
{
	t_multi *player;
	t_multi *idk;
	mlx_image_t *something;
	mlx_image_t *something_2;
}t_images;

typedef struct s_ray
{
	double	ray_angle;
	double	wall_dst;
	bool	is_met;
} t_ray;


typedef struct s_lst
{
	char			*map_line;
	struct s_lst 	*next;
} t_lst;

typedef struct s_camera
{
	int		x;
	int		y;
	double	angle;
	float	fov_radi;
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

typedef struct s_mlx_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t *image_2;
	t_game		*game;
	t_camera	*camera;
	t_ray		*ray;		
	
} t_mlx_data;

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
void	free_game(t_game *game);

#endif
