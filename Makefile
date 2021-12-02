kFLAGS = -Wall -Wextra -Werror
DFLAGS = -fsanitize=address -g
INCLUDES = ../includes
NAME = lexer
FILES = lexer.c\
		token/token.c\
		get_next_line/get_next_line.c\
		strtools/char_to_string.c\
        strtools/ft_putstr_fd.c\
        strtools/ft_strcmp.c\
        strtools/ft_strdup.c\
        strtools/ft_strjoin.c\
        strtools/ft_strlen.c\
        strtools/ft_substr.c\
        strtools/str_match.c

SRCS = $(patsubst %, srcs/%, $(FILES))
all : $(NAME)

$(NAME): $(SRCS)
	@echo "Building up the lexer.."
	clang $(DFLAGS) $(FLAGS) srcs/main.c $(SRCS) -o $(NAME)

clean:
	rm -rf lexer

fclean: clean

build_test: tests/lexer_tests.c
	clang $(DFLAGS) $(FLAGS) tests/lexer_tests.c $(SRCS) -o test

test: build_test
	./test

re: fclean all
