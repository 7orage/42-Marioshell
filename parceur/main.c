
#include "lexeur.h"

// CUT THE TOKEN PROPERLY
char    *cut(char *raw_tok)
{
    char buffer[4096];
    int i = 0;
    int j = 0;
    int is_single = 0;
    int is_double = 0;

    while (raw_tok[i] && raw_tok[i] != '(' && raw_tok[i] != ')' && raw_tok[i] != '>' && raw_tok[i] != '<' && raw_tok[i] != '|' )
    {
        if (!is_single && raw_tok[i] == '\'') // tout premier '
        {
            is_single = 1;
            i++;
        }
        else if (!is_double && raw_tok[i] == '"') // tout premier "
        {
            is_double = 1;
            i++;
        }
        else if (is_single)
        {
            if (raw_tok[i] == '\'')
            {
                is_single = 0;
                i++;
            }
            else
            {
                buffer[j] = raw_tok[i];
                i++;
                j++;
            }
        }
        else if (is_double)
        {
            if (raw_tok[i] == '$')
            {
                i++;//i += find_value();
            }
            else if (raw_tok[i] == '\'')
            {
                is_double = 0;
                i++;
            }
            else
            {
                buffer[j] = raw_tok[i];
                i++;
                j++;
            }
        }
        else
        {
            if (raw_tok[i] == '$')   
                i++;
            buffer[j] = raw_tok[i];
            i++;
            j++;
        }
    }
    while (j > 0 && ft_isspace(buffer[j - 1]))
        j--;
    buffer[j] = '\0';
    return (ft_strdup(buffer));
}

void    lexeur(char *input)
{

    int i = 0;
    lst_lexer     *head = NULL;
    while (input[i])
    {
        while (ft_isspace(input[i]))
            i++;
        if (input[i] == '>')
        {
            if (input[i + 1] == '>')
            {
                add_node_lexer(&head, TOK_RED_BRS, NULL);
                i += 1;
            }
            else
                add_node_lexer(&head, TOK_RED_BR, NULL);
            i += 1;
        }
        else if (input[i] == '<')
        {
            if (input[i + 1] == '<')
            {
                add_node_lexer(&head, TOK_RED_BLS, NULL);
                i += 1;
            }
            else
                add_node_lexer(&head, TOK_RED_BL, NULL);
            i += 1;
        }
        else if (input[i] == '|')
        {
            add_node_lexer(&head, TOK_PIPE, NULL);
            i += 1;
        }
        else if (input[i] == '(')
        {
            add_node_lexer(&head, TOK_PAR_L, NULL);
            i += 1;
        }
        else if (input[i] == ')')
        {
            add_node_lexer(&head, TOK_PAR_R, NULL);
            i += 1;
        }
        else
        {
            char *word = cut(&input[i]);
            if (!word)
                return;
            i += add_node_lexer(&head, TOK_W, word);
        }
    }
    add_node_lexer(&head, TOK_EOF, NULL);
    print_lexer(head);
    return;
}