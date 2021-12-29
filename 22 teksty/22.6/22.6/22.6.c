#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int my_strlen(const char* str)
{
	if (str == NULL)
		return -1;
	
	int size = 0, i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) != '\n')
			size++;
		i++;
	}
	return size;
}

char* my_strcpy(char* dest, const char* src)
{





	return dest;
}




int main()
{
	char txt1[1010], txt2[1010], *ptxt1, *ptxt2;
	int size;

	printf("Podaj napis 1 (do 1010 znakow):\t");
	fgets(txt1, 1010, stdin);
	printf("Podaj napis 2 (do 1010 znakow):\t");
	fgets(txt2, 1010, stdin);

	printf("nap1: %d\t nap2: %d\n", my_strlen(txt1), my_strlen(txt2));




	return 0;
}