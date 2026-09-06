/* A REPASSER AVANT FINAL
-norminette

envp       OKKKKKKKKKKKKKKK
lexeur cut OKKKKKKKKKKKKKKK
lexeur lst OKKKKKKKKKKKKKKK
lexeur     OKKKKKKKKKKKKKKK
expand
istype     OKKKKKKKKKKKKKKK
parceur 

- verif leaks 
*/

/* NORMINETTE
    Lorsqu'on déclare un pointeur, pour pouvoir l'initialiser sur la même ligne on peut le déclarer suivant:
        -> 	type	* const ptr = xxx ;
    ! Ne pas utiliser ce glich si l'adresse de ptr doit rester modifiable !
*/

/*TEST
echo 'coucou' > text.txt
echo hello | cat
ls > out.txt | wc -l
cat f | grep a | wc -l
cat < in.txt | grep x > res.txt	
> out.txt
echo hi >
*/
*********************************************************

    /*  PRINT LE LEXER  */

Pour tester le rendu du lexer, voir visuellement le découpage:>
    - insérer la fonction suivante:

``` bash
void    print_lexer(lst_lexer *head)
{
    char *types[] = {"TOK_RED_BRS", "TOK_RED_BLS", "TOK_RED_BR",
                     "TOK_RED_BL", "TOK_PIPE", "TOK_PAR_L",
                     "TOK_PAR_R", "TOK_W", "TOK_EOF", NULL};
    while (head)
    {
        printf("type: %-15s | value: %s\n", types[head->type],
               head->value ? head->value : "NULL");
        head = head->next;
    }
}
```

    - utiliser un main de cet exemple:

``` bash 
int main(void)
{
    lexeur("echo hello | cat -n > file.txt");
}
```

Découpage, brainsto de la fonction cut:

``` bash
    // gerer les ' ' ', les  ' " '
    // attention, si obj bizarres (<> etc STOP)
    //quand ' ' ' jamais expansion MAIS si " expand, de meem pour $ 
    // attention aux quotes pas fermees PAS A GERER

    //➜  minishell git:(parcing) ✗ echo "$HOME"              
    // /home/laura
    //➜  minishell git:(parcing) ✗ echo '$HOME'
    // $HOME
    //-> bash-5.2$ echo $HOME
    // /home/lheteau
    
    // ➜  minishell git:(parcing) ✗ echo "hello"
    // hello
    // ➜  minishell git:(parcing) ✗ echo 'hello'
    // hello
    //➜  minishell git:(parcing) ✗ echo 'hello
    // quote> jfjh'
    // hello
    // jfjh
    // ➜  minishell git:(parcing) ✗ echo $VAR = "hey"
    // = hey
    // ➜  minishell git:(parcing) ✗ echo $VAR = 'hey'
    // = hey
    //➜  minishell git:(parcing) ✗ export VAR="hey"; echo VAR
    //VAR
    //➜  minishell git:(parcing) ✗ export VAR='hey'; echo VAR
    //VAR
```

*********************************************************

    /*  PRINT L'AST */

Pour voir le rendu de l'ast, inclure le main et le fichier ci-dessous:

``` bash
int main(void)
{
    lst_lexer *head = lexeur("echo hello | cat -n > file.txt");
	t_lst_ast	*ast = create_ast(&head);
	print_ast(ast);	
}
```

``` bash
#include "parceur.h"

static const char *node_type_str(node_type type)
{
    if (type == N_RED)  return "N_RED";
    if (type == N_PIPE) return "N_PIPE";
    if (type == N_PAR)  return "N_PAR";
    if (type == N_CMD)  return "N_CMD";
    return "TOK_EOF";
}

static void print_ast_rec(t_lst_ast *node, int depth, int is_right)
{
    int i;

    if (!node)
        return ;
    i = 0;
    while (i < depth - 1)
    {
        printf("│   ");
        i++;
    }
    if (depth > 0)
    {
        if (is_right)
            printf("├── ");
        else
            printf("└── ");
    }
    printf("[%s]", node_type_str(node->node_type));
    if (node->node_type == N_CMD && node->tokens)
    {
        int j = 0;
        printf(" |");
        while (node->tokens[j])
        {
            printf(" %s", node->tokens[j]);
            j++;
        }
        printf(" |");
    }
    if (node->red_file)
        printf(" -> \"%s\"", node->red_file);
    printf("\n");
    if (node->left || node->right)
    {
        print_ast_rec(node->right, depth + 1, 1);
        print_ast_rec(node->left,  depth + 1, 0);
    }
}

void    print_ast(t_lst_ast *root)
{
    if (!root)
    {
        printf("(empty AST)\n");
        return ;
    }
    printf("AST:\n");
    print_ast_rec(root, 0, 0);
}
```