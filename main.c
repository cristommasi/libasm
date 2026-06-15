#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

// extern size_t	ft_strlen(char const *s);
// void	test_strlen(void) {

// 	const char *s1		= "hello world";
// 	const char s2[12]		= "hello world";
// 	const char *s3		= "";


// 	printf("------glibc strlen VS libasm ft_strlen-------\n\n");
// 	printf("const char *s1	= \"hello world\";\nconst char s2[12]	= \"hello world\";\nconst char *s3	= \"\";\n\n");
		
// 	printf("strlen(s1), ft_strlen(s1) = %zu, %zu\n", strlen(s1), ft_strlen(s1));
// 	printf("strlen(s2), ft_strlen(s2) = %zu, %zu\n", strlen(s2), ft_strlen(s2));
// 	printf("strlen(s3), ft_strlen(s3) = %zu, %zu\n", strlen(s3), ft_strlen(s3));

// 	printf("\n");
// }


// extern char *ft_strcpy(char *dest, const char *src);
// void    test_strcpy(void) {

//     char        dst1[64];
//     char        dst2[64];
//     const char  *src;

//     printf("------glibc strcpy VS libasm ft_strcpy-------\n\n");

//     src = "BBB";
//     memset(dst1, 0, 64); memset(dst2, 0, 64);
//     printf("strcpy(dst, BBB),      ft_strcpy(dst, BBB)        = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
//     src = "hello";
//     memset(dst1, 0, 64); memset(dst2, 0, 64);
//     printf("strcpy(dst, hello),    ft_strcpy(dst, hello)      = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
//     src = "";
//     memset(dst1, 0, 64); memset(dst2, 0, 64);
//     printf("strcpy(dst, \"\"),       ft_strcpy(dst, \"\")         = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
//     src = "A";
//     memset(dst1, 0, 64); memset(dst2, 0, 64);
//     printf("strcpy(dst, A),        ft_strcpy(dst, A)          = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
//     src = "test";
//     memset(dst1, 0, 64); memset(dst2, 0, 64);
//     printf("strcpy returns dst?    ft_strcpy returns dst?     = %d, %d\n", strcpy(dst1, src) == dst1, ft_strcpy(dst2, src) == dst2);
//     src = "12345";
//     memset(dst1, 0, 64); memset(dst2, 0, 64);
//     printf("strcpy(dst, 12345),    ft_strcpy(dst, 12345)      = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));
//     src = "hi there!";
//     memset(dst1, 0, 64); memset(dst2, 0, 64);
//     printf("strcpy(dst, hi there!), ft_strcpy(dst, hi there!) = %s, %s\n", strcpy(dst1, src), ft_strcpy(dst2, src));

//     printf("\n");
// }


// extern int ft_strcmp(const char *s1, const char *s2);
// void    test_strcmp(void) {

//     const char *a, *b;
//     printf("------glibc strcmp VS libasm ft_strcmp-------\n\n");

//     a = "AAA"; b = "AAA";
//     printf("strcmp(AAA, AAA),   ft_strcmp(AAA, AAA)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = ""; b = "";
//     printf("strcmp(\"\", \"\"),     ft_strcmp(\"\", \"\")     = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "AAA"; b = "AAB";
//     printf("strcmp(AAA, AAB),   ft_strcmp(AAA, AAB)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "AAA"; b = "BBB";
//     printf("strcmp(AAA, BBB),   ft_strcmp(AAA, BBB)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = ""; b = "AAA";
//     printf("strcmp(\"\", AAA),    ft_strcmp(\"\", AAA)    = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "a"; b = "b";
//     printf("strcmp(a, b),       ft_strcmp(a, b)       = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "abc"; b = "abd";
//     printf("strcmp(abc, abd),   ft_strcmp(abc, abd)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "AA"; b = "AAA";
//     printf("strcmp(AA, AAA),    ft_strcmp(AA, AAA)    = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "AAB"; b = "AAA";
//     printf("strcmp(AAB, AAA),   ft_strcmp(AAB, AAA)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "BBB"; b = "AAA";
//     printf("strcmp(BBB, AAA),   ft_strcmp(BBB, AAA)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "AAA"; b = "";
//     printf("strcmp(AAA, \"\"),    ft_strcmp(AAA, \"\")    = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "b"; b = "a";
//     printf("strcmp(b, a),       ft_strcmp(b, a)       = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "abd"; b = "abc";
//     printf("strcmp(abd, abc),   ft_strcmp(abd, abc)   = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "AAA"; b = "AA";
//     printf("strcmp(AAA, AA),    ft_strcmp(AAA, AA)    = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "A"; b = "a";
//     printf("strcmp(A, a),       ft_strcmp(A, a)       = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));
//     a = "a"; b = "A";
//     printf("strcmp(a, A),       ft_strcmp(a, A)       = %d, %d\n", strcmp(a, b), ft_strcmp(a, b));

