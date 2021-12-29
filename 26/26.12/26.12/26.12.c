#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define tabsize 201

//wymagane
int validate(const char * number);
int compare(const char* number1, const char* number2);
int add(const char* number1, const char* number2, char** result);
int subtract(const char* number1, const char* number2, char** result);

//moje

void mow_the_grass(char *num);
void calculate_sub(const char* number1, const char* number2, char** result, int sign);
void calculate_add(const char* number1, const char* number2, char** result, int sign);
int compare_unsigned(const char* number1, const char* number2);
void small_loan_of_a_million_dollars(char* number, int pos);
void rev(char* num);


int main()
{
	char *num1, *num2, *wynik;
	int buff;
	num1 = (char*)malloc(tabsize * sizeof(char));
	if (!num1)
	{
		printf("Failed to allocate memory");
		return 2;
	}

	num2 = (char*)malloc(tabsize * sizeof(char));
	if (!num2)
	{
		printf("Failed to allocate memory");
		free(num1);
		return 2;
	}
	
	printf("Podaj pierwsza liczbe: ");
	scanf("%200s", num1);

	while ((buff != EOF) &&((buff = getchar()) != '\n'));

	printf("Podaj druga liczbe: ");
	scanf("%200s", num2);



	if (validate(num1) || validate(num2))
	{
		printf("Error");
		free(num1);
		free(num2);
		return 1;
	}

	if (add(num1, num2, &wynik) == 3) {
		printf("Failed to allocate memory\n");
		free(num1);
		free(num2);
		return 2;
	}

	puts(wynik);
	free(wynik);

	if (subtract(num1, num2, &wynik) == 3) {
		printf("Failed to allocate memory\n");
		free(num1);
		free(num2);
		return 2;
	}

	puts(wynik);


	free(num1);
	free(num2);
	free(wynik);
	return 0;
}

int validate(const char *number)
{
	if (!number) 
	{
		return 2;
	}

	if (!strlen(number)) 
	{
		return 1;
	}

	if (strlen(number) == 1 && *(number) == '-') 
	{
		return 1;
	}
	else if ((strlen(number) > 1) && ((*(number) == '-' && *(number + 1) == '0') || (*(number) == '0'))) 
	{
		return 1;
	}

	if ((*(number) != '-') && (!isdigit(*number))) 
	{
		return 1;
	}

	for (int i = 1; i < (int)strlen(number); i++) 
	{
		if (!isdigit(*(number + i))) 
		{
			return 1;
		}
	}

	return 0;
}

int add(const char* number1, const char* number2, char** result)
{
	if (!number1 || !number2 || !result) 
	{
		return 1;
	}

	if (validate(number1) || validate(number2)) 
	{
		return 2;
	}

	int length1 = strlen(number1);
	int length2 = strlen(number2);

	if ((*number1 == '-') && (*number2 == '-')) 
	{
		if (!(*result = malloc((length1 < length2 ? length2 : length1) + 2))) 
		{
			return 3;
		}

		length1 < length2 ? calculate_add(number2, number1, result, 1) : calculate_add(number1, number2, result, 1);
	}
	else if (!(*number1 == '-') && !(*number2 == '-')) 
	{
		if (!(*result = malloc((length1 < length2 ? length2 : length1) + 2))) 
		{
			return 3;
		}

		length1 < length2 ? calculate_add(number2, number1, result, 0) : calculate_add(number1, number2, result, 0);
	}
	else if (!(*number1 == '-') && (*number2 == '-')) 
	{
		if (compare_unsigned(number1, number2) >= 0) 
		{
			if (!(*result = malloc(length1 + 1))) 
			{
				return 3;
			}

			calculate_sub(number1, number2, result, 0);
		}
		else 
		{
			if (!(*result = malloc(length2 + 1))) 
			{
				return 3;
			}

			calculate_sub(number2, number1, result, 1);
		}
	}
	else {
		if (compare_unsigned(number1, number2) > 0) 
		{
			if (!(*result = malloc(length1 + 1))) 
			{
				return 3;
			}

			calculate_sub(number1, number2, result, 1);
		}
		else 
		{
			if (!(*result = malloc(length2 + 1))) 
			{
				return 3;
			}

			calculate_sub(number2, number1, result, 0);
		}
	}

	return 0;
}

