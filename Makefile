NAME = scop

SRCS = main.cpp\
		Window.cpp\

OBJS = $(SRCS:.cpp=.o)

CC = c++

CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -I/usr/local/include/glm/glm/glm -Iincludes $(SRCS) -o $(NAME) `sdl2-config --cflags --libs` -g
				
clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re
