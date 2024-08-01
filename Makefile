NAME = fdf
SRCS = main.c\
		check_argc.c\
		check_filename.c\
		check_map.c\
		convert_coordinates.c\
		convert_coordinates_2.c\
		convert_coordinates_3.c\
		draw_wireframe.c\
		draw_wireframe_2.c\
		get_mapinfo.c\
		get_mapinfo_2.c\
		get_next_line.c\
		get_next_line_second.c\
		put_error.c\
		fdf_utils.c\
		event_hook.c
OBJS = $(SRCS:.c=.o)
HEADER = fdf.h
INCDIR = .
CC = cc
CFLAGS = -Wall -Wextra -Werror
LINUX_MLXFLAGS = -lXext -lX11 -lm
MLXFLAGS = -Imlx -lmlx -framework OpenGL -framework AppKit -lm #for macOS
LIBDIR = ./libft
LIBFT = ./libft/libft.a
MLXDIR = ./minilibx-linux
MLXLIB = ./minilibx-linux/libmlx_Linux.a

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(MLXLIB)
	@$(CC) $(OBJS) $(LIBFT) $(MLXLIB) $(CFLAGS) $(LINUX_MLXFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS)	-c $< -o $@ -I $(INCDIR)
	@echo "| fdf"

$(LIBFT):
	@make -C $(LIBDIR)

$(MLXLIB):
	@make -C $(MLXDIR)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBDIR)
	@make clean -C $(MLXDIR)

fclean:	clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBDIR)
	@make fclean -C $(MLXDIR)

re: fclean all

.PHONY: all clean fclean re