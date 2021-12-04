kFLAGS = -Wall -Wextra -Werror
DFLAGS = -fsanitize=address -g
INCLUDES = ../includes
NAME = lexer
LEXER_TEST = lexer_test
PARSER_TEST = parser_test
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

$(LEXER_TEST): tests/lexer_tests.c $(SRCS)
	clang $(DFLAGS) $(FLAGS) tests/lexer_tests.c $(SRCS) -o $(LEXER_TEST)
	./$(LEXER_TEST)

$(PARSER_TEST): tests/parser_tests.c $(SRCS)
	clang $(DFLAGS) $(FLAGS) tests/parser_tests.c srcs/parser.c $(SRCS) -o $(LEXER_TEST)
	./$(LEXER_TEST)

re: fclean all
