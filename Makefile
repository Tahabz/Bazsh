kFLAGS = -Wall -Wextra -Werror
DFLAGS = -fsanitize=address -g
INCLUDES = ../includes
NAME = lexer
LIBS = srcs/libs/libft.a
FILES = main.c \
		lexer.c \
		token/token.c \
		get_next_line/get_next_line.c
SRCS = $(patsubst %, srcs/%, $(FILES))
all : $(NAME)

$(NAME): $(SRCS)
	make -C srcs/libft/
	@echo "Building up the lexer.."
	clang $(DFLAGS) $(FLAGS) $(SRCS) $(LIBS) -o $(NAME)

clean:
	rm -rf lexer

fclean: clean
	rm -rf lexer
	cd libft; make fclean

test: all srcs/lexer_tests.c
	clang srcs/lexer.c srcs/token/token.c srcs/lexer_tests.c srcs/libs/libft.a -o test && ./test
re: fclean all
