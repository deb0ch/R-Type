CC	=	g++

RM	=	rm -f

CXXFLAGS	+=	-Wextra -Wall
CXXFLAGS	+=	-Werror
CXXFLAGS 	+=	-ansi -pedantic
CXXFLAGS	+=	-I./src/core/ -I./src/systems/ -I./src/components/ -I./src/entities/
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-ggdb3 -O0
CXXFLAGS	+=	$(INCLUDE)

INCLUDE =

LIBDIR	=
LIB	=

LDFLAGS	+=	$(LIBDIR) $(LIB)

NAME	=	rtype

SRCS	=	src/core/main.cpp		\
		src/core/World.cpp		\
\
		src/core/Entity.cpp		\
\
		src/core/ASystem.cpp		\
		src/core/AComponent.cpp		\
\
<<<<<<< HEAD:ECS/Makefile
		FooSystem.cpp		\
		BarSystem.cpp		\
		FooComponent.cpp
=======
		src/components/FooComponent.cpp	\
		src/systems/FooSystem.cpp
>>>>>>> develop:Makefile

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
