#include<stdio.h>
#include<stdlib.h>
#include"for_loop.h"

int main() 
{
	void(*tab[4])(double) = { print_value, print_accumulated, print_square, print_abs };
	
	double start, step, end;
	int choice;
	
	printf("Start, step, end: ");
	scanf("%lf %lf %lf", &start, &step, &end);
	
	if (step <= 0 || start > end) 
	{
		printf("Incorrect input");
		return 1;
	}
	
	printf("Podaj rodzaj operacji:");
	scanf("%d", &choice);
	
	switch (choice)
	{
	case 0: 
		for_loop(start, step, end, (*(tab)));
		break;
	case 1: 
		for_loop(start, step, end, (*(tab + 1)));
		break;
	case 2: 
		for_loop(start, step, end, (*(tab + 2)));
		break;
	case 3:
		for_loop(start, step, end, (*(tab + 3)));
		break;
	default:
		printf("Incorrect input");
		return 1;
	}
	
	return 0;
}