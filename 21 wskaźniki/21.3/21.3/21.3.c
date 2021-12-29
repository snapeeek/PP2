#include<stdio.h>

int main()
{
	int T[10], *p;

	p = T;

	for (int i = 0; i < 10; i++)
	{
		*p = i;
		p++;
	}

	p = T;

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", *p);
		p++;
	}






	return 0;
}