#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


extern size_t	ft_strlen(char const *s);
void	test_strlen(void) {

	const char *s1		= "hello world";
	const char s2[12]		= "hello world";
	const char *s3		= "";


	printf("------glibc strlen VS libasm ft_strlen-------\n\n");
	printf("const char *s1	= \"hello world\";\nconst char s2[12]	= \"hello world\";\nconst char *s3	= \"\";\n\n");
		
	printf("strlen(s1), ft_strlen(s1) = %zu, %zu\n", strlen(s1), ft_strlen(s1));
	printf("strlen(s2), ft_strlen(s2) = %zu, %zu\n", strlen(s2), ft_strlen(s2));
	printf("strlen(s3), ft_strlen(s3) = %zu, %zu\n", strlen(s3), ft_strlen(s3));

	printf("\n");
}


extern char *ft_strcpy(char *dest, const char *src);
void    test_strcpy(void) {

    char        dst1[64];
    char        dst2[64];
    const char  *src;

    printf("------glibc strcpy VS libasm ft_strcpy-------\n\n");

    src = "BBB";
    memset(dst1, 0, 64); memset(dst2, 0, 64);
    printf("strcpy(dst, BBB),      ft_strcpy(dst, BBB)        = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
    src = "hello";
    memset(dst1, 0, 64); memset(dst2, 0, 64);
    printf("strcpy(dst, hello),    ft_strcpy(dst, hello)      = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
    src = "";
    memset(dst1, 0, 64); memset(dst2, 0, 64);
    printf("strcpy(dst, \"\"),       ft_strcpy(dst, \"\")         = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
    src = "A";
    memset(dst1, 0, 64); memset(dst2, 0, 64);
    printf("strcpy(dst, A),        ft_strcpy(dst, A)          = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
    src = "test";
    memset(dst1, 0, 64); memset(dst2, 0, 64);
    printf("strcpy returns dst?    ft_strcpy returns dst?     = %d, %d\n", strcpy(dst1, src) == dst1, ft_strcpy(dst2, src) == dst2);
    src = "12345";
    memset(dst1, 0, 64); memset(dst2, 0, 64);
    printf("strcpy(dst, 12345),    ft_strcpy(dst, 12345)      = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
    src = "hi there!";
    memset(dst1, 0, 64); memset(dst2, 0, 64);
    printf("strcpy(dst, hi there!), ft_strcpy(dst, hi there!) = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));

    printf("\n");
}


extern int ft_strcmp(const char *s1, const char *s2);
void    test_strcmp(void) {

    const char *a, *b;
    printf("------glibc strcmp VS libasm ft_strcmp-------\n\n");

    a = "AAA"; b = "AAA";
    printf("strcmp(AAA, AAA),   ft_strcmp(AAA, AAA)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = ""; b = "";
    printf("strcmp(\"\", \"\"),     ft_strcmp(\"\", \"\")     = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "AAA"; b = "AAB";
    printf("strcmp(AAA, AAB),   ft_strcmp(AAA, AAB)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "AAA"; b = "BBB";
    printf("strcmp(AAA, BBB),   ft_strcmp(AAA, BBB)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = ""; b = "AAA";
    printf("strcmp(\"\", AAA),    ft_strcmp(\"\", AAA)    = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "a"; b = "b";
    printf("strcmp(a, b),       ft_strcmp(a, b)       = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "abc"; b = "abd";
    printf("strcmp(abc, abd),   ft_strcmp(abc, abd)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "AA"; b = "AAA";
    printf("strcmp(AA, AAA),    ft_strcmp(AA, AAA)    = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "AAB"; b = "AAA";
    printf("strcmp(AAB, AAA),   ft_strcmp(AAB, AAA)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "BBB"; b = "AAA";
    printf("strcmp(BBB, AAA),   ft_strcmp(BBB, AAA)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "AAA"; b = "";
    printf("strcmp(AAA, \"\"),    ft_strcmp(AAA, \"\")    = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "b"; b = "a";
    printf("strcmp(b, a),       ft_strcmp(b, a)       = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "abd"; b = "abc";
    printf("strcmp(abd, abc),   ft_strcmp(abd, abc)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "AAA"; b = "AA";
    printf("strcmp(AAA, AA),    ft_strcmp(AAA, AA)    = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "A"; b = "a";
    printf("strcmp(A, a),       ft_strcmp(A, a)       = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
    a = "a"; b = "A";
    printf("strcmp(a, A),       ft_strcmp(a, A)       = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));

	printf("\n");
}

int		main(void) {

	test_strlen();
	test_strcpy();
	test_strcmp();
	

	return (0);
}

