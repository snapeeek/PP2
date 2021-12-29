#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct point_t
{
	int x;
	int y;
};

struct segment_t
{
	struct point_t start;
	struct point_t end;
};



struct segment_t* read_segment(struct segment_t* p)
{
	if (p == NULL)
		return NULL;
	
	printf("Podaj wspolrzedne pierwszego punktu:\n");
	printf("Podaj wspolrzedna x: ");
	scanf("%d", &p->start.x);
	printf("Podaj wspolrzedna y: ");
	scanf("%d", &p->start.y);
	
	printf("Podaj wspolrzedne drugiego punktu:\n");
	printf("Podaj wspolrzedna x: ");
	scanf("%d", &p->end.x);
	printf("Podaj wspolrzedna y: ");
	scanf("%d", &p->end.y);
	return p;
}

void show_segment(const struct segment_t* p)
{
	if (p != NULL)
	{
		printf("Wspolrzedne poczatku wektora: x = %d, y = %d\n", p->start.x, p->start.y);
		printf("Wspolrzedne konca wektora: x = %d, y = %d", p->end.x, p->end.y);
	}
}

float length(const struct segment_t* s, int *err_code)
{
	
	if ((s == NULL))
	{
		if (err_code != NULL)
			*err_code = 1;
		return -1;
	}
	if (err_code != NULL)
	{
		*err_code = 0;
	}
	
	float dlugosc;
	float rozx, rozy;
	rozx = (float)s->end.x - (float)s->start.x;
	rozy = (float)s->end.y - (float)s->start.y;
	dlugosc = (float)hypot(rozx, rozy);

	return dlugosc;
}

int main()
{
	struct segment_t *p, karta;
	int error = 0, *err;
	float dlug;
	err = &error;
	p = &karta;
	if (read_segment(p) == NULL)
	{
		printf("Error");
		return 1;
	}

	show_segment(p);
	dlug = length(p, err);
	printf("\n%.2f", dlug);



	return 0;
}