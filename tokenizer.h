#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct s_token
{
	enum
	{
		TOKEN_PIPE,
		TOKEN_GTEHN,
		TOKEN_LTEHN,
		TOKEN_LHEREDOC,
		TOKEN_RHEREDOC,
		TOKEN_WORD
	}e_type;
	char *value;
}t_token;

typedef struct s_tokenlst
{
	t_token *token;
	struct s_tokenlst *next;
	struct s_tokenlst *prev;

}t_tokenlst;

t_token *init_token(int type, char *value);
t_tokenlst	*ft_lstnew(t_token *token);
t_tokenlst	*ft_lstlast(t_tokenlst *lst);
void	ft_lstadd_back(t_tokenlst **lst, t_tokenlst *new);
void	ft_lstdelone(t_tokenlst *lst, void (*del)(void*));
void	ft_lstclear(t_tokenlst **lst, void (*del)(void*));

#endif

// cat hello bleed | hdhdh
