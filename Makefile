NAMES = minishell 
 
CFILES = main.c parser.c lex1.c mc_alloc.c wolf_parse.c special_char.c send_mini_string.c quots_and_dollar.c func_special_char.c env.c

CC = CC -g

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -lreadline

all :  $(NAMES)

$(NAMES) : $(CFILES)
			$(CC) $(CFLAGS) $(CFILES) -o minishell

clean : 
		$(RM) $(NAMES)

fclean : clean 

re : fclean all 
