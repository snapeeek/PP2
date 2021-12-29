#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	unsigned int first;
	unsigned short tab[2];
	unsigned char byte[4];
	struct probka bity[4];
};

int main()
{
	union bit_set help;
	printf("Podaj liczbe: ");
	scanf("%u", &(help.first));

	printf("%u\n", help.first);
	printf("%d %d\n", help.tab[0], help.tab[1]);
	printf("%d %d %d %d\n", help.byte[0], help.byte[1], help.byte[2], help.byte[3]);
	for (int i = 0; i < 4; i++)
	{
		printf("%d", help.bity[i].h);
		printf("%d", help.bity[i].g);
		printf("%d", help.bity[i].f);
		printf("%d", help.bity[i].e);
		printf("%d", help.bity[i].d);
		printf("%d", help.bity[i].c);
		printf("%d", help.bity[i].b);
		printf("%d", help.bity[i].a);
		printf(" ");
	}






	return 0;
}