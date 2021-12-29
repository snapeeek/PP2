#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"big_numbers.h"

int main()
{
	struct big_numbers_t *bn;
	int back;
	char *num, cleansing, zn;
	
	if ((back = create_big_numbers(&bn, 10)) != 0)
	{
		printf("Failed to allocate memory");	
		return 1;
	}
	
	if (!(num = malloc(201)))
	{
		printf("Failed to allocate memory");
		destroy_big_numbers(&bn);
		return 1;
	}

	printf("Podaj duze liczby:\n");
	do
	{
		
		for (int i = 0; i < 200; i++)
		{
			scanf("%c", &zn);
			*(num + i) = zn;
			if (zn == '\n')
			{
				*(num + i) = '\0';
				break;
			}
		}
		if (*num != '\n'&&*num != '\0')
		{
			
			back = validate(num);
			if (back != 0)
			{
				printf("Incorrect input\n");
			}
			if (back == 0)
			{

				back = add_big_number(bn, num);
				
				if (back != 0)
				{
					if (back == 1)
					{
						printf("Incorrect input\n");
					}
					if (back == 2)
					{
						printf("Failed to allocate memory\n");
						break;
					}
					if (back == 3)
					{
						printf("Buffer is full\n");
						break;
					}
				}
			}
		}
		

		if (200 < strlen(num))
		{
			while ((cleansing = getchar()) != '\n' && cleansing != EOF);
		}
	} while (*num != '\0' && *num != '\n');

	display(bn);
	if (bn->size == 0)
	{
		printf("Buffer is empty\n");
	}
	destroy_big_numbers(&bn);
	free(num);
	return 0;
}