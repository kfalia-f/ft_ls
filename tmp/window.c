#include <sys/ioctl.h>
#include <stdio.h>

int main()
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	printf("%d\n", w.ws_row);
	printf("%d\n", w.ws_col);
	return (0);
}
