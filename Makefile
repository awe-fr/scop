NAME = scop

SRCS = SRCS/main.cpp\
		headers/scopApp.cpp\

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -std=c++17 -O2

LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SHADERS = compile.sh

all: 		$(NAME)

$(NAME):	$(OBJS)
			cd shaders && ./$(SHADERS)
		g++ $(CFLAGS) -o $(NAME) $(SRCS) $(LDFLAGS)

test: 		$(NAME)
		./$(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f shaders/frag.spv
		rm -f shaders/vert.spv
		rm -f $(NAME)

re:		fclean all

.PHONY: all test clean fclean re