NAME = fdf
SRCS = check_argc.c check_filename.c check_map.c convert_coordinates.c create_window.c draw_wireframe.c get_mapinfo.c get_next_line.c main.c put_error.c\
		get_next_line_copy.c
OBJS = $(SRCS:.c=.o)
HEADER = fdf.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
#LINUX_MLXFLAGS = -lmlx_Linux -lXext -lX11 -lm #for Linux
MLXFLAGS = -Imlx -lmlx -framework OpenGL -framework AppKit -lm
LIBDIR = ./libft
LIBFT = ./libft/libft.a

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(MLXFLAGS) -o $(NAME)

$(OBJS):	$(SRCS) $(HEADER)
	$(CC) $(CFLAGS) -c $(SRCS)

$(LIBFT):
	make -C $(LIBDIR)

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBDIR)

fclean:	clean
	rm -rf $(NAME)
	make fclean -C $(LIBDIR)

re: fclean all

.PHONY: all clean fclean re