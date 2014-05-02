CXX	=	g++

RM	=	rm -f

CXXFLAGS	+=	-Wextra -Wall
CXXFLAGS	+=	-Werror
CXXFLAGS 	+=	-pedantic
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-ggdb3 -O0
CXXFLAGS	+=	$(INCLUDE)

INCLUDE		=	-I./ECS/ -I./components/ -I./systems/ -I./events/ -I./lib/SFML-1.6/includes -I./Network/

LIBDIR		+=	-L./ECS/ -L./Network/build/
#LIBDIR		+=	-L./lib/openal-soft-1.15.1/
#LIBDIR		+=	-L./lib/SFML-1.6/lib/
LIB		+=	-lecs
#LIB		+=	-lopenal
LIB		+=	-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lNetworklib

LDFLAGS	+=	$(LIBDIR) $(LIB)

NAME	=	rtype

SRCS	=	main.cpp				\
\
		components/Pos2DComponent.cpp		\
		components/Box2DComponent.cpp		\
		components/NetworkUpdateComponent.cpp	\
\
		systems/MoveSystem.cpp			\
		systems/CollisionSystem.cpp		\
		systems/Networksystem.cpp		\
\
		events/CollisionEvent.cpp

OBJS	=	$(SRCS:.cpp=.o)

all:		LIBNETWORK LIBECS $(NAME)

LIBECS:
		make -C ./ECS/

LIBNETWORK:
		mkdir -p Network/build
		cd Network/build && cmake ..
		$(MAKE) -C Network/build

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

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
