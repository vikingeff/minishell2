#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleger <gleger@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/03 14:29:03 by gleger            #+#    #+#              #
#    Updated: 2014/05/18 12:26:36 by gleger           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_minishell2

SRC = 	main.c\
		error.c\
		shell_ini.c\
		sh_env.c\
		sh_unsetenv.c\
		sh_setenv.c\
		sh_cd.c\
		env_array_to_list.c\
		env_list_to_array.c\
		env_get_value.c\
		env_list_add.c\
		str_join_chr.c\
		prompt_display.c\
		command_parse.c\
		command_get_env.c\
		command_execute.c\
		command_shell.c\
		ft_strsplit_all.c\
		ft_tablen.c\
		ft_lst.c\
		ft_modify_arg.c\
		ft_parser_direct.c\
		ft_utility.c\
		ft_signal.c\
		ft_free_arg.c\
		ft_open.c\
		ft_pipe.c\
		ft_execute.c\
		ft_close_count_pipe.c\
		sh_tool.c\
		ft_inib.c\
		ft_parser.c\
		sh_env_utility.c\
		local_var.c\
		command_execute_simple.c\
		sh_cd_goto.c\
		ft_execute_backquote.c\
		ft_delete_char.c\
		sh_alias.c\
		ft_get_alias.c\
		sh_unalias.c\
		command_get.c\
		term_ini.c\
		term_edit_set.c\
		term_canonical_mode.c\
		term_put.c\
		term_set_attr.c\
		term_std_set.c\
		keys.c\
		key_jump.c\
		key_jump_line.c\
		edit_key.c\
		edit_char_add.c\
		edit_char_del.c\
		edit_erase_display.c\
		edit_line_display.c\
		edit_list_to_str.c\
		hist.c\
		hist_utils.c\
		hist_navigation.c\
		hist_chr.c\
		hist_launch.c\
		completion.c\
		reset_comp.c\
		fill_completion.c\
		utils.c\
		ft_globing.c\
		ft_parser_next.c\
		gnl.c\
		ft_strtools.c\
		ft_strother.c\
		ft_strcheck.c\
		ft_itoa.c\
		ft_putsome.c\
		ft_putmore.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -g -O3

LIBFT = libft/libft.a

MANPATH := ${PWD}/MAN

all: $(NAME)

$(NAME): $(OBJ) ./include/shell.h 
	@echo "\033[1;35;m[Linking] \t\t\033[0m: " | tr -d '\n'
	gcc $(FLAG) $(OBJ) -L /usr/lib -ltermcap -o $(NAME)
	@echo "\033[1;32;m[Compilation done]\033[0m"

$(LIBFT):
	@echo "\033[1;35;m[Linking Libft]\033[0m"

%.o: src/%.c
	@echo "\033[1;36;m[Compiling $<]\t\033[0m: " | tr -d '\n'
	gcc -c $(FLAG) $< -I include/

clean:
	@echo "\033[0;33;m[Cleaning objects]\033[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[0;31;m[Deleting $(NAME)]\033[0m"
	@rm -f $(NAME)

re: fclean all

rtfm:
	set -e; \
    . ./MAN/expman.sh;
    
git:
	git add src include/shell.h Makefile MAN
	git commit -m "auto push"
	git push

.PHONY: all clean fclean re git rtfm
