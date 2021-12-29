#include<stdio.h>
#include<stdlib.h>

int tab_min(const int* tab, int size, int *min)
{
	int i = 0;
	if ((tab == NULL) || (min == NULL) || (size < 0))
		return 0;

	while (i < size)
	{
		if (i == 0)
			*min = *tab;
		else
		{
			if (*(tab + i) < *min)
				*min = *(tab + i);
		}
		i++;
	}
	return 1;
}

int main()
{
	int size, input, tab[100], min, *p;
	printf("Ile chcesz wprowadzic elementow? ");
	scanf("%d", &size);
	printf("Wprowadz liczby: ");
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &input);
		*(tab + i) = input;
	}

	p = &min;
	tab_min(tab, size, p);
	printf("Min: %d\n", *p);





	return 0;
}