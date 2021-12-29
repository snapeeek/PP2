#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void string_to_float(char* string, float* res)
{
	int len = strlen(string);
	int mnoznik = 1;
	int i;

	for (i = len - 1; i >= 0; i--, mnoznik = mnoznik * 10)
	{
		*res = (float)(((int)*(string + i) - '0') * mnoznik) + *res;
	}
}

int validate_expression(const char *expr)
{
	if (expr == NULL)
		return -1;
	
	if (((*(expr) < 48) || (*(expr) > 57)) || ((*(expr + strlen(expr) - 1)  < 48) || (*(expr + strlen(expr) - 1) > 57)))
		return 0;

	int i = 0;
	while (*(expr + i) != '\0')
	{
		if (((*(expr + i) < 48) || (*(expr + i) > 57)) && ((*(expr + i) != 42) && (*(expr + i) != 43) && (*(expr + i) != 45) && (*(expr + i) != 47)))
			return 0;

		if (((*(expr + i) == 42) || (*(expr + i) == 43) || (*(expr + i) == 45) || (*(expr + i) == 47)) && ((*(expr + i + 1) == 42) || (*(expr + i + 1) == 43) || (*(expr + i + 1) == 45) || (*(expr + i + 1) == 47)))
			return 0;
		i++;
	}

	return 1;
}

int calculate(const char* expr, float *result)
{
	if ((expr == NULL) || (result == NULL))
		return 0;

	if (validate_expression(expr) == 0)
		return 0;
	
	if ((strchr(expr, '/') == NULL) && (strchr(expr, '*') == NULL) && (strchr(expr, '+') == NULL) && (strchr(expr, '-') == NULL))
	{
		string_to_float((char*)expr, result);
		return 1;
	}
	
	
	int op = 0, //do sprawdzania operatora: 1 = dodawanie, 2 odejmowanie, 3 mnozenie, 4 dzielenie
		len = strlen(expr),
		op_counter = 0, //zeby sprawdzic ktora operacja
		counter = 0, // do uzupelniania helpera
		i = 0; // licznik ogolny
	char helper[200];
	float helperf, *p;
	p = &helperf;

	while ((*(expr + i) >= '0') && (*(expr + i) <= '9'))
	{
		*(helper + i) = *(expr + i);
		i++;
	}
	*(helper + i) = '\0';
	*p = 0;
	string_to_float(helper, result); //pierwszy wrzut do resa

	while (i != len + 1)
	{
		if (*(expr + i) == '+')
		{
			if (op_counter == 0)
			{
				op = 1;
				op_counter++; //bo wtedy nie ma helperf
			}
			else {
				*(helper + counter) = '\0';
				*p = 0;
				string_to_float(helper, p);
				if (op == 1)
				{
					*result += helperf;
				}
				else if (op == 2)
				{
					*result -= helperf;
				}
				else if (op == 3)
				{
					*result *= helperf;
				}
				else if (op == 4)
				{
					*result /= helperf;
				}
				
				op = 1;
				op_counter++;
				counter = 0;
			}
		}
		else if (*(expr + i) == '-')
		{
			if (op_counter == 0)
			{
				op = 2;
				op_counter++;
			}
			
			else {
				*(helper + counter) = '\0';
				*p = 0;
				string_to_float(helper, p);
				if (op == 1)
				{
					*result += helperf;
				}
				else if (op == 2)
				{
					*result -= helperf;
				}
				else if (op == 3)
				{
					*result *= helperf;
				}
				else if (op == 4)
				{
					*result /= helperf;
				}
				
				op = 2;
				op_counter++;
				counter = 0;
			}
		}
		else if (*(expr + i) == '*')
		{
			if (op_counter == 0)
			{
				op = 3;
				op_counter++;
			}
			else {
				*(helper + counter) = '\0';
				*p = 0;
				string_to_float(helper, p);
				if (op == 1)
				{
					*result += helperf;
				}
				else if (op == 2)
				{
					*result -= helperf;
				}
				else if (op == 3)
				{
					*result *= helperf;
				}
				else if (op == 4)
				{
					*result /= helperf;
				}
				
				op = 3;
				op_counter++;
				counter = 0;
			}
		}
		else if (*(expr + i) == '/')
		{
			if (op_counter == 0)
			{
				op = 4;
				op_counter++;
			}
			else {
				*(helper + counter) = '\0';
				*p = 0;
				string_to_float(helper, p);
				if (op == 1)
				{
					*result += helperf;
				}
				else if (op == 2)
				{
					*result -= helperf;
				}
				else if (op == 3)
				{
					*result *= helperf;
				}
				else if (op == 4)
				{
					*result /= helperf;
				}
				
				op = 4;
				op_counter++;
				counter = 0;
			}
		}
		else if (*(expr + i) == '\0')
		{
			*(helper + counter) = '\0';
			*p = 0;
			string_to_float(helper, p);
			if (op == 1)
			{
				*result += helperf;
			}
			else if (op == 2)
			{
				*result -= helperf;
			}
			else if (op == 3)
			{
				*result *= helperf;
			}
			else if (op == 4)
			{
				*result /= helperf;
			}
		}
		else
		{
			*(helper + counter) = *(expr + i);
			counter++;
		}
		i++;
	}

	return 1;
}

int main()
{
	char expr[200];
	float res = 0, *p;
	p = &res;
	printf("Podaj wyrazenie: ");
	scanf("%199s", expr);

	if (calculate(expr, p) == 0)
	{
		printf("Error");
		return 1;
	}
	else
		printf("%.2f", res);

	return 0;
}