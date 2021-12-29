#include<stdio.h>
#include<stdlib.h>
#include"int_operations.h"

int main()
{
	int choice;
	int x, y;
	int res;

	printf("Podaj liczby: ");
	scanf("%d %d", &x, &y);

	printf("Podaj operacje: ");
	scanf("%d", &choice);
	switch (choice)
	{
	case 0:
		res = get_function(op_add)(x, y);
		break;
	case 1:
		res = get_function(op_sub)(x, y);
		break;
	case 2:
		res = get_function(op_div)(x, y);
		break;
	case 3:
		res = get_function(op_mul)(x, y);
		break;
	default:
		printf("Incorrect input");
		return 1;
	}

	printf("%d", res);


	return 0;
}