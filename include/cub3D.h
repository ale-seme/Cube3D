#ifndef CUBE3D_H
# define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include <stdbool.h>
#include "fcntl.h"
#include <math.h>
#include <stdbool.h>
#include "../MLX42/include/MLX42/MLX42.h" //you have to do make download mlx_42 and will work

# define CARDINALS "NSWE" //string containing the cardinals that are allowed
# define ELEMENTS "01 " //the only allowed elemebts besides cardinals are 0s 1s and normal space (not tabs)
# define SCREEN_WIDTH 1920 //this is the resoluton of my personal laptop, we can change it to codam's 
# define SCREEN_HEIGHT 1000 //same 
# define CELL_SIZE 32 //each cell is 32, could be 64 but it's nice to start with power of 2s
# define FOW 60 //field of view, which is the angle
# define CAM_SPEED 3 //this is gonna be the speed at which the player will move in the 4 directions
# define CAM_ROT 0.050 //for each frame of pressing the rot keys it will add or subtract this from the camera angle
# define PI  3.1415926535 //the value of PI greco

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

// typedef struct s_multi
// {
// 	mlx_image_t *image;
// 	int			x;
// 	int			y;
// }t_multi;

// typedef struct s_images
// {
// 	t_multi *player;
// 	t_multi *idk;
// 	mlx_image_t *something;
// 	mlx_image_t *something_2;
// }t_images;

/**
 * Struct to hold information about rays in the raycasting phase
 * This is a work in pogress
 */

typedef struct s_ray
{
	int		ray_n;
	float	unit_angle;
	float	current_angle;
	float	v_hit_x;//need to check if inter
	float	v_hit_y;
	float	h_hit_x;
	float	h_hit_y;
	float	wall_dst;
	bool	wall_met;
} t_ray;


/**
 * Struct for a linked list used to parse each line returned 
 * by get_next_line
 * @param map_line	Ptr to a string of the current node
 * @param next		Ptr to the next node of the linked list
 */
typedef struct s_lst
{
	char			*map_line;
	struct s_lst 	*next;
} t_lst;


/**
 * Struct holding information about the camera (player)
 * Currently a work in progress
 * @param x Current x cell of the player in map coordinates
 * @param y Current y cell of the player in map coordinates
 * @param angle Current angle of the player 
 * @param fov_radi Field of view (FOW) expressed in radiants
 * @param cardinal_point Character containing the starting cardinal(NSOW)
 */
typedef struct s_camera
{
	int 		x;
	float		pixel_x;
	float		pdx;
	int			y;
	float		pixel_y;
	float		pdy;		
	float		angle;
	float		fov_radi;
	char		cardinal_point;
	int			test;
} t_camera;

/**
 * Struct used to keep track of the number of identifiers
 * that have been met during the parsing phase
 */
typedef struct s_count
{
	int		count_nord;
	int		count_south;
	int		count_west;
	int		count_east;
	int		count_floor;
	int		count_ceiling;
}	t_count;

/** 
 * Main struct of the game, it contains several informations
 * that were gathered during the parsing phase
 * @param start_list_pointer Ptr to linked list used to parse/store all the lines
 * @param start_map_pointer Ptr to ode of the list where the map finally starts
 * @param n_ids Ptr to struct containing flags for the identifiers parsing
 * @param nord Ptr to path of the nord texture after parsing
 * @param south Ptr to path of the nord texture after parsing
 * @param west Ptr to path of the nord texture after parsing
 * @param east Ptr to path of the nord texture after parsing
 * @param floor_rgb_array Pointer to the string
 * @param cealing_rgb_array
 * @param n_rows Number of rows (x) of the 2d map
 * @param n_columns Number of columns (y) of the 2d map
 * */
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
	int				*floor_rbg_array;
	int				*cealing_rbg_array;
	int				n_rows;
	int				n_columns;
	char**			working_map;
} t_game;


/**
 * Main struct of the graphical part of the game
 * Containing several mlx and raycasting elements
 * For now a work in progress since the focus is on the minimap
 * 
 * @param mlx Ptr to main mlx handler struct
 * @param image_walls Ptr to the image struct for the walls (at the moment will be filled only with same pixels color instead of a texture)
 * @param image_floor Ptr to the image struct for the floor
 * @param image_cealing Ptr to the image struct for the cealing
 * @param main_image	Ptr to the main image buffer where to draw stuff
 * @param game Ptr to the game main struct 
 * @param camera Ptr to the camera(player) struct
 * @param ray Ptr to the ray structure
 */
typedef struct s_mlx_data
{
	mlx_t		*mlx;
	mlx_image_t	*image_walls; //for now instead of the textures we get form the parsing just images who's pixels we color
	mlx_image_t *image_player; // same for the player, for the 2d map we need for ex a 5x5 image that whose pixels we color
	mlx_image_t *image_floor; //this will be black for the 2d test minimap 
	mlx_image_t	*main_image; //this is the main image where the game will be drawn
	mlx_image_t *image_cealing; //this for now doesn't exists for the 2D minimap
	t_game		*game; //simply a pointer to the game struct
	t_camera	*camera; // a pointer to the camera information gethered during the parsing(is the player)
	t_ray		*ray; //pointer to a struct containing information for the raycasting	
	
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
void	free_everything(t_game *game);

/*raycasting*/
void	ray_casting(t_mlx_data *mlx_data);

/*init trig tables*/
void init_trig_tables(void);
float lookup_sin(float angle);
float lookup_cos(float angle);
#endif
