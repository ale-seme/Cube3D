/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 19:39:55 by asemerar      #+#    #+#                 */
/*   Updated: 2024/01/18 18:39:19 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_all(char **ss, size_t i)
{
	while (i > 0)
	{
		i--;
		free(ss[i]);
	}
	free(ss);
	return (NULL);
}

static size_t	ft_count_n_substrings(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
		{
			i++;
		}
	}
	return (count);
}

static char	*get_next_split(const char *s, size_t *start, char c)
{
	size_t	begin;
	size_t	end;
	char	*substring;

	begin = *start;
	end = *start;
	while (s[begin] == c)
		begin++;
	end = begin;
	while (s[end] && s[end] != c)
		end++;
	substring = ft_substr(s, begin, end - begin);
	if (!substring)
		return (NULL);
	*start = end;
	return (substring);
}

static char	**ft_split_shorter(char const *s, char c, size_t n_substrings)
{
	size_t	i;
	size_t	start;
	char	**ss;

	i = 0;
	start = 0;
	ss = (char **)malloc((n_substrings + 1) * sizeof(char *));
	if (!ss)
		return (NULL);
	while (s[start])
	{
		while (s[start] == c)
			start++;
		if (s[start] != '\0')
		{
			ss[i] = get_next_split(s, &start, c);
			if (!ss[i])
				return (ft_free_all(ss, i));
			i++;
		}
	}
	ss[i] = (NULL);
	return (ss);
}

char	**ft_split(char const *s, char c)
{
	size_t	n_substrings;

	if (!s)
		return (NULL);
	n_substrings = ft_count_n_substrings(s, c);
	if (n_substrings == 0)
		return (NULL);
	return (ft_split_shorter(s, c, n_substrings));
}

// int main(void) 
// {
// 	// const char s[] = "A1|B2|C3|D4|E5";
// 	// char **str = ft_split(s, '|');

// 	// const char s[] = "CCHELLO, thisCisChelloC";
// 	// char **str = ft_split(s, 'C');

// 	// const char s[] = "A1|B2|C3|D4|E5";
// 	// char **str = ft_split(s, '3');

// 	// const char s[] = "A1|B2|C3|D4|E5";
// 	// char **str = ft_split(s, ' ');

// 	// const char s[] = "A1|B2|C3|D4|E5";
// 	// char **str = ft_split(s, '\0');
// 	char **str = ft_split("",' ');
// 	if (str == NULL) 
// 	{
// 		printf("Memory allocation failed.\n");
// 		return 0;
// 	}
// 	size_t i = 0;
// 	while (str[i]) 
// 	{
// 		printf("%s\n", str[i]);
// 		i++;
// 	}
// 	i = 0;
// 	return 0;
// }