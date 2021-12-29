#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>


struct point_t
{
	int x;
	int y;
};

int save_points_b(const char *filename, const struct point_t* p, unsigned int N)
{
	struct point_t help;
	if ((filename == NULL) || (p == NULL) || (N < (unsigned int)1))
	{
		printf("Error");
		return 0;
	}

	FILE *fp;

	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("Couldn't create file");
		return 0;
	}
	else
	{
		unsigned int i;
		for (i = 0; i < N; i++)
		{
			help = *(p + i);
			fwrite(&(help.x), 4, 1, fp);
			fwrite(&(help.y), 4, 1, fp);
		}
		fclose(fp);
		printf("File saved");
		return 1;
	}
}

struct point_t* read(struct point_t* p)
{
	if (p == NULL)
		return NULL;

	printf("wpisz x: ");
	scanf("%d", &p->x);
	printf("wpisz y: ");
	scanf("%d", &p->y);
	return p;
}


int main()
{
	struct point_t tab[100], temp;
	int counter, x = 0;

	printf("Podaj ilosc punktow: ");
	x = scanf("%d", &counter);

	if ((!x) || (counter < 1))
	{
		printf("Error");
		return 1;
	}

	if (counter > 100)
	{
		counter = counter - (counter % 100);
	}

	int i;
	for (i = 0; i < counter; i++)
	{
		if ((read(&temp)))
		{
			*(tab + i) = temp;
		}
		else
		{
			printf("Error");
			return 1;
		}

	}

	char sauce[100];
	printf("Podaj nazwe pliku: ");
	scanf("%99s", sauce);
	if (!save_points_b(sauce, tab, counter))
	{
		return 1;
	}

	return 0;
}


