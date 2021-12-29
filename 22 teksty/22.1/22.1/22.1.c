#include<stdio.h>

int main()
{
	int i = 0;
	const char* t1 = "Ala Ma Kota a kot Ma AlE";
	while (*(t1 + i) != '\0')
	{
		putchar(*(t1 + i));
		i++;
	}


	return 0;
}