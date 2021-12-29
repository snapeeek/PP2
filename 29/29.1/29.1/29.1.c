#include<stdio.h>
#include"int_operations.h"

int main()
{
	int in1, in2, choice;
	int(*p[4])(int, int) = 
	{
		add_int,
		sub_int,
		div_int,
		mul_int 	};
	printf("Podaj liczby: ");
	scanf("%d %d", &in1, &in2);

	printf("Podaj operacje: ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 0:
		printf("%d", calculate(in1, in2, (*p)));
		break;
	case 1:
		printf("%d", calculate(in1, in2, *(p + 1)));
		break;
	case 2:
		printf("%d", calculate(in1, in2, *(p+ 2)));
		break;
	case 3:
		printf("%d", calculate(in1, in2, *(p + 3)));
		break;
	default:
		printf("Incorrect input");
		return 1;
	}



	return 0;
}