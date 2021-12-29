#include<stdio.h>
#include"int_operations.h"

int(*get_function(enum operations_t type))(int,int)
{
	if (type < 0 || type > 3)
		return NULL;
	
	int(*funcs[4])(int, int);
	*(funcs + 0) = add_int;
	*(funcs + 1) = sub_int;
	*(funcs + 2) = div_int;
	*(funcs + 3) = mul_int;

	if (type == 0)
		return *(funcs + 0);
	else if (type == 1)
		return *(funcs + 1);
	else if (type == 2)
		return *(funcs + 2);
	else if (type == 3)
		return *(funcs + 3);

	return NULL;
}
int add_int(int a, int b)
{
	return a + b;
}
int sub_int(int a, int b)
{
	return a - b;
}
int div_int(int a, int b)
{
	if (b == 0)
		return 0;
	else
		return a / b;
}
int mul_int(int a, int b)
{
	return a * b;
}