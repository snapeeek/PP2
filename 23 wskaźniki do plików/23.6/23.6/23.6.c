#include<stdio.h>
#include<stdlib.h>

int main()
{
	int input;
	FILE *f2, *f3, *f5, *f0;
	printf("Podaj liczby, jesli chcesz zakonczyc wprowadz 0: ");
	
	f2 = fopen("2.txt", "w");
	if (f2 == NULL)
	{
		printf("Error");
		return 1;
	}
	
	f3 = fopen("3.txt", "w");
	if (f3 == NULL) 
	{
		printf("Error");
		fclose(f2);
		return 1;
	}
	
	f5 = fopen("5.txt", "w");
	if (f5 == NULL) 
	{
		printf("Error");
		fclose(f2);
		fclose(f3);
		return 1;
	}
	
	f0 = fopen("0.txt", "w");
	if (f0 == NULL)
	{
		printf("Error");
		fclose(f2);
		fclose(f3);
		fclose(f5);
		return 1;
	}
	
	for (;;)
	{
		scanf("%d", &input);
		if (input == 0)
			break;
		if (input % 2 == 0)
		{
			fprintf(f2, "%d\n", input);
		}
		if (input % 3 == 0)
		{
			fprintf(f3, "%d\n", input);
		}
		if (input % 5 == 0)
		{
			fprintf(f5, "%d\n", input);
		}
		if ((input % 2 != 0) && (input % 3 != 0) && (input % 5 != 0))
		{
			fprintf(f0, "%d\n", input);
		}
		
	}
	
	fclose(f2); fclose(f3); fclose(f5); fclose(f0);
	printf("Files saved");




	return 0;
}