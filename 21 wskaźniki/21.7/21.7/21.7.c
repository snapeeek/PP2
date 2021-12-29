#include<stdio.h>
#include<stdlib.h>

int sum(const float* tab, unsigned int size, float *result)
{
	float suma = 0;
	if ((tab != NULL) && (result != NULL))
	{
		for (unsigned int i = 0; i < size; i++)
		{
			suma = *tab + suma;
			tab++;
		}
		*result = suma;
		printf("%.2f", *result);
		return 1;
	}
	else
		return 0;
}
int avg(const float* tab, unsigned int size, float *result)
{
	float suma = 0;
	if ((tab != NULL) && (result != NULL))
	{
		for (unsigned int i = 0; i < size; i++)
		{
			suma = *tab + suma;
			tab++;
		}
		*result = suma / (size);
		printf("%.2f", *result);
		return 1;
	}
	else
		return 0;
	
}

int main()
{
	float input, tab[100], *p, *p2, res, res1;
	unsigned int size = 0;
	printf("Podaj liczby (maks 100): ");
	p = tab;
	for (int i = 0; i < 100; i++)
	{
		scanf("%f", &input);
		if (input != 0) {
			*p = input;
			p++;
			size++;
		}
		else
			break;
	}

	if (size == 0)
	{
		printf("Error");
		return 1;
	}
	p = &res;
	p2 = &res1;

	sum(tab, size, p);
	printf("\n");
	avg(tab, size, p2);
	printf("\n");
	




	return 0;
}