// 	printf("\n");
// }


// extern ssize_t ft_write(int fd, const void *buf, size_t count);
// void    test_write(void) {


// 	printf("------glibc write VS libasm ft_write -------\n\n");
		
	
//     ssize_t glibc_res = write(1, "Hello World\n", 12);
//     ssize_t libasm_res = ft_write(1, "Hello World\n", 12);
//     printf("write(STDOUT), ft_write(STDOUT) = %zu, %zu\n", glibc_res, libasm_res);

// 	glibc_res = write(2, "Hello World\n", 12);
//     libasm_res = ft_write(2, "Hello World\n", 12);
//     printf("write(STDERR), ft_write(STDERR) = %zu, %zu\n", glibc_res, libasm_res);

//     glibc_res = write(55, "Hello World\n", 12);
//     libasm_res = ft_write(55, "Hello World\n", 12);
//     printf("write(FD=55), ft_write(FD=55)   = %ld, %ld\n", glibc_res, libasm_res);
// 	printf("\n");   
// }

// extern ssize_t ft_read(int fd, void *buf, size_t count);
// void    test_read(void)
// {
//     char    glibc_buf[64];
//     char    libasm_buf[64];
//     ssize_t glibc_res;
//     ssize_t libasm_res;
//     int     pipefd[2];

//     printf("------glibc read VS libasm ft_read -------\n\n");

//     pipe(pipefd);
//     write(pipefd[1], "Hello World", 11);
//     glibc_res = read(pipefd[0], glibc_buf, 11);
//     glibc_buf[glibc_res] = '\0';
//     close(pipefd[0]);
//     close(pipefd[1]);
//     pipe(pipefd);
//     write(pipefd[1], "Hello World", 11);
//     libasm_res = ft_read(pipefd[0], libasm_buf, 11);
//     libasm_buf[libasm_res] = '\0';
//     close(pipefd[0]);
//     close(pipefd[1]);


//     printf("read(pipe),  ft_read(pipe)  = (%ld - %s), (%ld - %s)\n", glibc_res, glibc_buf, libasm_res, libasm_buf);


//     errno = 0;
//     glibc_res = read(55, glibc_buf, 11);
//     int temp1 = errno;
//     errno = 0;
//     libasm_res = ft_read(55, libasm_buf, 11);
//     int temp2 = errno;

//     printf("read(FD=55), ft_read(FD=55) = (%ld - errno %d), (%ld - errno %d)\n", glibc_res, temp1, libasm_res, temp2);
//     printf("\n");
// }


// extern int ft_atoi_base(char *str, char *base);
// void	test_atoi_base(void)
// {
// 	char *base10 = "0123456789";
// 	char *base2 = "01";
// 	char *base8 = "01234567";
// 	char *base16 = "0123456789abcdef";
// 	char *base36 = "0123456789abcdefghijklmnopqrstuvwxyz";
//     char *base16_upper = "0123456789ABCDEF";

// 	char *num1 = "";
// 	char *num2 = "-2147483648";
// 	char *num3 = "   +42";
// 	char *num4 = "\t\n\v\f\r-42";
// 	char *num5 = "+--++42";
// 	char *num6 = "42abc";
// 	char *num7 = "101010";
// 	char *num8 = "2a";
// 	char *num9 = "7fffffff";
// 	char *num10 = "-80000000";


// 	printf("------ atoi & strtol VS ft_atoi_base -------\n\n");

