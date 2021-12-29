#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int space_changer(char* t)
{
	int i = 0;
	if (t == NULL)
		return 0;
	
	while (*(t + i) != '\0')
	{
		if (*(t + i) == ' ')
			*(t + i) = '_';

		i++;
	}
	return 1;
}

char *trimwhitespace(char *str)
{
	char *end;


	while (((*(str) >= 9) && (*(str) <= 13)) || (*(str) == 32)) str++;

	if (*str == 0)
		return str;


	end = str + strlen(str) - 1;
	while (end > str && (((*(end) >= 9) && (*(end) <= 13)) || (*(end) == 32))) end--;


	*(end + 1) = 0;

	return str;
}


int main()
{
	char txt[1010], *t;
	printf("Wpisuj tekst: ");
	fgets(txt, 1010, stdin);
	t = trimwhitespace(txt);
	space_changer(t);
	
	printf("%s", t);
	
	
	return 0;
}