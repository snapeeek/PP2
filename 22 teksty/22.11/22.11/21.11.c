#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int change_letter_size(char* txt, char c)
{
	if (txt == NULL) 
		return 0;

	int i = 0;

	if ((c == 'B') || (c == 'b'))
	{
		while (*(txt + i) != '\0')
		{
			if ((*(txt + i) >= 97) && (*(txt + i) <= 122))
			{
				*(txt + i) = *(txt + i) - 32;
			}
			i++;
		}
	}

	if ((c == 'S') || (c == 's'))
	{
		while (*(txt + i) != '\0')
		{
			if ((*(txt + i) >= 65) && (*(txt + i) <= 90))
			{
				*(txt + i) = *(txt + i) + 32;
			}
			i++;
		}
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
	char txt[1010], literka[2], *p;
	printf("Podaj tekst: ");
	fgets(txt, 1010, stdin);
	
	printf("Podaj literke: ");
	for (int i = 0;;i++)
	{
		
		fgets(literka, 2, stdin);
		if ((literka[0] != 'b') && (literka[0] != 'B') && (literka[0] != 's') && (literka[0] != 'S'))
		{
			printf("Incorrect data\n");
			continue;
		}
		else
			break;

		
	}
	
	p = trimwhitespace(txt);
	change_letter_size(p, literka[0]);
	
	int j = 0;
	while (*(txt + j) != '\0')
	{
		printf("%c", *(txt + j));
		j++;
	}

	return 0;
}