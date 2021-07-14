FLAGS = -Wall -Wextra -Werror
DFLAGS = -fsanitize=address -g
INCLUDES = ../includes
NAME = lexer
LIBS = ./libs/libft.a
SRCS = 	main.c \
		lexer.c \
		token/token.c \
		get_next_line/get_next_line.c

all : $(SRCS)
	make -C libft/
	@echo "Building up the lexer.."
	clang $(DFLAGS) $(FLAGS) $(SRCS) $(LIBS) -o $(NAME)

clean:
	rm -rf lexer

fclean: clean
	rm -rf lexer
	cd libft; make fclean

re: fclean all
