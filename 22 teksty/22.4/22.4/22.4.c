#include<stdio.h>
#include<string.h>

int main()
{
	const char* tekst = "Ala ma kota";
	char *p;
	int i = 0;
	p = (char*)tekst;
	
	while (*(p + i) != ' ')
	{
		printf("%c", *(p + i));
		i++;
	}

	return 0;
}