#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	double *p;
	
	p = (double*)malloc(sizeof(double));
	
	if (!p)
	{
		printf("Error");
		return 1;
	}
	*p = 3.141593;
	printf("%lf ", *p);
	printf("%p", (void*)p);
	
	free(p);
	
	return 0;
}