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

t_token *init_token(int type, char *value);

#endif

// cat hello bleed | hdhdh
