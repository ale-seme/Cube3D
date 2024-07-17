/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:25:02 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 18:11:01 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static size_t	ft_get_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	i = s1_len;
	while (i > 0 && ft_strchr(set, s1[i - 1]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*p1;

	if (!s1 || !set)
		return (NULL);
	start = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	if (start >= end)
	{
		p1 = (char *)malloc(1);
		if (!p1)
			return (NULL);
		p1[0] = '\0';
		return (p1);
	}
	p1 = (char *)malloc(end - start + 1);
	if (!p1)
		return (NULL);
	ft_strlcpy(p1, s1 + start, end - start + 1);
	return (p1);
}

// int main(void)
// {
// 	char const  s1[] = "---Hello World I see if you have some characters---  ";
// 	char const  set[] = "   Holle lodrW";
// 	char const  s1[] = "12232TakeOut the numberssss12212";
// 	char const  set[] = "321";
// 	char const  s1[] = "heywhat'sapp , do u wanna some carrots";
// 	char const  set[] = "yehstrroca;
// 	char const  s1[] = " ";
// 	char const  set[] = " ";
// 	char *p1 = ft_strtrim(s1, set); 
// 	printf("%s\n", p1);
// 	return (0);
// }