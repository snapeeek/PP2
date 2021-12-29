#include<stdio.h>
#include<stdlib.h>

int swap(int* a, int* b)
{
	int temp;
	if ((a != NULL) && (b != NULL)) {
		temp = *a;
		*a = *b;
		*b = temp;
		return 1;
	}
	else
		return 0;
}

int main()
{
	int a, b, *p, *p2;

	p = &a;
	p2 = &b;
	printf("Podaj dwie liczby int po spacji: ");
	scanf("%d %d", &a, &b);
	swap(p, p2);
	printf("a: %d; b: %d\n", *p, *p2);





	return 0;
}