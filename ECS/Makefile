CXX		=	g++

RM		=	rm -f

CXXFLAGS	+=	-Wextra -Wall
CXXFLAGS	+=	-Werror
CXXFLAGS 	+=	-ansi -pedantic
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-ggdb3 -O0
CXXFLAGS	+=	$(INCLUDE)

INCLUDE		=

#LIBDIR		=
#LIB		=

#LDFLAGS	+=	$(LIBDIR) $(LIB)

NAME	=	libecs.a

SRCS	=	World.cpp		\
		Entity.cpp		\
		AComponent.cpp		\
		ASystem.cpp		\
		AEvent.cpp

OBJS	=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		ar rcs $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

#run:		$(NAME)
#		./$(NAME) $(PARAMS)

#debug:		$(NAME)
#		valgrind --track-origins=yes $(OPTIONS) ./$(NAME) $(PARAMS)

.PHONY:		all clean fclean re
#run debug
