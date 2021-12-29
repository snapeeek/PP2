#include<stdio.h>
#include<stdlib.h>

void swap(int *x, int *y) 
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int sort_int(int* tab, int N, int(*p)(int, int))
{
	if (N < 1 || tab == NULL || p == NULL) 
		return 1;
	int i, j;
	
	for (i = 0; i < N; i++) 
	{
		for (j = 0; j < N - 1; j++) 
		{
			if (p(*(tab + j), *(tab + j + 1)) == 1) 
				swap((tab + j), (tab + j + 1));
		}
	}
	return 0;
}

int comp_int(int a, int b)
{
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}
int comp_int_abs(int a, int b)
{
	if (abs(a) > abs(b))
		return 1;
	else if (abs(a) < abs(b))
		return -1;
	else
		return 0;
}

int comp_int_length(int a, int b)
{
	int lena = 0, lenb = 0;
	while (abs(a) >= 1)
	{
		lena++;
		a /= 10;
	}
	while (abs(b) >= 1)
	{
		lenb++;
		b /= 10;
	}

	if (lena > lenb)
		return 1;
	else if (lena < lenb)
		return -1;
	else
		return 0;
}

int comp_int_digits_sum(int a, int b) {
	int suma = 0, sumb = 0;
	int tempa = a, tempb = b;
	
	if (tempa < 0) 
		tempa = abs(tempa);
	if (tempb < 0) 
		tempb = abs(tempb);
	
	suma += tempa % 10;
	sumb += tempb % 10;
	
	while ((tempa /= 10) != 0) 
		suma += tempa % 10;
	
	while ((tempb /= 10) != 0) 
		sumb += tempb % 10;
	
	if (suma > sumb) 
		return 1;
	else if (suma < sumb) 
		return -1;
	else 
		return 0;
}
