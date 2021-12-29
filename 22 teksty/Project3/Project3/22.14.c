#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define tabsize 201

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
	if ((number1 == NULL) || (number2 == NULL) || (result == NULL) || (size <= 0))
		return 0;
	int k, l; 
	for (k = 0; *(number1 + k) != '\0'; k++)
	{
		if (*(number1 + k) < 48 || *(number1 + k) > 57)
			return 0;
	}
	for (l = 0; *(number2 + l) != '\0'; l++)
	{
		if (*(number2 + l) < 48 || *(number2 + l) > 57)
			return 0;
	}
	k--, l--;
	
	int count_res = 0,
	helper = 0,
	temp_one = 0;
	
	for (; k >= 0 && l >= 0 && count_res<size; k--, l--, count_res++)
	{
		if (count_res >= size)
		{
			return 0;
		}
		helper = *(number1 + k) + *(number2 + l) - 48;
		if (temp_one == 1)
		{
			helper += 1;
			temp_one = 0;
		}
		if (helper > 57)
		{
			temp_one = 1;
			helper -= 10;
		}
		*(result + count_res) = (char)helper;
	}
	if (l != 0)
	{
		for (; l >= 0 && count_res <size ; l--, count_res++)
		{
			if (count_res >= size)
			{
				return 0;
			}
			helper = *(number2 + l);
			if (temp_one == 1)
			{
				helper += 1;
				temp_one = 0;
			}
			if (helper > 57)
			{
				temp_one = 1;
				helper -= 10;
			}
			*(result + count_res) = (char)helper;
		}
		if (count_res >= size)
		{
			return 0;
		}
	}
	if (k != 0)
	{
		for (; k >= 0 && count_res < size; k--, count_res++)
		{
			if (count_res >= size)
			{
				return 0;
			}
			helper = *(number1 + k);
			if (temp_one == 1)
			{
				helper += 1;
				temp_one = 0;
			}
			if (helper > 57)
			{
				temp_one = 1;
				helper -= 10;
			}
			*(result + count_res) = (char)helper;
		}
		if (count_res >= size)
		{
			return 0;
		}

	}
	if ((temp_one == 1) && (l == -1) && (k == -1))
	{
		*(result + count_res++) = 49;
	}
	if (count_res >= size)
	{
		return 0;
	}
	
	//odrwacanie tablicy
	*(result + count_res--) = '\0';
	int m;
	char temp;
	for (m = 0; m <= count_res; m++, count_res--)
	{
		temp = *(result + count_res);
		*(result + count_res) = *(result + m);
		*(result + m) = temp;
	}
	return 1;
}



int main()
{
	
	char num1[tabsize], num2[tabsize], wynik[3 * tabsize];
	char input;
	int counter1 = 0, counter2 = 0;
	
	printf("Podaj num1: ");
	do
	{
		scanf("%c", &input);
		if (input != '\n')
			*(num1 + counter1++) = input;


	} while (counter1 < tabsize - 1 && input != '\n');
	
	if (counter1 == tabsize - 1)
		getchar();
	*(num1 + counter1) = '\0';
	
	printf("Podaj num2: ");	
	do
	{
		scanf("%c", &input);
		if (input != '\n')
			*(num2 + counter2++) = input;

	} while (counter2 < tabsize - 1 && input != '\n');
	
	if (counter2 == tabsize - 1)
		getchar();
	*(num2 + counter2) = '\0';
	
	if (validate(num1) && validate(num2))
	{
		add(num1, num2, wynik, 2 * tabsize);
		puts(wynik);
	}
	else
	{
		printf("error");
		return 1;
	}

	return 0;
}