int subtract(const char* number1, const char* number2, char** result)
{
	if (!number1 || !number2 || !result) 
	{
		return 1;
	}

	if (validate(number1) || validate(number2)) 
	{
		return 2;
	}

	int length1 = strlen(number1);
	int length2 = strlen(number2);

	if ((*number1 == '-') && !(*number2 == '-')) 
	{
		if (!(*result = malloc((length1 < length2 ? length2 : length1) + 3))) 
		{
			return 3;
		}

		length1 < length2 ? calculate_add(number2, number1, result, 1) : calculate_add(number1, number2, result, 1);
	}
	else if (!(*number1 == '-') && (*number2 == '-')) 
	{
		if (!(*result = malloc((length1 < length2 ? length2 : length1) + 2))) 
		{
			return 3;
		}

		length1 < length2 ? calculate_add(number2, number1, result, 0) : calculate_add(number1, number2, result, 0);
	}
	else if (!(*number1 == '-') && !(*number2 == '-')) 
	{
		if (compare_unsigned(number1, number2) >= 0) 
		{
			if (!(*result = malloc(length1 + 1))) 
			{
				return 3;
			}

			calculate_sub(number1, number2, result, 0);
		}
		else {
			if (!(*result = malloc(length2 + 2))) 
			{
				return 3;
			}

			calculate_sub(number2, number1, result, 1);
		}
	}
	else {
		if (compare_unsigned(number1, number2) > 0) 
		{
			if (!(*result = malloc(length1 + 1))) 
			{
				return 3;
			}

			calculate_sub(number1, number2, result, 1);
		}
		else {
			if (!(*result = malloc(length2 + 1))) 
			{
				return 3;
			}

			calculate_sub(number2, number1, result, 0);
		}
	}

	return 0;
}

void calculate_add(const char* number1, const char* number2, char** result, int sign)
{
	int is_one = 0;
	int temp;
	int length1 = strlen(number1);
	int length2 = strlen(number2);

	int i = 0;

	while (i < length2 && isdigit(*(number1 + length1 - 1 - i)) && isdigit(*(number2 + length2 - 1 - i))) 
	{
		if ((temp = *(number1 + length1 - 1 - i) + *(number2 + length2 - 1 - i) - 2 * '0' + is_one) > 9) 
		{
			is_one = 1;
			temp %= 10;
		}
		else {
			is_one = 0;
		}

		*(*result + i++) = temp + '0';
	}

	while (i < length1 && isdigit(*(number1 + length1 - 1 - i))) 
	{
		if ((temp = *(number1 + length1 - 1 - i) - '0' + is_one) > 9) 
		{
			is_one = 1;
			temp %= 10;
		}
		else 
		{
			is_one = 0;
		}

		*(*result + i++) = temp + '0';
	}

	if (is_one) 
	{
		*(*result + i++) = '1';
	}

	if (sign) 
	{
		*(*result + i++) = '-';
	}

	*(*result + i) = '\0';

	rev(*result);
}

