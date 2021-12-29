#include<stdio.h>
#include<stdlib.h>

int clamp(int *v, int lo, int hi)
{
	if (v == NULL)
		return 0;
	if (lo < hi)
	{
		if (*v < lo)
			*v = lo;
		else if (*v > hi)
			*v = hi;
		
	}
	else
	{
		if (*v < hi)
			*v = hi;
		else if (*v > lo)
			*v = lo;
		
	}
	return 1;
	
}


int main()
{
	int lim1, lim2, input, *p;
	p = &input;
	printf("Podaj liczbe: ");
	scanf("%d", &input);
	printf("Podaj pierwsza granice: ");
	scanf("%d", &lim1);
	printf("Podaj druga granice: ");
	scanf("%d", &lim2);

	clamp(p, lim1, lim2);
	printf("Liczba wynosi: %d\n", *p);




	return 0;
}