#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int change_letter_size(const char* src, char* dest)
{
	int i = 0;
	if ((src == NULL) || (dest == NULL))
		return 0;

	while (*(src + i) != '\0')
	{
		if ((*(src + i) >= 65) && (*(src + i) <= 90))
			*(dest + i) = *(src + i) + 32;
		else if ((*(src + i) >= 97) && (*(src + i) <= 122))
			*(dest + i) = *(src + i) - 32;
		else
			*(dest + i) = *(src + i);
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
	char txt1[1010], txt2[1010], *p;
	printf("Podaj tekst: ");
	fgets(txt1, 1010, stdin);
	change_letter_size(txt1, txt2);
	p = trimwhitespace(txt2);
	printf("%s", p);


	return 0;
}