RM	=	rm -f

NAME	=	RType

all:		$(NAME)

$(NAME):
		mkdir -p build
		cd build && cmake ..
		$(MAKE) -C build
		mv build/$(NAME) .

clean:
		$(MAKE) clean -C build

fclean:		clean
		$(RM) $(NAME)

installsfml:	LIBSFML
		$(MAKE) install -C SFML-src/build/
		cp /usr/local/lib/libsfml-* /usr/lib

re:		fclean all

run:		$(NAME)
		./$(NAME) $(PARAMS)

debug:		$(NAME)
		valgrind --track-origins=yes $(OPTIONS) ./$(NAME) $(PARAMS)

.PHONY:		$(NAME) all clean fclean re run debug
