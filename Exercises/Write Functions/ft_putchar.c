#include <unistd.h>

// Writes a single character to standard output
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

// Writes the string "Ergis Hasani" to standard output
void	ft_putstr(void)
{
	write(1, "Ergis Hasani", 12);
}

// Writes the string "Error\n" to standard error
void	error(void)
{
	write(2, "Error\n", 6);
}

int	main(void)
{
	// Test ft_putchar
	ft_putchar('A');
	write(1, "\n", 1); // Newline
	// Test ft_putstr
	ft_putstr();
	write(1, "\n", 1); // Newline
	// Test error
	error();
	return (0);
}
