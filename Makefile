NAME = fdf
SRCS = main.c\
		check_argc.c\
		check_filename.c\
		check_map.c\
		convert_coordinates.c\
		convert_coordinates_utils.c\
		draw_wireframe.c\
		draw_wireframe_2.c\
		get_mapinfo.c\
		get_mapinfo_2.c\
		get_next_line.c\
		get_next_line_second.c\
		put_error.c\
		fdf_utils.c
OBJS = $(SRCS:.c=.o)
HEADER = fdf.h
INCDIR = .
CC = cc
CFLAGS = -Wall -Wextra -Werror
LINUX_MLXFLAGS = -lmlx_Linux -lXext -lX11 -lm #for Linux
MLXFLAGS = -Imlx -lmlx -framework OpenGL -framework AppKit -lm
LIBDIR = ./libft
LIBFT = ./libft/libft.a

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(MLXFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS)	-c $< -o $@ -I $(INCDIR)
	@echo "| fdf"

$(LIBFT):
	@make -C $(LIBDIR)

clean:
	@rm -rf $(OBJS)
	make clean -C $(LIBDIR)

fclean:	clean
	@rm -rf $(NAME)
	make fclean -C $(LIBDIR)

re: fclean all

.PHONY: all clean fclean re