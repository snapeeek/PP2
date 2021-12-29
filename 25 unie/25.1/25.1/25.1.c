#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>

union byte_set
{
	unsigned int liczba;
	unsigned char byte;
};

int main()
{
	union byte_set lel, *p;
	p = &lel;
	int ile = 0;
	printf("Podaj liczbe: ");
	scanf("%u", &(p->liczba));
	
	while (ile < 4)
	{
		printf("%d ", p->byte);
		p->liczba /=  256;
		ile++;
	}

	return 0;
}