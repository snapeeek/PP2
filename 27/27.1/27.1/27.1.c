#include<stdio.h>
#include<stdlib.h>



int main(void) {
	
	int wier = 10, col = 10;
	int **tab;


	tab = (int**)malloc(wier * sizeof(int*)); 
	if (tab == NULL)
	{
		printf("Error");
		return 1;
	}
	for (int i = 0; i < wier; i++) 
	{
		*(tab + i) = (int*)malloc(col * sizeof(int));
		if (*(tab + i) == NULL)
		{
			printf("Error");
			for (int j = 0; j < i; j++)
				free(*(tab + j));
			free(tab);
			return 1;
		}
			
	}
												  
	for (int i = 0; i < wier; i++) 
	{
		*(*(tab + i)) = i + 1;
		*(*tab + i) = i + 1;
	}

	for (int i = 1; i < wier; i++)
	{
		for (int j = 1; j < col; j++)
		{
			*(*(tab + i) + j) = (*(*tab + j)) * (*(*(tab + i)));
		}
	}


	
	for (int i = 0; i<wier; i++) 
	{
		for (int j = 0; j<col; j++) 
		{
			if (j == 0)
				printf("%d", *(*(tab + i) + j));
			else
				printf("%4d", *(*(tab + i) + j));
		}
		printf("\n");
	}

	
	for (int i = 0; i<col; i++)
		free(*(tab + i));
	free(tab);

	return 0;
}