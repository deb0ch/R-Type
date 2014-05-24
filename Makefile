RM		=	rm -f

NAME_C	=	RType_Client
NAME_S	=	RType_Server

all:		$(NAME_C) $(NAME_S)

		mkdir -p build
		cd build && cmake ..
		$(MAKE) -j 8 -C build
		ln -sf build/$(NAME_C) .
		ln -sf build/$(NAME_S) .

clean:
		$(MAKE) clean -C build

fclean:		clean
		$(RM) $(NAME_C)
		$(RM) $(NAME_S)

sfml:
		mkdir -p SFML-src/build
		cd SFML-src/build && cmake ..
		$(MAKE) -C SFML-src/build

installsfml:	sfml
		$(MAKE) install -C SFML-src/build/
		cp /usr/local/lib/libsfml-* /usr/lib

re:		fclean all

run:		$(NAME_C)
		./$(NAME_C) $(PARAMS)

debug:		$(NAME_C)
		valgrind --track-origins=yes $(OPTIONS) ./$(NAME_C) $(PARAMS)

doc:
		doxygen doxygen.cfg

.PHONY:		$(NAME_C) $(NAME_S) all clean fclean re run debug doc
