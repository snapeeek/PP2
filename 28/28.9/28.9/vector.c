#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

int create(struct array_t *a, int N)
{
	if (!a || N < 1) 
	{
		return 1;
	}

	if (!(a->ptr = malloc(sizeof(float) * N))) 
	{
		return 2;
	}

	a->size = 0;
	a->capacity = N;

	return 0;
}

int add(struct array_t *a, float value)
{
	if (!a) 
	{
		return 1;
	}

	if (a->size == a->capacity) 
	{
		return 2;
	}

	*(a->ptr + a->size) = value;
	a->size++;

	return 0;
}

void display(const struct array_t *a)
{
	if (a->size <= a->capacity && a && a->size > 0)
	{
		for (int i = 0; i < a->size; i++) 
		{
			printf("%.2f ", *(a->ptr + i));
		}
		printf("\n");
	}
}

void destroy(struct array_t *a)
{
	if (a && a->ptr) 
	{
		free(a->ptr);
	}
}

void destroy_array(struct array_t **a)
{
	if (a) 
	{
		destroy(*a);
		free(*a);
	}
}

int create_array(struct array_t **a, int N)
{
	if (!a || N < 1) 
	{
		return 1;
	}

	if (!(*a = malloc(sizeof(struct array_t)))) 
	{
		return 2;
	}

	if (!((*a)->ptr = malloc(N* sizeof(float)))) 
	{
		destroy_array(a);
		return 2;
	}

	(*a)->size = 0;
	(*a)->capacity = N;

	return 0;
}

float dot_product(const struct array_t *a, const struct array_t *b)
{
	if (!a || !b ||	a->size > a->capacity || b->size > b->capacity || a->size != b->size || !a->ptr || !b->ptr || a->size < 1 || b->size < 1)
	{
		return -1;
	}

	double res = 0;

	for (int i = 0; i < a->size; i++) {
		res = res + (double)*(a->ptr + i) * *(b->ptr + i);
	}

	return (float)res;
}

float length(const struct array_t *a)
{
	if (!a || !a->ptr || a->size < 1 || a->size > a->capacity) 
	{
		return -1;
	}

	double suma = 0;

	for (int i = 0; i < a->size; i++) 
	{
		suma = suma + (double)*(a->ptr + i) * *(a->ptr + i);
	}

	return (float)sqrt(suma);
}