#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int validate(const char * number)
{
	if (number == NULL)
		return -1;
	int i = 0;
	
	while (*(number + i) != 0)
	{
		if ((*(number + i) < 48) || (*(number + i) > 57))
		{
			return 0;
		}
		i++;
	}

	return 1;
}

int add(const char* number1, const char* number2, char* result, int size)
{
	if ((number1 == NULL) || (number2 == NULL) || (result == NULL))
		return 0;

	if (strlen(number1) > strlen(number2))
	{
		int tab2[200], res[201] = { 0 };
		for (int i = 0; i <= (int)strlen(number1); i++)
		{
			if (i == (int)strlen(number1))
				*(res + i + 1) = '\0';
			else
				*(res + i + 1) = *(number1 + i) - 48;
			
		}

		for (int i = 0; i <= (int)strlen(number2); i++)
		{
			if (i == (int)strlen(number2))
				*(tab2 + i + 1) = '\0';
			else
				*(tab2 + i + 1) = *(number1 + i) - 48;
		}
	
		for (int i = 0; i < (int)strlen(number2); i++)
		{
		*(res + strlen(number1) - i) = *(tab2 + strlen(number2) - 1 - i) + *(res + strlen(number1) - i);
		}
		
		int temp = 0;
		while (*(res + temp) != '\0')
		{
			printf("%d", *(res+temp));
			temp++;
		}
	}






	return 1;
}

int main()
{
	char num1[200], num2[200], res[201]; int sizeres;
	printf("Podaj pierwsza liczbe: ");
	fgets(num1, 200, stdin); 
	
	if ((*(num1 + strlen(num1) - 1) == '\n') && (strlen(num1) > 1)) //usuwanie zbednego entera z konca
	{
		*(num1 + strlen(num1) - 1) = '\0';
	} 

	if ((validate(num1) == -1) || (validate(num1) == 0))
	{
		printf("Error");
		return 1;
	}

	printf("Podaj druga liczbe: ");
	fgets(num2, 200, stdin);
	
	if ((*(num2 + strlen(num2) - 1) == '\n') && (strlen(num2) > 1)) //usuwanie zbednego entera z konca vol2
	{
		*(num2 + strlen(num2) - 1) = '\0';
	}

	if ((validate(num2) == -1) || (validate(num2) == 0))
	{
		printf("Error");
		return 1;
	}

	if (strlen(num1) > strlen(num2))
	{
		sizeres = strlen(num1) + 1;
		*(res + sizeres) = 0;
	}
	else
	{
		sizeres = strlen(num2) + 1;
		*(res + sizeres) = 0;
	}


	add(num1, num2, res, sizeres);
	//printf("%s", res);




	return 0;
}
