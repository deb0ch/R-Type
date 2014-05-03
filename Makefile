CXX	=	g++

RM	=	rm -f

CXXFLAGS	+=	-Wextra -Wall
CXXFLAGS	+=	-Werror
CXXFLAGS 	+=	-pedantic
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-ggdb3 -O0
CXXFLAGS	+=	$(INCLUDE)

INCLUDE		=	-I./ECS/ -I./components/ -I./systems/ -I./events/ -I./lib/SFML-1.6/includes -I./Network/ -I./SFML-src/include/

LIBDIR		+=	-L./ECS/ -L./Network/build/ -L./SFML-src/build/lib/
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
		components/Speed2DComponent.cpp		\
		components/Box2DComponent.cpp		\
		components/SFMLSpriteComponent.cpp	\
		components/NetworkUpdateComponent.cpp	\
\
		events/CollisionEvent.cpp		\
\
		systems/NetworkSystem.cpp		\
		systems/MoveSystem.cpp			\
		systems/CollisionSystem.cpp		\
		systems/SFMLRenderSystem.cpp

OBJS	=	$(SRCS:.cpp=.o)

all:		LIBNETWORK LIBECS LIBSFML $(NAME)

LIBECS:
		$(MAKE) -C ./ECS/

LIBSFML:
		mkdir -p SFML-src/build
		cd SFML-src/build && cmake ..
		$(MAKE) -C ./SFML-src/build

LIBNETWORK:
		mkdir -p Network/build
		cd Network/build && cmake ..
		$(MAKE) -C Network/build

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C ./ECS/
		$(MAKE) clean -C Network/build
		$(MAKE) clean -C SFML-src/build

fclean:		clean
		$(RM) $(NAME)
		$(MAKE) fclean -C ./ECS/
		$(MAKE) fclean -C Network/build

installsfml:	LIBSFML
		$(MAKE) install -C SFML-src/build/

re:		fclean all

run:		$(NAME)
		./$(NAME) $(PARAMS)

debug:		$(NAME)
		valgrind --track-origins=yes $(OPTIONS) ./$(NAME) $(PARAMS)

.PHONY:		all clean fclean re run debug
