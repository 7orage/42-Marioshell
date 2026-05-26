#include "parceur.h"

/*
// FREE THE LIST
void	lst_free(t_data *img)
{
	t_col	*tmp;

	while (img->map.collectibles)
	{
		tmp = img->map.collectibles->next;
		free(img->map.collectibles);
		img->map.collectibles = tmp;
	}
}

// REMOVE A COLLECTIBLE FROM THE LISTE, SET AS "NON ACCESSIBLE"
void	lst_remove_col(t_col **liste, int x, int y)
{
	t_col	*ptr;
	t_col	*tmp;

	if (!liste || !*liste)
		return ;
	ptr = *liste;
	if (ptr->x == x && ptr->y == y)
	{
		if (ptr->next != NULL)
			*liste = ptr->next;
		else
			*liste = NULL;
		return (free(ptr));
	}
	while (ptr->next != NULL)
	{
		if (ptr->next->x == x && ptr->next->y == y)
		{
			tmp = ptr->next;
			ptr->next = tmp->next;
			free(tmp);
			return ;
		}
		ptr = ptr->next;
	}
}

// CHECK IF THE COLLECTIBLE IS ALREADY WON
int	lst_verif_col(t_col **liste, int x, int y)
{
	t_col	*ptr;

	if (!*liste)
		return (0);
	ptr = *liste;
	while (ptr->next != NULL)
	{
		if (ptr->x == x && ptr->y == y)
			return (1);
		ptr = ptr->next;
	}
	if (ptr->x == x && ptr->y == y)
		return (1);
	return (0);
}
*/
// CUT THE TOKEN PROPERLY
static char    *cut(char *raw_tok)
{
    int i = 0;
    int j = 0;
    char    *token;

    while (isspace(raw_tok[i]) == 0 || raw_tok[i] == '"' || raw_tok[i] == '\'')
        i++;
    while (!(isspace(raw_tok[i]) == 0 || raw_tok[i] == '"' || raw_tok[i] == '\''))
    {
        token[j] = raw_tok[i];
        i++;
        j++;
    }
    return(token);
}

// ADD A NEW TOKEN TO THE LISTE
int	add_node_parceur(token_type type, char *token, parceur **liste)
{
	parceur	*new;
	parceur	*ptr;

	new = malloc(sizeof(parceur));
	if (!new)
		return ;
	new->type = type;
	new->value = cut(token);
	new->next = NULL;
	if (!*liste)
		*liste = new;
	else
	{
		ptr = *liste;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
    return (ft_strlen(new->value));
}
/*
// INIT THE COLLECTIBLE LISTE
void	lst_get_list_col(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->raw_map[y])
	{
		x = 0;
		while (map->raw_map[y][x])
		{
			if (map->raw_map[y][x] == 'C')
				lst_create_new_col(x, y, &(map->collectibles));
			x++;
		}
		y++;
	}*/