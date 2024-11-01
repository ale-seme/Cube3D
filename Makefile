NAME = cub3D

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

LINKS =

INCLUDES = -I./libft -I./include

MLXFLAGS = MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

SRC = main.c get_next_line.c initial_parsing.c parsing_ids_1.c \
	parsing_ids_2.c parsing_ids_3.c parsing_ids_4.c parsing_map.c \
	free_stuff.c raycaster.c draw_everything.c key_hooks_2.c \
	drawing_environment.c errors.c initialize_data_for_mlx.c key_hooks.c \
	display_2d_map.c drawing_environment_2.c bresenham.c raycaster2.c

DIR_SRC = src

DIR_OBJ = obj

SRC := ${addprefix ${DIR_SRC}/, ${SRC}}


OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

LIBFT = libft/libft.a

GIT_MLX = git clone https://github.com/codam-coding-college/MLX42.git

MLX_LIB = MLX42/build/libmlx42.a

${NAME}: ${MLX_LIB} ${OBJ} ${LIBFT}
	@${CC} -o ${CFLAGS} $^ ${LINKS} -o $@ $(MLXFLAGS)

all : ${NAME}

${LIBFT}:
	@make bonus -C libft

${MLX_LIB}:
	$(GIT_MLX)
	cd MLX42 && cmake -B build
	cd MLX42 && cmake --build build -j4 && clear


${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	@rm -rf ${DIR_OBJ}

fclean: clean
	rm -rf MLX42
	@rm -rf ${NAME}
	@make fclean -C libft

re: fclean all 

.PHONY: all clean fclean re
