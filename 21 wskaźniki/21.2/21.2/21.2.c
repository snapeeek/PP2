#include<stdio.h>

int main()
{
	int a = 5, *p;
	p = &a;

	printf("%d %d %p\n", a, *p, (void*)p);

	*p = 3;
	printf("%d %d %p\n", a, *p, (void*)p);




	return 0;
}