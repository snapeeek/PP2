#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct complex_t
{
	float re;
	float im;
};

struct complex_t* set(struct complex_t* cp, float re, float im, int *err_code)
{
	if (cp == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return NULL;
	}

	cp->re = re;
	cp->im = im;
	if (err_code != NULL)
		*err_code = 0;

	return cp;
}

void show(const struct complex_t* cp)
{
	if (cp != NULL)
	{
		if (cp->re != 0)
			printf("%.2f", cp->re);
		if (cp->im < 0)
		{
			printf(" - i%.2f", -cp->im);
		}
		else if (cp->im > 0)
		{
			printf(" + i%.2f", cp->im);
		}
		printf("\n");
	}
}

float complex_abs(struct complex_t* cp, int * err_code)
{
	if (cp == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return -1;
	}
	else
	{
		float mod;
		mod = (float)sqrt(((cp->re)*(cp->re)) + ((cp->im)*(cp->im)));
		if (err_code != NULL)
			*err_code = 0;
		return mod;
	}
}

int main()
{
	srand(rand());
	struct complex_t karta1, karta2, *p1, *p2;
	p1 = &karta1; p2 = &karta2;
	int error = 0, *err;
	err = &error;
	
	p1 = set(p1, (float)((rand() % 11) + ((float)(rand() % 101) / (float)100)), (float)((rand() % 11) + ((float)(rand() % 101) / (float)100)), err);
	p2 = set(p2, (float)((rand() % 11) + ((float)(rand() % 101) / (float)100)), (float)((rand() % 11) + ((float)(rand() % 101) / (float)100)), err);
	
	show(p1);
	show(p2);
	if (complex_abs(p1, err) > complex_abs(p2, err))
		show(p1);
	else if (complex_abs(p1, err) < complex_abs(p2, err))
		show(p2);
	else
	{
		show(p1);
		show(p2);
	}





	return 0;
}