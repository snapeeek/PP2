#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
	double T[100], *p, suma = 0;
	srand(time(NULL));

	p = T;

	for (int i = 0; i < 100; i++)
	{
		*p = (double)((rand()) + 100000) / 10000;
		p++;
	}

	p = T;
	for (int i = 0; i < 100; i++)
	{
		printf("%.4lf ", *p);
		p++;
	}

	p = T;
	for (int i = 0; i < 100; i++)
	{
		suma = suma + (*p);
		p++;
	}
	printf("\nSuma wynosi: %.2lf\n", suma);
	printf("Srednia wynosi: %.2lf\n", suma/100);
	

	return 0;


}