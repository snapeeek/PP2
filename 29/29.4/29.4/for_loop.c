#include<stdio.h>
#include<stdlib.h>
#include "for_loop.h"

double for_loop(double start, double step, double end, void(*tab)(double)) 
{
	if ((*tab) == NULL || step <= 0 || start > end || (start < 0 && step < 0)) 
		return 1;
	(*tab)(start);
	start = start + step;
	
	if (start < end) 
	{
		for_loop(start, step, end, (*tab));
	}
	
	return 0;
}

void print_value(double input) 
{
	printf("%lf ", input);
}

void print_accumulated(double input) 
{
	static double help;
	help += input;
	printf("%lf ", help);
}

void print_square(double input) 
{
	double help = input * input;
	print_value(help);
}

void print_abs(double input) 
{
	double help;
	if (input < 0) {
		help = input * -1;
		print_value(help);
	}
	else print_value(input);
}