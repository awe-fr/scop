NAME = scop

SRCS = main.cpp\

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -std=c++17 -O2

LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

all: 		$(NAME)

$(NAME):	$(OBJS)
		g++ $(CFLAGS) -o $(NAME) main.cpp $(LDFLAGS)


test: 		$(NAME)
		./$(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)


re:		fclean all

.PHONY: all test clean fclean re