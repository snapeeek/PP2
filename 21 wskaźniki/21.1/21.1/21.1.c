#include<stdio.h>

int main()
{
	int a, *p;
	float b, *p2;
	char c, *p3;

	p = &a;
	p2 = &b;
	p3 = &c;

	*p = 1;
	*p2 = 5.6;
	*p3 = 'a';

	printf("%d %.1f %c\n", *p, *p2, *p3);





	return 0;
}