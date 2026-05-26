#include "parceur.h"

// VERIF CONDITION == 1
int     ft_isspace(char c)
{
    if ((c >= 9 && c <= 13) || c == ' ')
        return (1);
    return (0);
}

/* TOKEN TYPE FUNDING*/
// IS IT A REDIRECTION ?
int     is_red(char *token)
{
    int     i = 0;

    while (ft_isspace(token[i]) == 1)
        i++;
    if (token[i] == '>' || token[i] == '<')
    {
        if (ft_isspace(token[i + 1]) == 1 || token[i + 1] == '\0')
            return (1);
        else if (token[i] == token[i + 1])
        {
            if (ft_isspace(token[i + 2]) == 1 || token[i + 2] == '\0')
                return (1);
        }
    }
    return (0);
} 

// IS IT A PIPE ?
int     is_pipe(char *token)
{
    int     i = 0;

    while (ft_isspace(token[i]) == 1)
        i++;
    if (token[i] == '|')
    {
        if (ft_isspace(token[i + 1]) == 1 || token[i + 1] == '\0')
            return (1);
    }
    return (0);
}

// IT IS A '$?' (EXIT STATUS) ?
int     is_exst(char *token)
{
    int     i = 0;

    while (token[i] != '\0' && (ft_isspace(token[i]) == 1 || token[i] == '\'' || token[i] == '"'))
        i++;
    if (token[i] == '$')
    {
        i += 1;
        if (token[i] == '?')
        {
            i += 1;
            if (token[i] == '\0' || ft_isspace(token[i]) == 1 || token[i] == '\'' || token[i] == '"')
                return (i);
            else
                return (0);
            i++;
        }
    }
    return (0);
}

// IS IT AN ENVIRONMENT VARIABLE ?
int     is_venv(char *token)
{
    int     i = 0;

    while (token[i] != '\0' && (ft_isspace(token[i]) == 1 || token[i] == '\'' || token[i] == '"'))
        i++;
    if (token[i] == '$')
    {
        i+= 1;
        while(1)
        {
            if (token[i] >= 65 && token[i] <= 90)
                i++;
            else
            {
                if (token[i] == '\0' || ft_isspace(token[i]) == 1 || token[i] == '\'' || token[i] == '"')
                    return (i);
                else
                    return (0);
            }
        }
    }
    return (0);
}

// IS IT A CMD ?
int     is_cmd(char *token)
{
    int     i = 0;
    int     j = 0;
    char    *cmds[] = {
        "echo",
        "cd",
        "pwd",
        "export",
        "unset",
        "env",
        "exit",
        NULL
    };

    while (ft_isspace(token[i]) == 1)
        i++;
    while (cmds[j])
    {
        if (ft_strncmp(cmds[j], &token[i], ft_strlen(cmds[j])) == 0)
            return (ft_strlen(cmds[j]));
        else
            j++;
    }
    return (0);
}

// IS IT AN OPTION ?
int     is_op(char *token)
{
    int     i = 0;

    while (ft_isspace(token[i]) == 1)
        i++;
    if (ft_strncmp("-n", &token[i], 2) == 0)
            return (2);
    return (0);
}

// IT IS AN OBJECT (file...) ?
int     is_obj(char *token)
{
    int     i = 0;

    while (token[i] && ft_isspace(token[i]) == 1)
        i++;
    while (token[i] && ft_isspace(token[i]) == 0)
        i++;
    while (token[i] && ft_isspace(token[i]) == 1)
        i++;
    return (i);
}

/*
#include <stdio.h>
int main(int argc, char **argv)
{
    (void)argc;
    printf("la rep : %d\n", is_cmd(argv[1]));
}*/

