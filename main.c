#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

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


extern ssize_t ft_write(int fd, const void *buf, size_t count);
void    test_write(void) {


	printf("------glibc write VS libasm ft_write -------\n\n");
		
	
    ssize_t glibc_res = write(1, "Hello World\n", 12);
    ssize_t libasm_res = ft_write(1, "Hello World\n", 12);
    printf("write(STDOUT), ft_write(STDOUT) = %zu, %zu\n", glibc_res, libasm_res);

	glibc_res = write(2, "Hello World\n", 12);
    libasm_res = ft_write(2, "Hello World\n", 12);
    printf("write(STDERR), ft_write(STDERR) = %zu, %zu\n", glibc_res, libasm_res);

    glibc_res = write(55, "Hello World\n", 12);
    libasm_res = ft_write(55, "Hello World\n", 12);
    printf("write(FD=55), ft_write(FD=55)   = %ld, %ld\n", glibc_res, libasm_res);

	printf("\n");   
}

extern ssize_t ft_read(int fd, void *buf, size_t count);
void    test_read(void)
{
    char    glibc_buf[64];
    char    libasm_buf[64];
    ssize_t glibc_res;
    ssize_t libasm_res;
    int     pipefd[2];

    printf("------glibc read VS libasm ft_read -------\n\n");

    pipe(pipefd);
    write(pipefd[1], "Hello World", 11);
    glibc_res = read(pipefd[0], glibc_buf, 11);
    glibc_buf[glibc_res] = '\0';
    close(pipefd[0]);
    close(pipefd[1]);
    pipe(pipefd);
    write(pipefd[1], "Hello World", 11);
    libasm_res = ft_read(pipefd[0], libasm_buf, 11);
    libasm_buf[libasm_res] = '\0';
    close(pipefd[0]);
    close(pipefd[1]);

    printf("read(pipe),  ft_read(pipe)  = (%ld - %s), (%ld - %s)\n", glibc_res, glibc_buf, libasm_res, libasm_buf);


    errno = 0;
    glibc_res = read(55, glibc_buf, 11);
    int temp1 = errno;
    errno = 0;
    libasm_res = ft_read(55, libasm_buf, 11);
    int temp2 = errno;

    printf("read(FD=55), ft_read(FD=55) = (%ld - errno %d), (%ld - errno %d)\n", glibc_res, temp1, libasm_res, temp2);
    printf("\n");
}

int		main(void) {

	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
    test_read();
    
	return (0);
}

