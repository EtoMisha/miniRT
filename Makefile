SRCS =  main.c			create_camera_light.c 		vectors.c \
		parser.c 		create_sphere_plane.c 		vectors2.c \
		draw.c			create_cylinder.c			intersection.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

ADD_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

INCLUDES = minirt.h libft/libft.h mlx/mlx.h objects.h vectors.h

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

NAME = miniRT

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(FLAGS) $(ADD_FLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(MLX_LIB)

$(LIBFT_LIB): libft ;

$(MLX_LIB): libmlx ;

%.o:%.c ${INCLUDES} Makefile
		gcc ${FLAGS} -o $@ -c $<

libft:
	make -C $(LIBFT_DIR)

libmlx:
	make -C $(MLX_DIR)

all : $(NAME)

clean :
	rm -rf $(OBJS)
	make -C libft clean
	make -C mlx clean

fclean : clean
	rm -rf $(NAME) libft/libft.a
	rm -rf $(NAME) mlx/libmlx.a

re : fclean all

.PHONY: all libft libmlx clean fclean re