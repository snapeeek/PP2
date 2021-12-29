#include<stdio.h>
#include<stdlib.h>

float* create_array(int N)
{
	if (N <= 0)
		return NULL;

	float *tab;
	tab = (float*)malloc(N * sizeof(float));
	
	return tab;
}

int main()
{
	srand(rand());
	int size;
	float *tab;
	printf("Podaj ilosc danych: ");
	scanf("%d", &size);

	tab = create_array(size);
	if (!tab)
	{
		printf("Error");
		return 1;
	}

	for (int i = 0; i < size; i++)
	{
		*(tab + i) = (float)(((float)(rand() % 200001) / 10000) - 10);
	}

	for (int i = 0; i < size; i++)
	{
		printf("%f ", *(tab + i));
	}

	free(tab);

	return 0;
}