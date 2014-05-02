CC	=	g++

RM	=	rm -f

CXXFLAGS	+=	-Wextra -Wall
CXXFLAGS	+=	-Werror
CXXFLAGS 	+=	-ansi -pedantic
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-ggdb3 -O0
CXXFLAGS	+=	$(INCLUDE)

INCLUDE		=	-I./core/ -I./systems/ -I./components/ -I./entities/

#LIBDIR		=
#LIB		=

#LDFLAGS	+=	$(LIBDIR) $(LIB)

NAME	=	libecs.a

SRCS	=	core/World.cpp			\
		core/Entity.cpp			\
		core/AComponent.cpp		\
		core/ASystem.cpp

OBJS	=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		ar rcs $(NAME) $(OBJS)
		mkdir -p includes/
		cp core/*.hh includes/

clean:
		$(RM) $(OBJS)
		$(RM) -r includes/

fclean:		clean
		$(RM) $(NAME)
		rm -rf includes/

re:		fclean all

#run:		$(NAME)
#		./$(NAME) $(PARAMS)

#debug:		$(NAME)
#		valgrind --track-origins=yes $(OPTIONS) ./$(NAME) $(PARAMS)

.PHONY:		all clean fclean re
#run debug
