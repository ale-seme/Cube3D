NAME = cub3D

CFLAGS = -g -fsanitize=address #-Wall -Werror -Wextra

LINKS =

INCLUDES = -I./libft -I./include

MLXFLAGS = MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

SRC = main.c get_next_line.c initial_parsing.c parsing_ids_1.c \
	parsing_ids_2.c parsing_ids_3.c parsing_ids_4.c parsing_map.c \
	free_stuff.c raycaster.c 2d_minimap_test.c test.c

DIR_SRC = src

DIR_OBJ = obj

SRC := ${addprefix ${DIR_SRC}/, ${SRC}}


OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

LIBFT = libft/libft.a

GIT_MLX = git clone https://github.com/codam-coding-college/MLX42.git

${NAME}: ${OBJ} ${LIBFT}
	@${CC} -o ${CFLAGS} $^ ${LINKS} -o $@ $(MLXFLAGS)

all : ${NAME}

${LIBFT}:
	@make bonus -C libft

${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	@rm -rf ${DIR_OBJ}

fclean: clean
	@rm -rf ${NAME}
	@make fclean -C libft

download_mlx42:
	$(GIT_MLX)
	cd MLX42 && cmake -B build
	cd MLX42 && cmake --build build -j4 && clear
	echo "\033[0;32mNow you can "make" and play :=D\033[0m"

delete_mlx42:
	rm -rf MLX42

re: fclean all 

.PHONY: all clean fclean re
