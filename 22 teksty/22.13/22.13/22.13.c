#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int starts_with(const char* txt, const char* find)
{
	if ((txt == NULL) || (find == NULL))
		return -1;

	if (strstr(txt, find) == txt)
		return 1;
	

	else
		return 0;
}

int ends_with(const char* txt, const char* find)
{
	if ((txt == NULL) || (find == NULL))
	{
		return -1;
	}
	if (strstr(txt, find) == ((txt + strlen(txt) - 1) - strlen(find) + 1))
		return 1;
	else if ((strstr(txt, find) != 0) && (strstr(txt, find) != ((txt + strlen(txt) - 1) - strlen(find) + 1)))
	{
		txt = strstr(txt, find) + strlen(find) - 1;
		ends_with(txt, find);

	}
	else if (strstr(txt, find) == 0)
		return 0;
	
	
	return 1;
}


int main()
{
	char txt[1010], find[1010];
	printf("Podaj pierwszy tekst: ");
	fgets(txt, 1010, stdin);
	printf("Podaj drugi tekst: ");
	fgets(find, 1010, stdin);
	
	if ((*(txt + strlen(txt) - 1) == '\n') && (strlen(txt) > 1))
	{
		*(txt + strlen(txt) - 1) = '\0';
	}

	if ((*(find + strlen(find) - 1) == '\n') && (strlen(find) > 1))
	{
		*(find + strlen(find) - 1) = '\0';
	}

	printf("%d %d", starts_with(txt, find), ends_with(txt, find));
	


	return 0;
}