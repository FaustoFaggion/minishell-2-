NAME			=	minishell
#NAME_BONUS		=	minishell_bonus

PATH_LIBFT		=	./libft
LIBFT			=	$(PATH_LIBFT)/libft.a

I_LIBFT			=	-I ./libft
I_MINISHELL		=	-I ./include
L_READLINE		=	-lreadline

CC				=	clang
CFLAGS			=	-g -Wall -Werror -Wextra

SRC_DIR			=	sources
SRC_FILES		=	minishell.c \
					get_prompt.c \
					token_analysis.c \
					lexical_analysis.c \
					sintax_analysis.c \
					create_cmd_tab.c \
					create_node.c \
					expansion.c \
					expansion_tilde.c \
					expansion_envp.c \
					expansion_utils.c \
					setup_error.c \
					exit.c \
					exit_utils.c \
				#	expansion_d_quote.c \
					cmd_tab_utils.c \
					exec_cmd_path_ck.c \
					exec_cmd_tab.c \
					exec_cmd_pipe.c \
					exec_cmd_redirect.c \
					exec_cmd_d_less.c \
					exec_cmd_d_great.c \
					built_in_cmd.c \
					exec_cmd_echo.c \
					exec_cmd_pwd.c \
					exec_cmd_cd.c \
					exec_cmd_export.c \
					exec_cmd_unset.c \
					exec_cmd_env.c \
					exec_cmd_exit.c \
					handle_signal_prompt.c \
					handle_signal_parent.c \
					handle_signal_child.c \
					handle_signal_here_doc.c \
					#exec_cmd_simple.c \

SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

#SRC_DIR_BONUS	=	sources_bonus
#SRC_FILES_BONUS	=	pipex_bonus.c \
					pipex_utils_bonus.c \
					ft_split_shell_bonus.c \

#SRC_BONUS		=	$(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILES_BONUS))

OBJ_DIR			=	objects
OBJ				=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#OBJ_DIR_BONUS	=	objects_bonus
#OBJ_BONUS		=	$(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

#FS				=	-fsanitize=address -g3

all:	$(NAME)

bonus:	$(NAME_BONUS)

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) -g3 $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(I_MINISHELL) $(I_LIBFT) $(L_READLINE)

#$(NAME_BONUS):	$(LIBFT) $(OBJ_DIR_BONUS) $(OBJ_BONUS)
#	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS) $(I_PIPEX) $(I_LIBFT)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_MINISHELL) $(I_LIBFT)

#$(OBJ_DIR_BONUS)/%.o:	$(SRC_DIR_BONUS)/%.c
#	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX) $(I_LIBFT)

$(LIBFT):
	make -C $(PATH_LIBFT)

$(OBJ_DIR):
	mkdir objects

#$(OBJ_DIR_BONUS):
#	mkdir objects_bonus

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
#	rm -rf $(OBJ_BONUS)
#	rm -rf $(OBJ_DIR_BONUS)
	make -C $(PATH_LIBFT) clean

fclean: clean
	rm -rf $(NAME)
#	rm -rf $(NAME_BONUS)
	make -C $(PATH_LIBFT) fclean

re: fclean all

run:
	make re && ./minishell

#run_bonus:
#	make && ./pipex file1.txt "tr a b" "tr e c" file2.txt

#sanitize:	$(LIBFT) $(OBJ_DIR) $(OBJ)
#	$(CC) $(CFLAGS) $(FS) $(OBJ) $(LIBFT) -o $(NAME) $(I_PIPEX) $(I_LIBFT)
#	./pipex file1.txt "tr a b" "tr e c" file2.txt

valgrind:
	make re && valgrind --leak-check=full --show-leak-kinds=all ./minishell

#valgrind_bonus: $(NAME_BONUS)
#	valgrind --leak-check=full --show-leak-kinds=all ./pipex file1.txt "tr a b" "tr e c" file2.txt