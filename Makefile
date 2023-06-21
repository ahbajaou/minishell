NAMES = minishell 
 
CFILES = parse_all.c lex1.c lex2.c allocate_Memory.c symboles.c str_join.c handle.c env.c ft_exec.c

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -lreadline

all :  $(NAMES)

$(NAMES) : $(CFILES)
			$(CC) $(CFLAGS) $(CFILES) -o minishell

clean : 
		$(RM) $(NAMES)

fclean : clean 

re : fclean all 
