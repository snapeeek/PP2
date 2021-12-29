#include<stdio.h>
#include<stdlib.h>

int is_equal(int a, int b);
int is_negative(int value);


int main()
{
	int in1, in2;

	printf("Podaj liczb: ");
	scanf("%d %d", &in1, &in2);

	if (is_equal(in1, in2))
		printf("rowne\n");
	else
		printf("nierowne\n");


	if (is_negative(in1))
		printf("ujemna ");
	else
		printf("nieujemna ");
	
	if (is_negative(in2))
		printf("ujemna");
	else
		printf("nieujemna");


	return 0;
}

int is_equal(int a, int b) 
{
	if (a^b)
		return 0;
	else 
		return 1;
}

int is_negative(int value)
{
	if (value & 2147483648)
		return 1;
	else 
		return 0;
}