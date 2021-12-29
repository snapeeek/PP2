#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	const char* t1 = "Ala Ma Kota a kot Ma AlE";
	int size = strlen(t1);
	int i = size - 1;
	char *p;
	p = (char*)t1;

	while ((p + i) != p-1)
	{
		printf("%c", *(p + i));
		i--;
	}
	
	return 0;
}