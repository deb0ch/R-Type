CC	=	g++

RM	=	rm -f

CXXFLAGS	+=	-Wextra -Wall
CXXFLAGS	+=	-Werror
CXXFLAGS 	+=	-ansi -pedantic
CXXFLAGS	+=	-I./ECS/core/ -I./ECS/systems/ -I./ECS/components/ -I./ECS/entities/
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-ggdb3 -O0
CXXFLAGS	+=	$(INCLUDE)

INCLUDE =

LIBDIR	=
LIB	=

LDFLAGS	+=	$(LIBDIR) $(LIB)

NAME	=	rtype

SRCS	=	ECS/core/main.cpp		\
		ECS/core/World.cpp		\
\
		ECS/core/Entity.cpp		\
\
		ECS/core/ASystem.cpp		\
		ECS/core/AComponent.cpp		\
\
		ECS/components/FooComponent.cpp	\
		ECS/systems/FooSystem.cpp	\
		ECS/systems/BarSystem.cpp

OBJS	=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

run:		$(NAME)
		./$(NAME) $(PARAMS)

debug:		$(NAME)
		valgrind --track-origins=yes $(OPTIONS) ./$(NAME) $(PARAMS)

.PHONY:		all clean fclean re run debug
