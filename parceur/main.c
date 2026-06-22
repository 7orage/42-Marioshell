
#include "parceur.h"

lst_ast	*create_ast(lst_lexer **liste)
{
	lst_ast	*head = find_pipe(liste);
	free_lexer(*liste);
	return (head);
}

int		main(int argc, char **argv, char **envp)
{
	(void)argv;
    (void)argc;
	t_env *env;

	env = envp_list(envp);
	lst_lexer *head = lexeur("echo  | cat -n > file.txt", env);
	lst_ast *ast = create_ast(&head);
	print_ast(ast);
}