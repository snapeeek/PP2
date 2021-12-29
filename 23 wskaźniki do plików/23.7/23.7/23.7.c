#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int ile, i = 0; float ilef;
	printf("Podaj ile liczb chcesz wylosowac: ");
	scanf("%d", &ile);
	ilef = (float)ile / 10;
	if (ilef > (ile / 10))
		ile = (ile / 10) + 1;
	else
		ile = ile / 10;
	FILE *f;
	while (i <= ile)
	{
		f = fopen()








	}


	return 0;
}
