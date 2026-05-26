//#include "minishell.h"
#include "parceur.h"



void    parce(char *input)
{
    int i = 0;
    parceur     *liste_token;
    while (input[i])
    {
        while (isspace(input[i]) == 1)
            i++;
        if (isred(&input[i]) == 1)
            i+= add_node_parceur(TOK_RED, &input[i], &liste_token);
        else if (ispipe(&input[i]) == 1)
            i+= add_node_parceur(TOK_PIPE, &input[i], &liste_token);
        else if (is_exst(&input[i]) == 1)
            i+= add_node_parceur(TOK_EXST, &input[i], &liste_token);
        else if (ishenv(&input[i]) == 1)
            i+= add_node_parceur(TOK_HENV, &input[i], &liste_token);
        else if (iscmd(&input[i]) == 1)
            i+= add_node_parceur(TOK_CMD, &input[i], &liste_token);
        else if (isop(&input[i]) == 1)
            i+= add_node_parceur(TOK_OP, &input[i], &liste_token);
        else if (input[i] == '\0')
           return;
        else
            i+= add_node_parceur(TOK_OBJ, &input[i], &liste_token);
    }
}

int	main(void)
{
	char    input = "cat lol.c | cat > lol.c";

    parce(input);
}