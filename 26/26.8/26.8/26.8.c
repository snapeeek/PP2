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
int create_array(struct array_t **a, int N);
void destroy_array(struct array_t **a);
int remove_item(struct array_t *a, int value);

int main()
{
	int input, choice, err = 0;
	printf("Podaj ile elementow: ");
	scanf("%d", &choice);

	struct array_t *a;
	if (create_array(&a, choice) != 0)
	{
		printf("Failed to allocate memory");
		return 1;
	}

	printf("Podaj co chcesz zrobic: ");
	scanf("%d", &choice);
	while (choice != 0)
	{
		switch (choice)
		{
		case 1:
			err = 0;
			printf("Podaj liczby, ktore maja zostac dodane do tablicy: ");
			scanf("%d", &input);
			
			while (input != 0)
			{
				if (add(a, input) != 0)
					err = 1;
				scanf("%d", &input);
			}
			if (err == 1)
				printf("Error\n");
			
			if (a->size > 0)
				display(a);
			else
				printf("Buffer is empty");

			break;
		case 2:
			err = 0;
			printf("Podaj liczby, ktore maja zostac usuniete z tablicy: ");
			scanf("%d", &input);
			
			while (input != 0)
			{
				if (remove_item(a, input) == -1)
					err = 2;
				scanf("%d", &input);
			}
			
			if (err == 2)
				printf("Error\n");

			if (a->size > 0)
				display(a);
			else
				printf("Buffer is empty");

			break;
		default:
			printf("Incorrect input");
			break;
		}
		printf("\nCo dalej? ");
		scanf("%d", &choice);
	}

	destroy_array(&a);
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

int create_array(struct array_t **a, int N)
{
	if (!a || N <= 0)
		return 1;

	if (!(*a = malloc(sizeof(struct array_t))))
		return 2;

	switch (create(*a, N))
	{
	case 1:
		free(*a);
		return 1;
	case 2:
		free(*a);
		return 2;
	}

	return 0;
}

void destroy_array(struct array_t **a)
{
	if (a)
	{
		destroy(*a);
		free(*a);
	}
}

int remove_item(struct array_t *a, int value)
{
	if (!a || !a->ptr || a->size > a->capacity || a->size <= 0 || a->capacity <= 0)
		return -1;

	int counter = 0;
	for (int i = a->size; i >= 0; i--)
	{
		if (*(a->ptr + i) == value)
		{
			counter++;
			for (int j = i; j < a->size; j++)
			{
					*(a->ptr + j) = *(a->ptr + j + 1);
			}
			a->size--;
		}
	}
	
	return counter;
}