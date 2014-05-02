CC	=	g++

RM	=	rm -f

CXXFLAGS	+=	-Wextra -Wall
CXXFLAGS	+=	-Werror
CXXFLAGS 	+=	-ansi -pedantic
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-ggdb3 -O0
CXXFLAGS	+=	$(INCLUDE)

INCLUDE		=	-I./ECS/ -I./components/ -I./systems/

LIBDIR		=	-L./ECS/
LIB		=	-lecs

LDFLAGS	+=	$(LIBDIR) $(LIB)

NAME	=	rtype

SRCS	=	main.cpp			\
\
		components/Pos2DComponent.cpp	\
\
		systems/MoveSystem.cpp

OBJS	=	$(SRCS:.cpp=.o)

all:		LIBECS $(NAME)

LIBECS:
		make -C ./ECS/

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJS)
		make clean -C ./ECS/

fclean:		clean
		$(RM) $(NAME)
		make fclean -C ./ECS/

re:		fclean all

run:		$(NAME)
		./$(NAME) $(PARAMS)

debug:		$(NAME)
		valgrind --track-origins=yes $(OPTIONS) ./$(NAME) $(PARAMS)

.PHONY:		all clean fclean re run debug
