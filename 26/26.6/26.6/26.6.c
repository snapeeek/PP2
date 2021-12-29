#include<stdio.h>
#include<stdlib.h>

struct array_t {
	int *ptr;
	int size;
	int capacity;
};

int create(struct array_t *a, int N);
int add(struct array_t *a, int value);
void display(const struct array_t *a);
void destroy(struct array_t *a);

int main()
{
	int input, choice, err = 0;
	printf("Podaj ile elementow: ");
	scanf("%d", &choice);

	struct array_t a;
	if (create(&a, choice) != 0)
	{
		printf("Failed to allocate memory");
		return 1;
	}

	printf("Podaj liczby: ");
	scanf("%d", &input);
	while (input != 0)
	{
		if (add(&a, input) != 0)
			err = 1;
		scanf("%d", &input);
	}
	if (err == 1)
		printf("Error\n");

	if (a.size == 0)
		printf("Buffer is empty");
	else
		display(&a);

	destroy(&a);
	return 0;
}

int create(struct array_t *a, int N) 
{
	if (!a || N <= 0)
		return 1;

	if (!(a->ptr = malloc(N * sizeof(int))))
		return 2;

	a->capacity = N;
	a->size = 0;

	return 0;
}

int add(struct array_t *a, int value)
{
	if (!a || !a->ptr || a->size > a->capacity || a->size < 0 || a->capacity <= 0)
		return 1;

	if (a->size == a->capacity)
		return 2;
	else
	{
		*(a->ptr + a->size) = value;
		a->size++;
	}
	return 0;
}

void display(const struct array_t *a)
{
	if (a)
	{
		if (a->ptr && a->size >= 0 && a->capacity > 0 && a->size <= a->capacity)
		{
			for (int i = 0; i < a->size; i++)
			{
				printf("%d ", *(a->ptr + i));
			}
		}
	}
}

void destroy(struct array_t *a)
{
	if (a)
	{
		free(a->ptr);
	}
}