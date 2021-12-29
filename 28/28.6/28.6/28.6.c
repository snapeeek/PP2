#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//stare rzeczy
int subtract(const char* number1, const char* number2, char** result);
int add(const char* number1, const char* number2, char** result);
int validate(const char *number);
int compare(const char* number1, const char* number2);
void calculate_add(const char* number1, const char* number2, char** result, int sign);
void calculate_sub(const char* number1, const char* number2, char** result, int sign);
int comp_unsign(const char* number1, const char* number2);
int is_neg(const char* number);
void mow_grass(char *num);
void small_loan_of_a_million_dollars(char* num, int position);
void rev(char* num);


//nowe rzeczy
int multiply(const char* number1, const char* number2, char** result);
int calculate(const char* expr, char **result);
int validate_expression(const char *expr);
int calculate_mult(const char* number1, const char* number2, char** result, int sign);
int mult_add(const char* number1, const char* number2, char** result);
void set_value(char **result, int length);
int what_is_next(const char *expr, char **num, int *position);

int main()
{
	char *expr;
	char *result;

	if (!(expr = malloc(501))) 
	{
		printf("Failed to allocate memory");
		return 3;
	}

	printf("Podaj wyrazenie: ");
	scanf("%1000s", expr);

	switch (calculate(expr, &result)) 
	{
	case 1:
		printf("Error\n");
		free(expr);
		return 1;
	case 2:
		printf("Incorrect input\n");
		free(expr);
		return 2;
	case 3:
		printf("Failed to allocate memory");
		free(expr);
		return 3;
	}

	printf("%s\n", result);

	free(result);
	free(expr);

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

	if (is_neg(number1) && !is_neg(number2)) 
	{
		if (!(*result = malloc((length1 < length2 ? length2 : length1) + 3))) 
		{
			return 3;
		}

		length1 - 1 < length2 ? calculate_add(number2, number1, result, 1) : calculate_add(number1, number2, result, 1);
	}
	else if (!is_neg(number1) && is_neg(number2)) 
	{
		if (!(*result = malloc((length1 < length2 ? length2 : length1) + 2))) 
		{
			return 3;
		}

		length1 < length2 - 1 ? calculate_add(number2, number1, result, 0) : calculate_add(number1, number2, result, 0);
	}
	else if (!is_neg(number1) && !is_neg(number2)) 
	{
		if (comp_unsign(number1, number2) >= 0) 
		{
			if (!(*result = malloc(length1 + 1))) 
			{
				return 3;
			}

			calculate_sub(number1, number2, result, 0);
		}
		else 
		{
			if (!(*result = malloc(length2 + 2))) 
			{
				return 3;
			}

			calculate_sub(number2, number1, result, 1);
		}
	}
	else 
	{
		if (comp_unsign(number1, number2) > 0) 
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

	if (is_neg(number1) && is_neg(number2)) 
	{
		if (!(*result = malloc((length1 < length2 ? length2 : length1) + 2))) 
		{
			return 3;
		}

		length1 < length2 ? calculate_add(number2, number1, result, 1) : calculate_add(number1, number2, result, 1);
	}
	else if (!is_neg(number1) && !is_neg(number2)) 
	{
		if (!(*result = malloc((length1 < length2 ? length2 : length1) + 2))) 
		{
			return 3;
		}

		length1 < length2 ? calculate_add(number2, number1, result, 0) : calculate_add(number1, number2, result, 0);
	}
	else if (!is_neg(number1) && is_neg(number2)) 
	{
		if (comp_unsign(number1, number2) >= 0) 
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
	else
	{
		if (comp_unsign(number1, number2) > 0) 
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
	else if (strlen(number) > 1 && (*(number) == '-' && *(number + 1) == '0' || *(number) == '0')) 
	{
		return 1;
	}

	if (*(number) != '-' && !isdigit(*number)) 
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

int compare(const char* number1, const char* number2)
{
	if (!number1 || !number2) 
	{
		return 2;
	}

	if (validate(number1) || validate(number2)) 
	{
		return 3;
	}

	if (is_neg(number1) && is_neg(number2)) 
	{
		if (strlen(number1) < strlen(number2)) 
		{
			return 1;
		}
		else if (strlen(number1) > strlen(number2)) 
		{
			return -1;
		}

		for (int i = 1; i < (int)strlen(number1); i++) 
		{
			if (*(number1 + i) < *(number2 + i)) 
			{
				return 1;
			}
			else if (*(number1 + i) > *(number2 + i)) 
			{
				return -1;
			}
		}
	}
	else if (is_neg(number1) && !is_neg(number2)) 
	{
		return -1;
	}
	else if (!is_neg(number1) && is_neg(number2)) 
	{
		return 1;
	}
	else 
	{
		if (strlen(number1) > strlen(number2)) 
		{
			return 1;
		}
		else if (strlen(number1) < strlen(number2)) 
		{
			return -1;
		}

		for (int i = 0; i < (int)strlen(number1); i++) 
		{
			if (*(number1 + i) > *(number2 + i)) 
			{
				return 1;
			}
			else if (*(number1 + i) < *(number2 + i)) 
			{
				return -1;
			}
		}
	}

	return 0;
}

int is_neg(const char* number)
{
	if (*(number) == '-') 
	{
		return 1;
	}

	return 0;
}

void calculate_add(const char* number1, const char* number2, char** result, int sign)
{
	int carried = 0;
	int temporary;
	int length1 = strlen(number1);
	int length2 = strlen(number2);

	int i = 0;

	while (i < length2 && isdigit(*(number1 + length1 - i - 1)) && isdigit(*(number2 + length2 - i - 1))) 
	{
		if ((temporary = *(number1 + length1 - i - 1) + *(number2 + length2 - i - 1) - 2 * '0' + carried) > 9) 
		{
			carried = 1;
			temporary %= 10;
		}
		else 
		{
			carried = 0;
		}

		*(*result + i++) = temporary + '0';
	}

	while (i < length1 && isdigit(*(number1 + length1 - i - 1))) 
	{
		if ((temporary = *(number1 + length1 - i - 1) - '0' + carried) > 9) 
		{
			carried = 1;
			temporary %= 10;
		}
		else 
		{
			carried = 0;
		}

		*(*result + i++) = temporary + '0';
	}

	if (carried) 
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
	int temporary;
	int length1 = strlen(number1);
	int length2 = strlen(number2);
	int negative1 = is_neg(number1);
	int negative2 = is_neg(number2);

	char *temp_num;

	temp_num = malloc(length1 + 1);
	memcpy(temp_num, number1, length1 + 1);

	int i = 0;

	while (i < (length2 - negative2) && isdigit(*(temp_num + length1 - i - 1)) && isdigit(*(number2 + length2 - i - 1))) 
	{
		if ((temporary = *(temp_num + length1 - i - 1) - *(number2 + length2 - i - 1)) < 0) 
		{
			small_loan_of_a_million_dollars(temp_num, length1 - 2 - i);
			*(*result + i++) = 10 + temporary + '0';
		}
		else 
		{
			*(*result + i++) = temporary + '0';
		}
	}

	while (i < (length1 - negative1) && isdigit(*(temp_num + length1 - i - 1))) 
	{
		*(*result + i) = *(temp_num + length1 - i - 1);
		i++;
	}

	if (sign) 
	{
		*(*result + i++) = '-';
	}

	*(*result + i) = '\0';

	rev(*result);
	mow_grass(*result);

	free(temp_num);
}

int comp_unsign(const char* number1, const char* number2)
{
	int length1 = strlen(number1);
	int length2 = strlen(number2);
	int negative1 = 0;
	int negative2 = 0;

	if (is_neg(number1))
	{
		length1--;
		negative1 = 1;
	}

	if (is_neg(number2))
	{
		length2--;
		negative2 = 1;
	}

	if (length1 > length2)
	{
		return 1;
	}
	else if (length1 < length2)
	{
		return -1;
	}

	for (int i = 0; i < length1; i++)
	{
		if (*(number1 + negative1 + i) > *(number2 + negative2 + i))
		{
			return 1;
		}
		else if (*(number1 + negative1 + i) < *(number2 + negative2 + i))
		{
			return -1;
		}
	}

	return 0;
}

void mow_grass(char *num)
{
	char *temp_num;

	temp_num = malloc((int)strlen(num) + 1);
	memcpy(temp_num, num, (int)strlen(num) + 1);

	int started = 1;
	int counter = 0;;

	int i = 0;

	if (is_neg(num)) 
	{
		*(num + counter++) = '-';
		i++;
	}

	for (; i < (int)strlen(num); i++) 
	{
		if (started && (*(temp_num + i) == '0')) 
		{
			continue;
		}
		else 
		{
			started = 0;
			*(num + counter++) = *(temp_num + i);
		}
	}

	if (started) 
	{
		*(num + counter++) = '0';
	}

	*(num + counter) = '\0';

	free(temp_num);
}

void small_loan_of_a_million_dollars(char* num, int position)
{
	while (*(num + position) == '0') 
	{
		*(num + position) = '9';
		position--;
	}

	(*(num + position))--;
}

void rev(char* number)
{
	char temporary;
	int length = strlen(number);

	for (int i = 0; i < length / 2; i++) 
	{
		temporary = *(number + i);
		*(number + i) = *(number + length - i - 1);
		*(number + length - i - 1) = temporary;
	}
}

int multiply(const char* number1, const char* number2, char** result)
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

	if (*number1 == '0' || *number2 == '0') 
	{
		if (!(*result = malloc(2))) 
		{
			return 3;
		}

		**result = '0';
		*(*result + 1) = '\0';

		return 0;
	}

	if (is_neg(number1) && is_neg(number2)) 
	{
		if (!(*result = malloc(length1 + length2 - 1))) 
		{
			return 3;
		}

		set_value(result, length1 + length2 - 1);

		if (length1 > length2 ? calculate_mult(number1 + 1, number2 + 1, result, 0) : calculate_mult(number2 + 1, number1 + 1, result, 0))
		{
			return 3;
		}
	}
	else if (!is_neg(number1) && !is_neg(number2)) 
	{
		if (!(*result = malloc(length1 + length2 + 1))) 
		{
			return 3;
		}

		set_value(result, length1 + length2 + 1);

		if (length1 > length2 ? calculate_mult(number1, number2, result, 0) : calculate_mult(number2, number1, result, 0)) 
		{
			return 3;
		}
	}
	else 
	{
		if (!(*result = malloc(length1 + length2 + 1))) 
		{
			return 3;
		}

		set_value(result, length1 + length2 + 1);

		if (is_neg(number1)) 
		{
			if (length1 > length2 ? calculate_mult(number1 + 1, number2, result, 1) : calculate_mult(number2, number1 + 1, result, 1)) 
			{
				return 3;
			}
		}
		else 
		{
			if (length1 < length2 ? calculate_mult(number2 + 1, number1, result, 1) : calculate_mult(number1, number2 + 1, result, 1)) 
			{
				return 3;
			}
		}
	}

	return 0;
}

int calculate_mult(const char* number1, const char* number2, char** result, int sign)
{
	int length1 = strlen(number1);
	int length2 = strlen(number2);
	int carry = 0;
	int position = 0;
	char *temporary, *sum;

	if (!(temporary = malloc(length1 + length2 + 1))) 
	{
		return 1;
	}

	mow_grass(*result);

	for (int i = length2 - 1; i >= 0; i--) 
	{
		set_value(&temporary, length1 + length2 + 1);
		position = length2 - i - 1;
		carry = 0;
		for (int j = length1 - 1; j >= 0; j--) 
		{
			carry += (*(number1 + j) - '0') * (*(number2 + i) - '0');

			*(temporary + position) = (carry % 10) + '0';

			carry = (carry - carry % 10) / 10;

			position++;
		}

		*(temporary + position) = carry + '0';
		*(temporary + position + 1) = '\0';

		rev(temporary);
		mow_grass(temporary);

		if (mult_add(temporary, *result, &sum)) 
		{
			free(temporary);
			return 1;
		}
		
		strcpy(*result, sum);
		free(sum);

		set_value(&temporary, length1 + length2 + 1);
	}

	if (sign) 
	{
		memmove(*result + 1, *result, strlen(*result) + 1);
		*(*result) = '-';
	}

	free(temporary);

	return 0;
}

void set_value(char **res, int length)
{
	for (int i = 0; i < length - 1; i++) 
	{
		*(*res + i) = '0';
	}

	*(*res + length - 1) = '\0';
}

int calculate(const char* expr, char **result)
{
	if (!expr || !result) 
	{
		return 1;
	}

	if (validate_expression(expr)) 
	{
		return 2;
	}

	char *temporary1, *temporary2, *helper;
	int position = -1;


	switch (what_is_next(expr, result, &position)) 
	{
	case 2:
		return 2;
	case 3:
		return 3;
	}

	if (position == (int)strlen(expr)) 
	{
		return 0;
	}

	while (position < (int)strlen(expr)) 
	{
		switch (*(expr + position)) 
		{
		case '*':
			switch (what_is_next(expr, &temporary1, &position)) 
			{
			case 2:
				free(*result);
				return 2;
			case 3:
				free(*result);
				return 3;
			}
			multiply(*result, temporary1, &temporary2);
			if (!(helper = realloc(*result, strlen(temporary2) + 1))) 
			{
				free(temporary1);
				free(temporary2);
				return 3;
			}
			*result = helper;
			strcpy(*result, temporary2);
			free(temporary1);
			free(temporary2);
			break;
		case '-':
			switch (what_is_next(expr, &temporary1, &position)) 
			{
			case 2:
				free(*result);
				return 2;
			case 3:
				free(*result);
				return 3;
			}

			subtract(*result, temporary1, &temporary2);
			if (!(helper = realloc(*result, strlen(temporary2) + 1))) 
			{
				free(temporary1);
				free(temporary2);
				return 3;
			}
			*result = helper;
			strcpy(*result, temporary2);
			free(temporary1);
			free(temporary2);
			break;
		case '+':
			switch (what_is_next(expr, &temporary1, &position)) 
			{
			case 2:
				free(*result);
				return 2;
			case 3:
				free(*result);
				return 3;
			}			

			add(*result, temporary1, &temporary2);
			if (!(helper = realloc(*result, strlen(temporary2) + 1))) 
			{
				free(temporary1);
				free(temporary2);
				return 3;
			}
			*result = helper;
			strcpy(*result, temporary2);
			free(temporary1);
			free(temporary2);
			break;
		}
	}

	return 0;
}

int validate_expression(const char *expr)
{
	if (!expr) 
	{
		return 2;
	}

	int length = strlen(expr);

	if (length < 1) 
	{
		return 1;
	}

	if (!isdigit(*expr)) 
	{
		if (*expr != '-') 
		{
			return 1;
		}
		else if (length > 1 && !isdigit(*(expr + 1))) 
		{
			return 1;
		}
	}

	for (int i = 0; i < length; i++) 
	{
		if (!isdigit(*(expr + i)) && i < length - 2) 
		{
			if (*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*') 
			{
				if (!isdigit(*(expr + i + 1))) 
				{
					if (*(expr + i + 1) != '-') 
					{
						return 1;
					}
					else if (!isdigit(*(expr + i + 2))) 
					{
						return 1;
					}
				}
			}
			else 
			{
				return 1;
			}
		}
		else if (!isdigit(*(expr + i)) && i < length - 1) 
		{
			if (*(expr + i) == '+' || *(expr + i) == '*' || *(expr + i) == '-')
			{
				if (*(expr + i + 1) != '-' && !isdigit(*(expr + i + 1)))
				{
					return 1;
				}

			}
			else 
			{
				return 1;
			}
		}
		else if (!isdigit(*(expr + i))) 
		{
			return 1;
		}
	}

	if (!isdigit(*(expr + length - 1))) 
	{
		return 1;
	}

	return 0;
}

int what_is_next(const char *expr, char **num, int *position)
{
	int length;

	if (*(expr + *position + 1) == '-') 
	{
		length = strcspn(expr + *position + 2, "+-*");
		length++;
	}
	else 
	{
		length = strcspn(expr + *position + 1, "+-*");
	}

	if (!(*num = malloc(length + 1))) 
	{
		return 3;
	}

	memcpy(*num, expr + *position + 1, length);
	*(*num + length) = '\0';

	if (validate(*num)) 
	{
		free(*num);
		return 2;
	}

	*position += length + 1;

	return 0;
}

int mult_add(const char* number1, const char* number2, char** result)
{
	int length1 = strlen(number1);
	int length2 = strlen(number2);


	if (!(*result = malloc((length1 < length2 ? length2 : length1) + 2))) 
	{
		return 3;
	}

	length1 < length2 ? calculate_add(number2, number1, result, 0) : calculate_add(number1, number2, result, 0);

	return 0;
}