FLAGS = -Wall -Wextra -Werror
DFLAGS = -fsanitize=address -g
INCLUDES = ../includes
#LDFLAGS="-L/goinfre/mobaz/homebrew/opt/readline/lib"
#CPPFLAGS="-I/goinfre/mobaz/homebrew/opt/readline/include"
LDFLAGS="-L/goinfre/ael-hach/.brew/opt/readline/lib"
CPPFLAGS="-I/goinfre/ael-hach/.brew/opt/readline/include"
FILES = lexer/lexer.c\
		lexer/arg_readers.c\
		lexer/lexer_helpers.c\
		lexer/lexer_utils.c\
		lexer/expanders.c\
		parser/parser.c\
		parser/parser_cmd_ops.c\
		parser/parser_destroy.c\
		parser/parser_error.c\
		parser/parser_helpers.c\
		parser/parser_helpers2.c\
		parser/parser_tools.c\
		strtools/char_to_string.c\
        strtools/ft_putstr_fd.c\
        strtools/ft_strcmp.c\
        strtools/ft_strdup.c\
        strtools/ft_strjoin.c\
        strtools/ft_strlen.c\
        strtools/ft_substr.c\
        strtools/ft_split.c\
        strtools/str_match.c\
		strtools/ft_itoa.c \
		strtools/char_tools.c \
		executor/built_ins/exit.c \
		executor/built_ins/cd.c \
		executor/built_ins/export.c \
		executor/built_ins/unset.c \
		executor/built_ins/echo.c \
		executor/built_ins/pwd.c \
		executor/built_ins/env.c \
		arr_tools/arr_contains.c \
		arr_tools/arr_length.c \
		arr_tools/list_to_arr.c \
		arr_tools/push.c \
		arr_tools/arr_remove.c \
		arr_tools/print_arr.c \
		executor/executor.c\
		executor/utils.c \
		executor/free.c \
		executor/file.c \
		executor/command.c \
		executor/command_2.c \
		executor/path.c \
		executor/heredoc.c \
		executor/fd.c \
		executor/utils2.c \
		executor/signal.c\
		executor/error.c

SRCS = $(patsubst %, srcs/%, $(FILES))
NAME = bazsh

all : $(NAME)

$(NAME): $(SRCS)
	@echo "Building up bazsh.."
	clang $(EXECUTOR) $(DFLAGS) $(SRCS) -lreadline  $(LDFLAGS) $(CPPFLAGS) -o $(NAME)

clean:
	rm bazsh

fclean: clean

re: fclean all
