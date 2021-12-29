#include<stdio.h>
#include<stdlib.h>
#include"char_operations.h"

int main()
{
	char(*funcs[4])(char) = { lower_to_upper, upper_to_lower, space_to_dash, reverse_letter };
	char* input, *res;
	if (!(input = malloc(1010 * sizeof(char))))
	{
		printf("Failed to allocate memory");
		return 2;
	}
	printf("Wbijaj teksta ziomus: ");
	fgets(input, 1010, stdin);
	
	int choice;
	printf("Wbijaj operacje ziomus: ");
	scanf("%d", &choice);
	
	switch (choice)
	{
	case 0:
		res = letter_modifier(input, (*(funcs)));
		if (!res)
		{
			printf("Failed to allocate memory");
			free(input);
			return 2;
		}
		break;
	case 1:
		res = letter_modifier(input, (*(funcs + 1)));
		if (!res)
		{
			printf("Failed to allocate memory");
			free(input);
			return 2;
		}
		break;
	case 2:
		res = letter_modifier(input, (*(funcs + 2)));
		if (!res)
		{
			printf("Failed to allocate memory");
			free(input);
			return 2;
		}
		break;
	case 3:
		res = letter_modifier(input, (*(funcs + 3)));
		if (!res)
		{
			printf("Failed to allocate memory");
			free(input);
			return 2;
		}
		break;
	default:
		printf("Incorrect input");
		free(input);
		return 1;
	}

	printf("%s", res);
	free(input);
	free(res);
	return 0;
}