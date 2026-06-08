/* A REPASSER AVANT FINAL
-norminette
-refaire makefile
-is_venv ne doit pas commencer par un chiffre
*/

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