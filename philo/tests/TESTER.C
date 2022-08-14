#include <stdio.h>
#include <unistd.h>
#include <string.h>

void hello_word();

int main()
{
	static int a = 2;
	if (a == 2)
	{
		a = 3;
		hello_word();
	}
	printf("non you are not\n");
	return (0);
}

void	hello_word()
{
	printf("hello word\n ");
	main();
	printf("you are crazy\n");
}

