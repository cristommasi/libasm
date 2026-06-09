#include <stdio.h>
char base_symbols[93] = {-1};

int		is_sign(char c) {

	return (c == '+' || c == '-');
}

int		is_whitespace(char c) {

	return (c == '\t' || c == '\r' || c == '\n' || c == ' ' || c == '\f' || c == '\v');
}


int		in_symbols(char c) {

	return (base_symbols[(unsigned char)c] != -1);
}

int		check_base(char *base) {

	int i = 0;
	printf("hello\n");
	while (base[i]) {

		if (is_sign(base[i])) {
			printf("is_sign = %c\n, ", base[i]);
			return (0);
		}
		if (is_whitespace(base[i])) {
			printf("is_whitespace = %c\n", base[i]);
			return (0);
		}
		if (in_symbols(base[i])) {
			printf("is_whitespace = %c\n", base[i]);
			return (0);
		}
		base_symbols[(unsigned char)base[i]] = i;
		i++;
	}
	return (i);
}


int		ft_atoi_base(char *str, char *base)
{
	
	int n_base = check_base(base);
	if (n_base <= 1)
		return (0);

	while (is_whitespace(*str))
		str++;

	int sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+') {
		sign = 1;
		str++;
	}

    int result = 0;
	while (*str != 0)
	{
		if (!in_symbols(*str))
			return (0);
		result = result * n_base + base_symbols[*str];
		str++;
	}
	return (result * sign);
}



int main(void) {



	printf("num = %d \n", ft_atoi_base("42", "0123456789"));

	
	
	
	
	return 0;
}