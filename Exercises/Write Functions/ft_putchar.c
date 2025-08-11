#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

// This function writes a single character to the standard output using the write system call.
// It takes a character 'c' as an argument and writes it to file descriptor 1, which corresponds to standard output (stdout).
// The function does not return any value.