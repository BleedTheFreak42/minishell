#include "minishell.h"

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);	
}

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

int	ft_isalnum(int c)
{
	return (((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')) || (c >= '0' && c <= '9'));
}

char* ft_strcat(char* destination, const char* source)
{
    // make `ptr` point to the end of the destination string
    char* ptr = destination + ft_strlen(destination);
 
    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // the destination is returned by standard `strcat()`
    return destination;
}

void	*ft_memcpy(void *dst, const void * src, size_t n)
{
	const unsigned char	*ptrsrc;
	unsigned char		*ptrdest;
	size_t				i;

	if (!dst && !src)
		return (0);
	ptrsrc = src;
	ptrdest = dst;
	if (!(*ptrdest) && !(*ptrsrc))
		return ("");
	i = 0;
	while (i < n)
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
	return (dst);
}

void *ft_realloc(void *ptr,size_t size)
{
	void *result;
	
	result = malloc(size);
	if (!result)
		return (NULL);
	ft_memcpy(result,ptr,sizeof(char) * ft_strlen((char *) ptr));
	free(ptr);
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substring;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else if (len >= ft_strlen(s) - start)
		substring = (char *) malloc(sizeof(char) * ft_strlen(s) - start);
	else
		substring = (char *) malloc(sizeof(char) * len + 1);
	if (!substring)
		return (0);
	i = 0;
	while (s[i] && i < len && start < ft_strlen(s))
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = 0;
	return (substring);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*ret;

	len = 0;
	while (s1[len])
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret)
	{
		i = 0;
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	if (dstsize == 0)
		return (len);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		i;

	i = 0;
	if (!(s1) || !(s2))
		return (NULL);
	if (*s1 == '\0' && *s2 == '\0')
		return (ft_strdup("\0"));
	string = (char *)
		malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) - 1));
	if (string)
	{
		while (*s1)
			string[i++] = *(s1++);
		while (*s2)
			string[i++] = *(s2++);
		string[i] = '\0';
	}
	return (string);
}

char	*ft_strchrq(const char *s, int c)
{
	int i;

	if(s)
	{
		i = 0;
		while (*s)
		{
			if (*s == 39 && !i)
				i = 1;
			else if (*s == 39 && i)
				i = 0;
			if (*s == (char)c && !i)
				return ((char *) s);
			s++;
		}
	}
	if (c == '\0')
		return ((char *) s);
	return (0);
}