#include "parceur.h"

//tester expansion : 	lst_lexer *head = lexeur("echo $HOME 'a$HOME' \"b$HOME\"", env);


t_lst_ast	*create_ast(t_lst_lexer **liste)
{
	t_lst_ast	*head;

	head = find_pipe(liste);
	free_lexer(*liste);
	return (head);
}

int		main(int argc, char **argv, char **envp)
{
	t_env		*env;
	t_lst_lexer	*head;
	t_lst_ast	*ast;

	(void)argv;
	(void)argc;
	env = envp_list(envp);
	head = lexer("echo 'coucou' > text.txt | echo hi >", env);
	ast = create_ast(&head);
	print_ast(ast);
}