

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include <stdbool.h>
# include "fcntl.h"
# include <math.h>
# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define MOVE_FORWARD  0b0001  // W key
# define MOVE_LEFT     0b0010  // A key
# define MOVE_BACKWARD 0b0100  // S key
# define MOVE_RIGHT    0b1000  // D key

# define CARDINALS "NSWE"
# define ELEMENTS "01 "
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1000
# define CELL_SIZE 32
# define CELL_MINI 16
# define FOV 60
# define CAM_SPEED 3
# define CAM_ROT 0.1
# define PI  3.1415926535

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
# define ERR_OVFL_RBG  "Error\nNumber given as RBG parameter \
should be max 255\n"
# define ERR_ARRAY     "Error\nFailed to malloc the int array for RBGs\n"
# define ERR_SPL_RBG   "Error\nFailed to split the rgb values for an id"
# define ERR_NUM_RGBS  "Error\nThe program accepts 3 and only 3 ids' RBGs"
# define ERR_EMPTY_LN  "Error\nEmpty lines in the map are no allowed\n"
# define ERR_NO_CARDI  "Error\nOne cardinal is needed for player starting pos\n"
# define ERR_BAD_WALLS "Error\nThe map is NOT sourrounded by walls!\n"
# define ERR_CAM_MEM   "Error\nFailed malloc for camera info\n"
# define ERR_2D_ARRAY  "Error\nFailed malloc for 2d array\n"
# define ERR_2D_LINE   "Error\nFailed malloc for a single line in 2D array\n"
# define ERR_NO_ALLOW  "Error\nMap contains a forbidded element or an \
element not allowed more than once\n"
# define ERR_BRE_CALLO "Error\nft_calloc failed\n"
# define ERR_SPL_COUNT "Error\nWrong number of separator in RBG arg\n"
# define ERR_MLX_INIT  "Errpr\nmlx_init failed\n"
# define ERR_MLX_IMAGE "Error\nmlx_image failed\n"
# define ERR_RAY_CALLO "Error\nFailed calloc for rays struct\n"

/**
 * @brief Data structure to store the variables used by the bresenham algo to
 * draw a straight line between 2 dots in a plane
 * @param dx Absolute differenct in the x-coordinates of the start and end
 * @param dy Absolute difference in the y_coordinates of the start and end
 * @param sx Step direction in the x-axis. Either 1 or -1
 * @param sy Steo direction in the y-axis. Either 1 or -1
 * @param e2 Temp variable used to double the error to determine direction
 */
typedef struct s_bre
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_bre;
/**
 * @brief Data structure to sore the coordinates of a point in a plane
 * @param x The x coordinate
 * @param y The y coordinate
 */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/**
 * @brief	data structure for rendering the ray casting on the minimap.
 * @param x_1 data point x coordinate for the start point of the ray.
 * @param y_1 data point y coordinate for the start point of the ray.
 * @param x_2 data point x coordinate for the end point of the ray.
 * @param y_2 data point y coordinate for the end point of the ray.
 */
typedef struct s_bersenham
{
	float		x_1[SCREEN_WIDTH];
	float		y_1[SCREEN_WIDTH];
	float		x_2[SCREEN_WIDTH];
	float		y_2[SCREEN_WIDTH];
}	t_bresenham;

/**
 * @brief this struct holds the information about rays in the raycasting phase
 * This is a work in pogress
 * @param bresenham this is a buffer for the information of the raycaster 
 * that is then used to draw the rays on the minimap
 * @param ray_n	number of rays.
 * @param horiz_met_first If the hoiz grid was met first
 * @param current_angle Current angle of the ray
 * @param v_hit_x x coordinate of the intersection with vertical grid
 * @param v_hit_y y coordinate of the intersection with vertical grid
 * @param h_hit_x x coordinate of the intersection with the horizontal grid
 * @param h_hit_y y coordinate of the intersection with the horizontal grid 
 * @param wall_dst current ray lenght from the player to the wall
 * @param wall_met flag to know if a wall was met
 * @param x_final_hit x coordinate of the final wall hit
 * @param y_final_hit y coordinate of the final wall hit
 */
typedef struct s_ray
{
	t_bresenham	*bresenham;
	int			ray_n;
	int			horiz_met_first;
	float		unit_angle;
	float		current_angle;
	float		v_hit_x;
	float		v_hit_y;
	float		h_hit_x;
	float		h_hit_y;
	float		wall_dst;
	bool		wall_met;
	float		x_final_hit;
	float		y_final_hit;
}	t_ray;

/**
 * @brief struct for a linked list used to parse each line returned 
 * by get_next_line
 * @param map_line	Ptr to a string of the current node
 * @param next		Ptr to the next node of the linked list
 */
typedef struct s_lst
{
	char			*map_line;
	struct s_lst	*next;
}	t_lst;

/**
 * @brief struct holding information about the camera (player)
 * Currently a work in progress
 * @param x Current x cell of the player in map coordinates
 * @param y Current y cell of the player in map coordinates
 * @param angle Current angle of the player 
 * @param fov_radi Field of view (FOW) expressed in radiants
 * @param plane_distance Distance from the camera and the projeciton plane
 * @param cardinal_point Character containing the starting cardinal(NSOW)
 * @param direction_flags Flag for direction of minimap raycasting
 */
typedef struct s_camera
{
	int			x;
	float		pixel_x;
	float		pdx;
	int			y;
	float		pixel_y;
	float		pdy;		
	float		angle;
	float		fov_radi;
	float		plane_distance;
	char		cardinal_point;
	int			direction_flags;
}	t_camera;

