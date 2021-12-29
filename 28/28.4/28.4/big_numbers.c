#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"big_numbers.h"

int validate(const char *number)
{
	if (!number)
		return 2;

	if (strlen(number) > 1 && *number == '0')
		return 1;

	int i = 0;	
	if (*(number) == '-')
		i = 1;
		
	do
	{
		if (*(number + i) > '9' || *(number + i) < '0')
			return 1;
		i++;
	} while (*(number + i) != '\0');
	
	return 0;
}
int create(struct big_numbers_t *bn, int capacity)
{
	if (capacity <= 0 || !bn)
		return 1;
	
	if (!((bn->big_number) = malloc(capacity * sizeof(char*))))
		return 2;
	
	bn->size = 0;
	bn->capacity = capacity;	
	
	return 0;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity)
{

	if (!bn || capacity <= 0)
		return 1;
	
	if (!(*bn = malloc(sizeof(struct big_numbers_t))))
		return 2;
	
	int back;
	back = create(*bn, capacity);
	
	switch (back)
	{
	case 1:
		free(*bn);
		return 1;
	case 2:
		free(*bn);
		return 2;
	}
	
	return 0;

}

void destroy(struct big_numbers_t *bn)
{
	if (bn)
	{
		if (bn->size >= 0)
		{
			if (bn->big_number)
			{
				for (int i = 0; i < bn->size; i++)
				{
					free(*(bn->big_number + i));
				}
				free(bn->big_number);
			}
		}
	}
}

void destroy_big_numbers(struct big_numbers_t **bn)
{
	if (bn)
	{
		if (*bn)
		{
			destroy(*bn);
			free(*bn);
		}
	}
}

int add_big_number(struct big_numbers_t *bn, const char *big_number)
{
	if (!bn || !bn->big_number)
		return 1;
	
	if (validate(big_number) != 0)
		return 1;
	
	if (bn->size < 0 || bn->capacity < 1)
		return 1;
	
	if (bn->size == bn->capacity)
		return 3;
	
	int help;
	help = bn->size;
	if (!(*(bn->big_number + help) = malloc(strlen(big_number) + 1)))
		return 2;
	
	bn->size = bn->size + 1;
	strcpy(*(bn->big_number + help), big_number);

	return 0;
}

void display(const struct big_numbers_t *bn)
{
	if (bn)
	{
		if (bn->big_number)
		{
			if ( bn->capacity > 0 && bn->size > 0 && bn->size <= bn->capacity)
			{
				for (int i = 0; i < bn->size; i++)
					printf("%s\n", *(bn->big_number + i));
			}
		}
	}
}