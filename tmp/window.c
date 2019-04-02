#include <sys/ioctl.h>
#include <stdio.h>

int main()
{
	struct winsize w;
	size_t len = 11;
	ioctl(0, TIOCGWINSZ, &w);
	printf("rows %d\n", w.ws_row);
	printf("cols %d\n", w.ws_col);
	size_t	row = w.ws_row;
	size_t	col = w.ws_col;
	if (row <= col)
	{
		printf("cols = %lu\n", col / row);
	}
	else
	{
		printf("rows =  %lu\n", row / col);
	}
	return (0);
}