/**
 * @brief Struct used to keep track of the number of identifiers
 * that have been met during the parsing phase
 * @param count_nord number of nord identifiers
 * @param count_south number of south identifiers
 * @param count_west number of west identifiers
 * @param count_floor number of floor identifiers
 * @param count_ceiling number of ceiling identifiers
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
 * @brief Main struct of the game, it contains several informations
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
 * @param working_map Pointer to 2d array of final map
 * @param mini_cell Minimap cell size
 * @param minimap_shifts n_of division by 2 of the minimap cells
 * @param yes_minimap flag to decide whether or not displaying the minimap
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
	char			**working_map;
	int				mini_cell;
	int				minimap_shifts;
	int				yes_minimap;
}	t_game;

/**
 * @brief Main struct of the graphical part of the game
 * Containing several mlx and raycasting elements
 * For now a work in progress since the focus is on the minimap
 * @param ray Ptr to the ray structure
 * @param game Ptr to the game struct
 * @param camera Ptr to the camera struct
 * @param image_player Ptr to the player image
 * @param image_floor Ptr to the image struct for the floor
 * @param image_cealing Ptr to the image struct for the cealing
 * @param main_image Ptr to the image where the game will be drawn
 * @param image_walls Ptr to the image struct for the walls
 * @param north Ptr to the north wall texture
 * @param south Ptr to the south wall texture
 * @param west Ptr to the west wall texture
 * @param east Ptr to the east wall texture
 * @param mlx Ptr to main mlx handler struct
 */
typedef struct s_mlx_data
{
	t_ray				*ray;
	t_game				*game;
	t_camera			*camera;
	mlx_image_t			*image_player;
	mlx_image_t			*image_floor;
	mlx_image_t			*image_cealing;
	mlx_image_t			*main_image;
	mlx_texture_t		*image_walls;
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*west;
	mlx_texture_t		*east;
	mlx_t				*mlx;
}	t_mlx_data;

/* -------------- display_2d_map.c ---------------------------- */
void			display_2d_map(t_mlx_data *mlx_data);

/* -------------- draw_everything.c --------------------------- */
void			draw_everything(void *param);

/* -------------- drawing_environment_2.c --------------------- */
float			get_x_o(mlx_texture_t *texture, t_mlx_data *mlx_data);
void			mlx_put_pixel_special(t_mlx_data *mlx_data, \
										int x, int y, int color);
void			floor_and_ceiling_drawing(t_mlx_data *mlx_data, \
									int high_pixel, int low_pixel);

/* -------------- drawing_environment.c ----------------------- */
void			wall_drawing(t_mlx_data *mlx_data, float slice_height, \
									int high_pixel, int low_pixel);
void			manage_wall_slice(t_mlx_data *mlx_data);

/* -------------- bresenham.c ----------------------- */
void			bresenham_line(t_mlx_data *mlx_data, t_point start, \
													t_point end);
void			initialize_b_struct(t_bre *b, t_point *start, t_point *end);
void			store_bresenham_coordinates(t_ray *ray, t_camera *camera);

/* -------------- errors.c ------------------------------------ */
void			print_error_and_exit(char *err_msg);
void			free_print_error_and_exit(void *free_me, char *err_msg);

/* -------------- parsing map management ---------------------- */
int				check_adapt_and_copy_map(t_game *game);
int				map_enclosed_by_walls(t_game *game);

/* -------------- parsing_identifiers_functions --------------- */

int				check_ids_and_get_map_start(t_lst *list, t_game *game);
int				check_ids_and_info(char *line, t_game *game);
int				manage_floor_cealing_ids_and_usless_char(char *line, \
													t_game *game);
int				split_store_and_check_rbg_amount(char *temp, \
											int n_id, t_game *game);
void			increment_id_count(t_game *game, int n_id);

/* -------------- general_parsing_funcitons ------------------- */
char			*get_next_line(int fd);
int				successfull_parsing(int argc, char **argv, t_game *game);

/* -------------- free memory functions ----------------------- */
void			free_list(t_lst *lst);
void			free_split(char **ss);
void			free_game(t_game *game);
void			free_game_parsing(t_game *game);
void			free_mlx_resources(t_mlx_data *mlx_data);

/* -------------- raycasting ---------------------------------- */
void			ray_casting(t_mlx_data *mlx_data);
void			bresenham_line(t_mlx_data *mlx_data, t_point start, \
													t_point end);
float			normalize_angle(float angle);
void			inc_and_pixel_vert(float angle, float *inc_x, \
							int *add_pixel_x, float *y_inc);
void			inc_and_pixel_horiz(float angle, float *y_inc, \
							int *add_pixel_y, float *x_inc);
int				wall_hit_or_out_bounds(t_mlx_data *mlx_data, float inter_y, \
									float inter_x, int flag);

/* -------------- utility funciton to adjust angles ----------- */
float			normalize_angle(float angle);

/* -------------- initialize_data_for_mlx.c ------------------- */
int				initialize_data_for_mlx(t_game *game, t_mlx_data *mlx_data);

/* -------------- key_hooks.c --------------------------------- */
void			ft_custom_key(void *param);
void			inc_and_pixel_vert(float angle, float *inc_x, \
									int *add_pixel_x, float *y_inc);
void			inc_and_pixel_horiz(float angle, float *y_inc, \
									int *add_pixel_y, float *x_inc);
float			get_angle_direction(t_mlx_data *mlx_data, int direction_flags);
float			obtain_h_inter(t_mlx_data *mlx_data, float angle);
float			obtain_v_inter(t_mlx_data *mlx_data, float angle);
void			turn_left_right(t_mlx_data *mlx_data);

#endif
