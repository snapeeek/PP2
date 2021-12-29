#include<stdio.h>
#include<stdlib.h>

int **create_array_2d(int width, int height);
void display_array_2d(int **ptr, int width, int height);
int read_array_2d(int **ptr, int width, int height);

int main()
{
	int width, height;
	int **tab;

	printf("Podaj: ");
	scanf("%d", &width);
	scanf("%d", &height);

	if (width <= 0 || height <= 0)
	{
		printf("incorrect input");
		return 1;
	}

	tab = create_array_2d(width, height);
	if (!tab)
	{
		printf("Failed to allocate memory");
		return 1;
	}

	read_array_2d(tab, width, height);
	display_array_2d(tab, width, height);


	for (int i = 0; i < height; i++)
		free(*(tab + i));
	free(tab);

	return 0;
}

int **create_array_2d(int width, int height)
{
	if (width <= 0 || height <= 0)
		return NULL;
	
	int **tab;
	tab = (int**)malloc(height * sizeof(int*));
	if (!tab)
		return NULL;
	
	for (int i = 0; i < height; i++)
	{
		*(tab + i) = (int*)malloc(width * sizeof(int*));
		if (!*(tab + i))
		{
			for (int j = 0; j < i; j++)
				free(*(tab + j));
			free(tab);
			return NULL;
		}
		
	}
	return tab;
}

void display_array_2d(int **ptr, int width, int height)
{
	
	if (ptr && width > 0 && height > 0)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
					printf("%d ", *(*(ptr + i) + j));
			}
			printf("\n");
		}
	}
}

int read_array_2d(int **ptr, int width, int height)
{
	if (!ptr || width <= 0 || height <= 0)
		return 1;
	
	printf("Podaj liczby:");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			scanf("%d", (*(ptr + i) + j));
		}
	}
	
	return 0;
}