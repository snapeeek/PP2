#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct point_t
{
	int x;
	int y;
};

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code)
{
	if ((p1 == NULL) || (p2 == NULL))
	{
		if (err_code != NULL)
		{
			*err_code = 1;
		}
		return -1;
	}
	else
	{
		if (err_code != NULL)
			*err_code = 0;
	}
	float dist;
	dist = (float)sqrt((((p2->x) - (p1->x))* ((p2->x) - (p1->x))) + (((p2->y) - (p1->y))*((p2->y) - (p1->y))));
	return dist;
}

int main()
{
	FILE *fp;
	struct point_t xy1, xy2, *p1, *p2;
	p1 = &xy1; p2 = &xy2;
	char sauce[50];
	int temp[4];

	printf("Podaj zrodlo pliczku mordzix: ");
	scanf("%49s", sauce);
	fp = fopen(sauce, "r");
	if (fp == NULL)
	{
		printf("Couldn’t open file");
		return 1;
	}
	int counter = 0;
	while ((fp + counter) == EOF)
	{

	}




	return 0;
}