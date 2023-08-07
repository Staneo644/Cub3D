CC := gcc

NAME := Cub3D

CFLAGS := -Wall -Wextra -Werror -O3

MLX_FLAGS := -L mlx -lmlx -lm -framework OpenGL -framework AppKit

INC_FLAGS := -I mlx -I includes

SRCS := ft_itoa.c get_next_line.c minimap.c parsing.c process.c raycast.c\
		 utils.c colors.c pixels.c hooks.c init_struct.c\
		 launch_ray.c draw.c t_map_func.c write_func.c map_parse.c libft.c check_map.c\
		 file_color_parse.c

OBJS := ${SRCS:.c=.o}

OBJDIR := $(addprefix obj/, $(OBJS))

INCLUDES := includes/cub.h includes/get_next_line.h mlx/mlx.h

RM  := rm -f 

all : $(NAME)

$(NAME) : $(OBJDIR)
	echo "\x1b[34m $1[Compiling Cub3D]\x1b[0m"
	$(CC) $(MLX_FLAGS) $(INC_FLAGS) $(OBJDIR) $(CFLAGS) -o $(NAME)
	echo "\x1b[34m $1[Done]\x1b[0m"

obj/%.o : src/%.c $(INCLUDES) Makefile
	mkdir -p obj
	$(CC) -c $< $(INC_FLAGS) $(CFLAGS) -o $@

clean :
	$(RM) $(OBJDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re libft
.SILENT :