void calculate_sub(const char* number1, const char* number2, char** result, int sign)
{
	int temp;
	int length1 = strlen(number1);
	int length2 = strlen(number2);
	int minus2 = 0;
	if (*number2 == '-')
		minus2 = 1;

	char *temporary_number;

	temporary_number = malloc(length1 + 1);
	memcpy(temporary_number, number1, length1 + 1);

	int i = 0;

	while (i < (length2 - minus2) && isdigit(*(temporary_number + length1 - 1 - i)) && isdigit(*(number2 + length2 - 1 - i))) 
	{
		if ((temp = *(temporary_number + length1 - 1 - i) - *(number2 + length2 - 1 - i)) < 0) 
		{
			small_loan_of_a_million_dollars(temporary_number, length1 - 2 - i);
			*(*result + i++) = 10 + temp + '0';
		}
		else 
		{
			*(*result + i++) = temp + '0';
		}
	}

	while (i < (length1 - minus2) && isdigit(*(temporary_number + length1 - 1 - i))) 
	{
		*(*result + i) = *(temporary_number + length1 - 1 - i);
		i++;
	}

	if (sign) 
	{
		*(*result + i++) = '-';
	}

	*(*result + i) = '\0';

	rev(*result);
	mow_the_grass(*result);

	free(temporary_number);
}
int compare(const char* number1, const char* number2)
{
	if (!number1 || !number2)
		return 2;
	
	if (validate(number1) == 1 || validate(number2) == 1)
		return 3;

	if ((*number1 == '-') && (*number2 != '-'))
		return -1;
	if ((*number1 != '-') && (*number2 == '-'))
		return 1;


	int length1 = strlen(number1),
		length2 = strlen(number2);
	if (length1 == length2)
	{
		int i = 0;
		if ((*number1 != '-') && (*number2 != '-'))
		{
			while (i < length1)
			{
				if (*(number1 + i) > (*(number2 + i)))
					return 1;
				else if (*(number1 + i) < (*(number2 + i)))
					return -1;
				i++;
			}
		}
		else if (*number1 == '-' && *number2 == '-')
		{
			while (i < length1)
			{
				if (*(number1 + i) >(*(number2 + i)))
					return -1;
				else if (*(number1 + i) < (*(number2 + i)))
					return 1;
				i++;
			}
		}
		return 0;
	}
	else if (length1 > length2)
	{
		if (*number1 == '-' && *number2 == '-')
			return -1;
		return 1;
	}
		
	else
	{
		if (*number1 == '-' && *number2 == '-')
			return 1;
		return -1;
	}
	
	

	return 0;
}

int compare_unsigned(const char* number1, const char* number2)
{
	int length1 = strlen(number1);
	int length2 = strlen(number2);
	int minus1 = 0;
	int minus2 = 0;

	if (*number1 == '-') {
		length1--;
		minus1 = 1;
	}

	if (*number2 == '-') {
		length2--;
		minus2 = 1;
	}

	if (length1 > length2) {
		return 1;
	}
	else if (length1 < length2) {
		return -1;
	}

	for (int i = 0; i < length1; i++) {
		if (*(number1 + minus1 + i) > *(number2 + minus2 + i)) {
			return 1;
		}
		else if (*(number1 + minus1 + i) < *(number2 + minus2 + i)) {
			return -1;
		}
	}

	return 0;
}

void mow_the_grass(char *number)
{
	char *temp;

	temp = malloc((int)strlen(number) + 1);
	memcpy(temp, number, (int)strlen(number) + 1);

	int started = 1;
	int counter = 0;;

	int i = 0;

	if (*number == '-') 
	{
		*(number + counter++) = '-';
		i++;
	}

	for (; i < (int)strlen(number); i++) 
	{
		if (started && (*(temp + i) == '0')) 
		{
			continue;
		}
		else 
		{
			started = 0;
			*(number + counter++) = *(temp + i);
		}
	}

	if (started) 
	{
		*(number + counter++) = '0';
	}

	*(number + counter) = '\0';

	free(temp);
}

void small_loan_of_a_million_dollars(char* number, int pos)
{
	while (*(number + pos) == '0') {
		*(number + pos) = '9';
		pos--;
	}

	(*(number + pos))--;
}

void rev(char* number)
{
	char ch;
	int length = strlen(number);

	for (int i = 0; i < length / 2; i++) {
		ch = *(number + i);
		*(number + i) = *(number + length - 1 - i);
		*(number + length - 1 - i) = ch;
	}
}