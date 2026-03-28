NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCS	= -Iinclude

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	RL_LIBS = -lreadline -lhistory -ltermcap
else
	RL_LIBS = -lreadline -lhistory -lncurses
endif

SRCS	= \
src/main.c \
src/utils/part_list.c \
src/utils/token_list.c \
src/utils/str_utils.c \
src/utils/str_more.c \
src/utils/str_join.c \
src/utils/io_utils.c \
src/utils/argv.c \
src/utils/argv_expanded.c \
src/utils/arg_list.c \
src/utils/redir_list.c \
src/utils/cmd_list.c \
src/utils/pipeline.c \
src/utils/part_join.c \
src/lexer/lex_word.c \
src/lexer/lex_line.c \
src/parser/syntax_error.c \
src/parser/validate_tokens.c \
src/parser/parse_utils.c \
src/parser/parse_tokens.c \
src/parser/parse_handlers.c \
src/parser/parse_line.c \
src/parser/debug_print.c \
src/expander/expand_core.c \
src/expander/expand_utils.c \
src/expander/expand_buf.c \
src/expander/expand_parts.c \
src/env/env_list.c \
src/env/env_build.c \
src/env/env_get.c \
src/env/env_set.c \
src/env/env_unset.c \
src/env/env_export.c \
src/signals/signals.c \
src/signals/jobctl.c \
src/shell/shell_loop.c \
src/builtins/echo.c \
src/builtins/pwd.c \
src/builtins/env.c \
src/builtins/dispatch.c \
src/builtins/cd.c \
src/builtins/export.c \
src/builtins/export_utils.c \
src/builtins/unset.c \
src/builtins/exit.c \
src/exec/execute.c \
src/exec/path.c \
src/exec/path_utils.c \
src/exec/external.c \
src/exec/external_err.c \
src/exec/external_child.c \
src/exec/pipeline.c \
src/exec/pipeline_run.c \
src/exec/pipeline_utils.c \
src/exec/pipeline_child.c \
src/exec/heredoc.c \
src/exec/heredoc_read.c \
src/exec/heredoc_prepare.c \
src/exec/redir.c \
src/exec/redir_file.c \
src/exec/external_cmd.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(RL_LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
