//#include "minishell.h"
#include "parceur.h"
#include <stdio.h>


void    parce(char *input)
{
    int i = 0;
    int len = 0;
   // parceur     *liste_token;
    while (input[i])
    {
        while (ft_isspace(input[i]) == 1)
            i++;
        if ((len = is_red(&input[i])) > 0)
        {
            printf("RED\n");
            printf("la string :%s\n", &input[i]);
            i+= len;
            //i+= add_node_parceur(TOK_RED, &input[i], &liste_token);
        }
        else if ((len = is_pipe(&input[i])) > 0)
        {
            printf("PIPE\n");
            printf("la string :%s\n", &input[i]);
            i+= len;
            //i+= add_node_parceur(TOK_PIPE, &input[i], &liste_token);
        }
        else if ((len = is_exst(&input[i])) > 0)
        {
            printf("EXST\n");
            printf("la string :%s\n", &input[i]);
            i+= len;
            //i+= add_node_parceur(TOK_EXST, &input[i], &liste_token);
        }
        else if ((len = is_venv(&input[i])) > 0)
        {
            printf("HENV\n");
            printf("la string :%s\n", &input[i]);
            i+= len;
            //i+= add_node_parceur(TOK_HENV, &input[i], &liste_token);
        }
        else if ((len = is_cmd(&input[i])) > 0)
        {
            printf("CMD\n");
            printf("la string :%s\n", &input[i]);
            i+= len;
                //i+= add_node_parceur(TOK_CMD, &input[i], &liste_token);
        }
       // else if (isop(&input[i]) == 1)
         //   //i+= add_node_parceur(TOK_OP, &input[i], &liste_token);
        else if (input[i] == '\0')
           return;
        else
        {
            printf("OBJ\n");
            printf("la string :%s\n", &input[i]);          
            i+= is_obj(&input[i]);
            //i+= add_node_parceur(TOK_OBJ, &input[i], &liste_token);
        }
    }
}

int	main(void)
{
	char    *input = "cd lol.c | echo > lol.c << pwd  $?    $HEYY";

    parce(input);
}