#include<stdio.h>
#include<stdlib.h>

void binary(unsigned long long val) 
{ 
	for (int i = 63; i >= 0; i--) 
	{ 
		if ((i + 1) % 8 == 0 && i != 63)
			printf(" ");
		printf("%lld",((val >> i) % 2)); 
	}    
	printf("\n");
}

int main()
{
	unsigned long long u;
	printf("Podaj liczbe 64 bitowa: ");
	scanf("%llu", &u);

	binary(u);


	return 0;
}