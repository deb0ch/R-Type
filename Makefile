RM		=	rm -f

NAME		=	RType

NAME_CLIENT	=	RType_Client

all:		$(NAME)

$(NAME):
		mkdir -p build
		cd build && cmake ..
		$(MAKE) -C build
		mv build/$(NAME) .
		mv build/$(NAME_CLIENT) ..

clean:
		$(MAKE) clean -C build

fclean:		clean
		$(RM) $(NAME)

sfml:
		mkdir -p SFML-src/build
		cd SFML-src/build && cmake ..
		$(MAKE) -C SFML-src/build

installsfml:	sfml
		$(MAKE) install -C SFML-src/build/
		cp /usr/local/lib/libsfml-* /usr/lib

re:		fclean all

run:		$(NAME)
		./$(NAME) $(PARAMS)

debug:		$(NAME)
		valgrind --track-origins=yes $(OPTIONS) ./$(NAME) $(PARAMS)

doc:
		doxygen doxygen.cfg

.PHONY:		$(NAME) all clean fclean re run debug doc
