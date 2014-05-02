CC	=	g++

RM	=	rm -f

CXXFLAGS	+=	-Wextra -Wall
CXXFLAGS	+=	-Werror
CXXFLAGS 	+=	-ansi -pedantic
CXXFLAGS	+=	-I./core/ -I./systems/ -I./components/ -I./entities/
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-ggdb3 -O0
CXXFLAGS	+=	$(INCLUDE)

INCLUDE =

LIBDIR	=
LIB	=

LDFLAGS	+=	$(LIBDIR) $(LIB)

NAME	=	rtype

SRCS	=	core/main.cpp		\
		core/World.cpp		\
\
		core/Entity.cpp		\
\
		core/ASystem.cpp		\
		core/AComponent.cpp		\
\
		components/FooComponent.cpp	\
		systems/FooSystem.cpp	\
		systems/BarSystem.cpp

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
