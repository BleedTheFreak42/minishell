#include "minishell.h"

t_token *init_token(int type, char *value)
{
	t_token *token;

	token = MALLOC(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

t_tokenlst	*ft_lstnew(t_token *token)
{
	t_tokenlst	*newlst;

	newlst = (t_tokenlst *) malloc(sizeof(t_tokenlst));
	if (!newlst)
		return (0);
	newlst->next = 0;
	newlst->prev = 0;
	newlst->token = token;
	return (newlst);
}

t_tokenlst	*ft_lstlast(t_tokenlst *lst)
{
	t_tokenlst	*ptrlst;

	if (lst == NULL)
		return (lst);
	ptrlst = lst;
	while (ptrlst->next)
		ptrlst = ptrlst->next;
	return (ptrlst);
}

void	ft_lstadd_back(t_tokenlst **lst, t_tokenlst *new)
{
	t_tokenlst	*ptrlst;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ptrlst = ft_lstlast(*lst);
	ptrlst->next = new;
	new->prev = ptrlst;
}

void	ft_lstdelone(t_tokenlst *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->token);
		free(lst);
	}
}

void	ft_lstclear(t_tokenlst **lst, void (*del)(void*))
{
	t_tokenlst	*temp;

	if (lst && *lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
		}
		lst = NULL;
	}
}