// 	printf("empty string                     = %d, %d\n", atoi(num1), ft_atoi_base(num1, base10));
// 	printf("INT_MIN                          = %d, %d\n", atoi(num2), ft_atoi_base(num2, base10));
// 	printf("spaces + 42                      = %d, %d\n", atoi(num3), ft_atoi_base(num3, base10));
// 	printf("all whitespace + -42             = %d, %d\n", atoi(num4), ft_atoi_base(num4, base10));
// 	printf("invalid sign sequence            = %d, %d\n", atoi(num5), ft_atoi_base(num5, base10));
// 	printf("stop at letters                  = %d, %d\n", atoi(num6), ft_atoi_base(num6, base10));
// 	printf("binary 101010                    = %d, %d\n", (int)strtol(num7, NULL, 2), ft_atoi_base(num7, base2));
// 	printf("hex 2a                           = %d, %d\n", (int)strtol(num8, NULL, 16), ft_atoi_base(num8, base16));
// 	printf("hex max int (lowercase input)    = %d, %d\n", (int)strtol("7fffffff", NULL, 16), ft_atoi_base(num9, base16));
// 	printf("hex min int (negative style)     = %d, %d\n", (int)strtol("-80000000", NULL, 16), ft_atoi_base(num10, base16));
//     printf("octal 52                         = %d, %d\n", (int)strtol("52", NULL, 8), ft_atoi_base("52", base8));
//     printf("octal max int                    = %d, %d\n", (int)strtol("17777777777", NULL, 8), ft_atoi_base("17777777777", base8));
//     printf("octal zero                       = %d, %d\n", (int)strtol("0", NULL, 8), ft_atoi_base("0", base8));
//     printf("octal invalid stops at 8         = %d, %d\n", (int)strtol("12345877", NULL, 8), ft_atoi_base("12345877", base8));
//     printf("base36 16                        = %d, %d\n", (int)strtol("16", NULL, 36), ft_atoi_base("16", base36));
//     printf("base36 z                         = %d, %d\n", (int)strtol("z", NULL, 36), ft_atoi_base("z", base36));
//     printf("base36 10z                       = %d, %d\n", (int)strtol("10z", NULL, 36), ft_atoi_base("10z", base36));
//     printf("base36 big number                = %d, %d\n", (int)strtol("1z141z3", NULL, 36), ft_atoi_base("1z141z3", base36));
//     printf("null base                        = %d\n", ft_atoi_base("42", NULL));
//     printf("empty base                       = %d\n", ft_atoi_base("42", ""));
//     printf("single char base                 = %d\n", ft_atoi_base("42", "0"));
//     printf("duplicate in base                = %d\n", ft_atoi_base("42", "0012345678"));
//     printf("base contains +                  = %d\n", ft_atoi_base("42", "0123456789+"));
//     printf("base contains -                  = %d\n", ft_atoi_base("42", "0123456789-"));
//     printf("base contains space              = %d\n", ft_atoi_base("42", "0123456789 "));
//     printf("hex upper 2A                     = %d, %d\n", (int)strtol("2A", NULL, 16), ft_atoi_base("2A", base16_upper));
//     printf("overflow positive                = %d, %d\n", atoi("2147483648"),  ft_atoi_base("2147483648",  base10));
//     printf("overflow large                   = %d, %d\n", atoi("9999999999"),  ft_atoi_base("9999999999",  base10));
//     printf("underflow                        = %d, %d\n", atoi("-2147483649"), ft_atoi_base("-2147483649", base10));
//     printf("way overflow                     = %d, %d\n", atoi("99999999999999999999"), ft_atoi_base("99999999999999999999", base10));
//     printf("just plus                        = %d, %d\n", atoi("+"),           ft_atoi_base("+",           base10));
//     printf("just minus                       = %d, %d\n", atoi("-"),           ft_atoi_base("-",           base10));
//     printf("plus zero                        = %d, %d\n", atoi("+0"),          ft_atoi_base("+0",          base10));
//     printf("minus zero                       = %d, %d\n", atoi("-0"),          ft_atoi_base("-0",          base10));
//     printf("double minus                     = %d, %d\n", atoi("--42"),        ft_atoi_base("--42",        base10));
//     printf("only whitespace                  = %d, %d\n", atoi("     "),       ft_atoi_base("     ",       base10));
//     printf("whitespace after digits          = %d, %d\n", atoi("42   "),       ft_atoi_base("42   ",       base10)); // should stop at space
//     printf("whitespace between digits        = %d, %d\n", atoi("4 2"),         ft_atoi_base("4 2",         base10)); // should give 4
//     printf("all zeros                        = %d, %d\n", atoi("000000"),      ft_atoi_base("000000",      base10));
//     printf("leading zeros                    = %d, %d\n", atoi("007"),         ft_atoi_base("007",         base10));
//     printf("negative leading zeros           = %d, %d\n", atoi("-007"),        ft_atoi_base("-007",        base10));
//     printf("binary all ones 32bit            = %d, %d\n", (int)strtol("11111111111111111111111111111111", NULL, 2), ft_atoi_base("11111111111111111111111111111111", base2));
//     printf("binary invalid char              = %d, %d\n", (int)strtol("1012", NULL, 2), ft_atoi_base("1012", base2)); // stops at '2'
//     printf("no valid digits at all           = %d, %d\n", atoi("abc"),         ft_atoi_base("abc",         base10)); // should return 0
//     printf("sign then invalid                = %d, %d\n", atoi("+abc"),        ft_atoi_base("+abc",        base10)); // should return 0

// }

int	main(void)
{
    // test_strlen();
    // test_strcpy();
    // test_strcmp();
    // test_write();
    // test_read();
	// test_atoi_base();
    test_strdup();
	return (0);
}

