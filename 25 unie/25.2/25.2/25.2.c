#include<stdio.h>

union word_set
{
	int number;
	unsigned short tab[2];
};

int main() {
	union word_set unia;
	printf("Podaj liczbe: ");
	scanf("%d", &unia.number);
	for (int i = 0; i < 2; i++)
	{
		printf("%d ", *(unia.tab + i));
	}
	return 0;
}