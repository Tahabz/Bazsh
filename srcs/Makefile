FLAGS = -Wall -Wextra -Werror
INCLUDES = ../includes
NAME = lexer
LIBS = ../libs/libft.a
SRCS = 	lexer.c \
		main.c \
		token/token.c \
		get_next_line/*

all : lib $(NAME)
	@echo "Building up the lexer.."

$(NAME): $(SRCS)
	gcc -o $(NAME) $(FLAGS) $(SRCS) $(LIBS) -I $(INCLUDES)

lib:
	cd libft; make

clean:
	rm -rf lexer

fclean: clean
	rm -rf lexer
	cd libft; make fclean

re: fclean all
