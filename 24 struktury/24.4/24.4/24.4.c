#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>



struct point_t
{
	int x;
	int y;
};

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

void show(const struct point_t* p)
{
	if (p == NULL)
	{
		printf("Error");
	}
	else {
		printf("x = %d ", p->x);
		printf("y = %d", p->y);
		printf("\n");
	}
}

struct point_t* set(struct point_t* p, int x, int y)
{
	if (p == NULL)
		return NULL;

	p->x = x;
	p->y = y;
	return p;
}

int save_point_t(const char *filename, const struct point_t* p)
{
	if ((filename == NULL) || (p == NULL))
		return 0;
	FILE *fp;
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		return 0;
	}
	fprintf(fp, "%d %d", p->x, p->y);
	fclose(fp);
	printf("File saved\n");
	return 1;
}

int load_point_t(const char *filename, struct point_t* p)
{
	if ((filename == NULL) || (p == NULL))
	{
		return 0;
	}

	FILE *fp;

	if ((fp = fopen(filename, "r")) == NULL) 
	{
		return 0;
	}

	if (!fscanf(fp, "%d", &(p->x)) || !fscanf(fp, "%d", &(p->y))) {
		fclose(fp);
		return 0;
	}

	fclose(fp);

	return 1;
}

int save_point_b(const char *filename, const struct point_t* p)
{
	if ((filename == NULL) || (p == NULL))
	{
		return 0;
	}

	FILE *fp;
	if ((fp = fopen(filename, "wb")) == NULL) 
	{
		return 0;
	}

	if (!fwrite(p, sizeof *p, 1, fp)) {
		fclose(fp);
		return 0;
	}

	fclose(fp);
	printf("File saved\n");
	return 1;
}

int load_point_b(const char *filename, struct point_t* p)
{
	if ((filename == NULL) || (p == NULL))
	{
		return 0;
	}

	FILE *f;

	if ((f = fopen(filename, "rb")) == NULL) 
	{
		return 0;
	}

	if (!fread(p, sizeof *p, 1, f)) {
		fclose(f);
		return 0;
	}

	fclose(f);

	return 1;
}

int main()
{

	struct point_t k, *p;
	char sauce[50], ch;
	int type = 0;
	

	
	p = &k;

	p = set(p, rand() % 500, rand() % 500);
	show(p);
	printf("Podaj sciezke pliku: ");
	scanf("%49s", sauce);
	
	if (strstr(sauce, ".txt"))
	{
		if (!save_point_t(sauce, p))
		{
			printf("Couldn't create file");
			return 1;
		}
		type = 1;
	}
	else if (strstr(sauce, ".bin"))
	{
		if (!save_point_b(sauce, p))
		{
			printf("Couldn't create file");
			return 1;
		}
		type = 2;
	}
	else
	{
		printf("Wrong filename!");
		return 1;
	}
	getchar();
	printf("Czy chcesz wczytac dane z pliku (y/n)? ");
	scanf("%c", &ch);
	if (tolower(ch) == 'y')
	{
		if (type == 1)
		{
			if (!load_point_t(sauce, p))
			{
				printf("File corrupted");
				return 1;
			}
			else
				show(p);
		}
		else if (type == 2)
		{
			if (!load_point_b(sauce, p))
			{
				printf("File corrupted");
				return 1;
			}
			else
				show(p);
		}
	}
	else if ((ch == 'n') || (ch == 'N'))
	{
		return 0;
	}
	else
	{
		printf("Error");
		return 1;
	}
		
}