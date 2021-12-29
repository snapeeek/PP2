#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
	int T[20], *p;
	srand(time(NULL));

	p = T;

	for (int i = 0; i < 20; i++)
	{
		*p = rand()%100;
		p++;
	}

	p = T;

	for (int i = 0; i < 20; i++)
	{
		printf("%d ", *p);
		p++;
	}
	printf("\n");
	p = T;

	for (int i = 0; i < 20; i = i + 2)
	{
		printf("%d ", *p);
		p = p + 2;
	}




	return 0;
}