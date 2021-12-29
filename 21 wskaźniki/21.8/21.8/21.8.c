#include<stdio.h>
#include<stdlib.h>

int read_vector(int* tab, int size, int stop_value)
{
	int input, dlug = 0;
	printf("Podaj liczby: ");
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &input);
		if (input != stop_value)
		{
			*tab = input;
			tab++;
			dlug++;
		}
		else break;
	}
	return dlug;
}

void display_vector(const int* tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", *tab);
		tab++;
	}
}

int sort(int* tab, int size)
{
	int temp, zmiana;
	if (tab != NULL) 
	{
		do {
			zmiana = 0;
			for (int i = 0; i < size - 1; i++)
			{
				if (i == size - 1)
					break;

				if (*(tab + i) > *(tab + i + 1))

				{
					temp = *(tab + i);
					*(tab + i) = *(tab + i + 1);
					*(tab + i + 1) = temp;
					zmiana++;
				}
			}
		} while (zmiana > 0);
		return 1;
	}
	else return 0;
}

int main()
{
	int tab[100], size; 

	size = read_vector(tab, 100, -1);
	sort(tab, size);
	display_vector(tab, size);





	return 0;
}
