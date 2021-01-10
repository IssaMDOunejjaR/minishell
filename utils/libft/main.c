/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:19:41 by iounejja          #+#    #+#             */
/*   Updated: 2019/11/06 13:23:36 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	del(void *a)
{
	*(char*)a = 0;	
}

char	f(unsigned int r,char c)
{
	r = 1;
	return (c + 1);
}

void	ft(void *str)
{
	int i;

	i = 0;
	while (*(char*)(str + i) != '\0')
	{
		*(char*)(str + i) += 1;
		i++;
	}
}

void	*ft_f(void *a)
{
	char *s = ft_strdup(a);
	*s = *s + 1;
	return ((void*)s);
}

int		main()
{
	//int fd = open("txt", O_WRONLY);
	
	//-- ft_stlen
	//printf("ft_strlen = %zu\n", ft_strlen(NULL));
	//printf("strlen = %zu\n", strlen(NULL));
	
	//-- ft_atoi
	//printf("ft_atoi = %d\natoi = %d\n", ft_atoi("-9999999999999999999999999"), atoi("1658"));
	
	//-- ft_isdigit
	//printf("ft_isdigit = %d\n", ft_isdigit(97));
	
	//-- ft_isalpha
	//printf("ft_isalpha = %d\n", ft_isalpha(NULL));
	//printf("isalpha = %d\n", isalpha(NULL));
	
	//-- ft_tolower
	//printf("ft_tolower = %d\n", ft_tolower(112));
	
	//-- ft_toupper
	//printf("ft_toupper = %d\n", ft_toupper(112));
	
	//-- ft_isprint
	//printf("ft_isprint = %d\n", ft_isprint(127));
	
	//-- ft_isalnum
	//printf("ft_isalnum = %d\n", ft_isalnum('0'));
	
	//-- ft_memset
	//char *s1 = NULL;
	//ft_memset(s1, '+', 20);
	//memset(s1, '+', 20);
	//printf("ft_memset = %s\n", s1);
	//printf("memset = %s\n", s1);
	
	//-- ft_strncmp
	//printf("ft_strncmp = %d\n", ft_strncmp("Healo", "Hello", 0));
	//printf("strncmp = %d\n", strncmp("Healo", "Hello", 0));
	
	//-- ft_strchr
	//printf("ft_strchr = %s\n", ft_strchr(NULL, 'z'));
	//printf("strchr = %s\n", strchr(NULL, 'z'));
	
	//-- ft_strrchr
	//printf("ft_strrchr = %s\n", ft_strrchr(NULL, 'z'));
	//printf("strrch = %s\n", strrchr(NULL, 'z'));
	
	//-- ft_isascii
	//printf("ft_isascii = %d\n", ft_isascii('a'));
	
	//-- ft_bzero
	//char *s1 = ft_strdup("Hello World!");
	//ft_bzero(s1, 0);
	//bzero(s1, 0);
	//printf("ft_bzero = %s\n", s1);
	//printf("bzero = %s\n", s1);
	
	//-- ft_memcpy
	//char *dest = ft_strdup("Hello");
	//char *src = NULL;
	//ft_memcpy(dest, src, 0);
	//memcpy(dest, src, 0);
	//printf("ft_memcpy = %s\n", dest);
	//printf("memcpy = %s\n", dest);
	
	//-- ft_memccpy
	//char *dest = ft_strdup("123456789");
	//char *src = ft_strdup("World!");
	//ft_memccpy(dest, src, 'e', 20);
	//memccpy(dest, src, 'e', 20);
	//printf("ft_memccpy = %s\n", dest);
	//printf("memccpy = %s\n", dest);
	
	//-- ft_memmove
	//char *dest = "NULL";
	//char *src = "NULL";
	//ft_memmove(dest, src, 1);
	//memmove("NULL", "NULL", 1);
	//printf("ft_memmove = %s\n", ft_memmove("NULL", "NULL", 1));
	//printf("ft_memmove = %s\n", memmove(dest, src, 1));
	
	//-- ft_strnstr
	//char *str = "Hi admin hello";
	//char *str1 = "hello";
	//printf("ft_strnstr = %s\n", ft_strnstr(str, str1, 100));
	//printf("strnstr = %s\n", strnstr(str, str1, 100));
	
	//-- ft_memchr
	//printf("ft_memchr = %s\n", ft_memchr(NULL, 'e', -20));
	//printf("memchr = %s\n", ft_memchr(NULL, 'e', -20));
	
	//-- ft_memcmp
	//char *s1 = NULL;
	///char *s2 = ft_strdup("Wordft");
	//printf("ft_memcmp = %d\n", ft_memcmp(s1, s2, 5));
	//printf("memcmp = %d\n", ft_memcmp(ft_strdup(""), s2, 5));
	
	//-- ft_strdup
	//printf("ft_strdup = %s\n", ft_strdup("Hello World!"));
	
	//-- ft_strlcpy
	//printf("ft_strlcpy = %lu\n", ft_strlcpy(NULL, "gyut", 5));
	//printf("strlcpy = %lu\n", strlcpy(NULL, "gyut", 5));
	
	//-- ft_calloc
	//printf("ft_calloc = %s\n", ptr);


	//-- ft_strlcat
	//printf("ft_strlcat = %zu\nstrlcat = %zu\n", ft_strlcat(NULL, ft_strdup("Hello"), 0), strlcat(NULL, ft_strdup("Hello"), 0));
	
	//-- ft_substr
	//printf("ft_substr = %s\n", ft_substr("Hello World!", 11, 1000));
	
	//-- ft_strjoin
	//printf("ft_strjoin = %s\n", ft_strjoin(s1, ""));
	
	//-- ft_strtrim
	printf("ft_strtrim = %s", ft_strtrim("wa b c \n \t\n abcHello World!cba \n\n\n\n\n\t      \t \t           \t\n aaaa bbbbbbbababbccccbcbcabw", "abc \n\t"));
	
	//-- ft_putchar_fd
	//ft_putchar_fd('n', fd);
	
	//-- ft_putstr_fd
	//ft_putstr_fd("Hello", fd);
	
	//-- ft_putendl_fd
	//ft_putendl_fd(s1, fd);
	
	//-- ft_putnbr_fd
	//ft_putnbr_fd(-20, fd);
	
	//-- ft_itoa
	//char *str = ft_itoa(22455455);
	//printf("ft_itoa = %s\n", str);
	//free(str);
	
	//-- ft_strmapi
	//printf("ft_strmapi = %s\n", ft_strmapi("abcd", f));
	
	//-- ft_split
	/*char **tab;
	tab = ft_split("  issam ounejjar                hello", ' ');
	while (*tab != NULL)
	{
		printf("%s\n", *tab);
		tab++;
	}*/

	//////////// BONUS ///////////////
	/*	
	int i;
	t_list *h;
	t_list *ls1;
	t_list *ls2;
	t_list *ls3;
	t_list *new;
	t_list *res;

	i = 1;
	//char *r = ft_strdup("ana");
	//char *y = ft_strdup("ana la3la");
	//new = ft_lstnew(r);
	//lst = ft_lstnew(y);
	
	char *l1 = ft_strdup("One");
	char *l2 = ft_strdup("Two");
	char *l3 = ft_strdup("Three");
	char *l4 = ft_strdup("Four");
	ls1 = ft_lstnew(l1);
	ls2 = ft_lstnew(l2);
	ls3 = ft_lstnew(l3);
	new = ft_lstnew(l4);
	h = ls1;
	ft_lstadd_back(&h, ls2);
	ft_lstadd_back(&h, ls3);
	ft_lstadd_back(&h, new);
	
	//ft_lstdelone(new, del);
	//ft_lstclear(&ls3, del);
	//free(r);
	//free(y);
	//free(l1);
	//free(l2);
	//free(l3);
	//free(l4);
	//printf("%s", new->content);
	//printf("list size = %d\n", ft_lstsize(h));
	//printf("the last ele is = %s\n", (char*)ft_lstlast(ls2)->content);
	//ft_lstiter(ls1, ft);*/
	/*res = ft_lstmap(ls1, ft_f, del);
	while (h)
	{
		printf("ft_lstmap = %s\n", h->content);
		h = h->next;
	}
	printf("########################################\n");
	while (res)
	{
		printf("ele list %d = %s\n", i, res->content);
		res = res->next;
		i++;
	}*/
}
