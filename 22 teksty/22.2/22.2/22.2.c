#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ASCIIZ_length(const char* txt)
{
	int i = 0, size = 0;
	if (txt == NULL)
		return -1;
	if (*txt == '\n')
		return 1;
	else
	{
		while (*(txt + i) != 0)
		{					
				size++;
				i++;			
		}
		
	}
	return size;	
}

int main()
{
	char txt[1010]; int size;
	printf("Podaj tekst, ladnie prosze :)\n");
	fgets(txt, 1010, stdin);
	if (*(txt + strlen(txt) - 1) == '\n')
		*(txt + strlen(txt) - 1) = 0;
	size = ASCIIZ_length(txt);
	printf("Size: %d\n", size);
	return 0;
}