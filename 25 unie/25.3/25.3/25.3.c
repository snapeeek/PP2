#include<stdio.h>

struct probka {
	unsigned char a : 1;
	unsigned char b : 1;
	unsigned char c : 1;
	unsigned char d : 1;
	unsigned char e : 1;
	unsigned char f : 1;
	unsigned char g : 1;
	unsigned char h : 1;
};

union bit_set {
	signed char number;
	struct probka bity;
};

int main()
{
	union bit_set unia;
	printf("Podaj bajt: ");
	scanf("%hhd", &(unia.number));
	
	printf("%d", unia.bity.h);
	printf("%d", unia.bity.g);
	printf("%d", unia.bity.f);
	printf("%d", unia.bity.e);
	printf("%d", unia.bity.d);
	printf("%d", unia.bity.c);
	printf("%d", unia.bity.b);
	printf("%d", unia.bity.a);





	return 0;
}
