#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct circular_buffer_t {
	int *ptr;
	int begin;
	int end;
	int capacity;
	unsigned char full : 1;
} structure;

void destroy(struct circular_buffer_t *cb)
{
	if (cb)
	{
		free(cb->ptr);
	}
}

void destroy_circular_buffer(struct circular_buffer_t **cb)
{
	if (cb)
	{
		destroy(*cb);
		free(*cb);
	}
}

int create(struct circular_buffer_t *cb, int N)
{
	if ((!cb) || (N < 1))
		return 1;
	
	if (!(cb->ptr = (int*)malloc(N * sizeof(int)))) {
		return 2;
	}
	
	
		cb->begin = 0;
		cb->end = 0;
		cb->capacity = N;
		cb->full = 0;
	
	return 0;
}

int create_circular_buffer(struct circular_buffer_t **cb, int N)
{
	if ((!cb) || (N < 1))
		return 1;

	if (!(*cb = (struct circular_buffer_t*)malloc(sizeof(struct circular_buffer_t))))
	{
		return 2;
	}

	if (create(*cb, N) != 0) 
	{
		destroy_circular_buffer(cb);
		return 2;
	}
	
	(*cb)->begin = 0;
	(*cb)->end = 0;
	(*cb)->full = 0;
	(*cb)->capacity = N;
	
	return 0;
}

int empty(const struct circular_buffer_t *cb)
{
	if (!cb)
		return -1;
	
	if ((cb->begin == cb->end) && (!cb->full))
		return 1;
	else
		return 0;
}

int full(const struct circular_buffer_t *cb)
{
	if (!cb)
		return -1;
	if (cb->full == 1)
		return 1;
	else
		return 0;
}

int push_back(struct circular_buffer_t *cb, int value)
{
	 if ((!cb) || (!cb->ptr)  || (cb->begin >= cb->capacity) || (cb->begin < 0)  || (cb->end < 0) || (cb->capacity < 1) || (cb->end >= cb->capacity))
		 return 1;
	
	 *(cb->ptr + cb->end) = value;		 

	 if (cb->full)
	 {
		 if (cb->begin == cb->capacity - 1)
			 cb->begin = 0;
		 else
			 cb->begin++;
	 }
	 
	 if (cb->end == cb->capacity - 1)
	 {
		 cb->end = 0;
		 if (cb->begin == cb->end)
			 cb->full = 1;
	 }
	 else
	 {
		 cb->end++;
		 if (cb->begin == cb->end)
			 cb->full = 1;
	 }
	 return 0;
}

int pop_front(struct circular_buffer_t *cb, int *err_code)
{
	if ((!cb) || (cb->begin < 0) || (cb->end < 0) || (cb->capacity < 0) || (cb->begin >= cb->capacity) || (cb->end >= cb->capacity) || (!cb->ptr))
	{
		if (err_code)
			*err_code = 1;
		return 0;
	}
	
	if (empty(cb))
	{
		if (err_code)
			*err_code = 2;
		return 0;
	}

	if (err_code)
	{
		*err_code = 0;
	}

	int zmienna;
	zmienna = *(cb->ptr + cb->begin);
	
	
	if (cb->begin < cb->capacity - 1)
		cb->begin++;
	else
		cb->begin = 0;
	
	if (full(cb))
		cb->full = 0;

	
	return zmienna;
}

int pop_back(struct circular_buffer_t *cb, int *err_code)
{
	if ((!cb) || (cb->begin < 0) || (cb->end < 0) || (cb->capacity < 0) || (cb->begin >= cb->capacity) || (cb->end >= cb->capacity) || (!cb->ptr))
	{
		if (err_code)
			*err_code = 1;
		return 0;
	}

	if (empty(cb))
	{
		if (err_code)
			*err_code = 2;
		return 0;
	}

	if (err_code)
	{
		*err_code = 0;
	}

	int zmienna;
	
	if (cb->end > 0)
		zmienna = *(cb->ptr + cb->end - 1);
	else
		zmienna = *(cb->ptr + cb->capacity - 1);
	
	if (cb->end > 0)
		cb->end--;
	else
		cb->end = cb->capacity - 1;
	
	if (full(cb))
		cb->full = 0;


	return zmienna;
}

void display(const struct circular_buffer_t *cb)
{
	if ((cb) && !((cb->begin < 0) || (cb->end < 0) || (cb->capacity < 0) || (cb->begin >= cb->capacity) || (cb->end >= cb->capacity) || (!cb->ptr)) && (!empty(cb))) {
		int start = 0;
		for (int i = cb->begin; i != cb->end || !start; i = (i + 1) % cb->capacity) {
			printf("%d ", *(cb->ptr + i));
			start = 1;
		}
		printf("\n");
	}
}

int main()
{
	struct circular_buffer_t *p;
	p = &structure;
	

	int *err, error = 0;
	err = &error;

	int input;
	
	printf("Podaj pojemnosc bufora: ");
	scanf("%d", &input);
	
	switch (create_circular_buffer(&p, input))
	{
	case 1:
		printf("Error");
		return 1;

	case 2:
		printf("Failed to allocate memory");
		return 2;
	}


	int choice;
	printf("Co chcesz zrobic? ");
	scanf("%d", &choice);
	int help = 0;
	
	while (choice != 0)
	{
		switch (choice)
		{
		case 1:
			
			printf("Podaj liczbe, ktora chcesz pyknac na koniec: ");
			scanf("%d", &help);
			push_back(p, help);		
			break;
		case 2:
			if (!empty(p))
				printf("%d\n", pop_back(p, err));
			else
				printf("Buffer is empty\n");
			break;
		case 3:
			if (!empty(p))
				printf("%d\n", pop_front(p, err));
			else
				printf("Buffer is empty\n");
			break;
		case 4:
			if (!empty(p))
				display(p);
			else
				printf("Buffer is empty\n");
			break;
		case 5:
			if (empty(p))
				printf("1\n");
			else
				printf("0\n");
			break;
		case 6:
			if (full(p))
				printf("1\n");
			else
				printf("0\n");
			break;
		default:
			printf("Incorrect input\n");
		}
		printf("Co dalej? ");
		scanf("%d", &choice);
	}

	
	destroy_circular_buffer(&p);

	return 0;
}