#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dictionary.h"

struct dictionary_t* create_dictionary(int N)
{
	if (N <= 0)
		return NULL;

	struct dictionary_t *p;
	if (!(p = malloc(sizeof(struct dictionary_t))))
		return NULL;

	p->capacity = N;
	p->size = 0;
	if (!(p->wc = malloc(N * sizeof(struct word_count_t))))
	{
		free(p);
		return NULL;
	}

	return p;
}

void destroy_dictionary(struct dictionary_t** d)
{
	if (d)
	{
		if ((*d)->wc) 
		{
			for (int i = 0; i < (*d)->size; i++)
			{
				free(((*d)->wc + i)->word);
			}
			free((*d)->wc);
		}
		free(*d);
	}
}

struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word)
{
	if (!d || !word || d->capacity < d->size)
		return NULL;

	int i = 0;	
	
	while(i < d->size)
	{
		if (strcmp(word, (d->wc + i)->word) == 0)
			return (d->wc + i);
		i++;
	}

	return NULL;
}

void dictionary_display(const struct dictionary_t *d)
{
	if (d && d->size >= 0 && d->capacity > 0 && d->size <= d->capacity)
	{
		if (d->wc)
		{
			int i = 0;
			
			while (i < d->size)
			{
				printf("%s %d\n", (d->wc +i)->word, (d->wc + i)->counter);
				i++;
			}
		}
	}
}

int dictionary_add_word(struct dictionary_t *d, const char *word)
{
	if (!d || !d->wc || !word || d->size > d->capacity || d->size < 0 || d->capacity <= 0)
		return 1;		

	struct word_count_t *s, *tmp;
	if (!(s = dictionary_find_word(d, word)))
	{
		if (d->size == d->capacity)
		{
			if (!(tmp = realloc(d->wc, 2 * d->capacity * sizeof(struct word_count_t))))
			{
				return 2;
			}
			else
				d->wc = tmp;
			d->capacity = 2 * d->capacity;
		}

		if (!((d->wc + d->size)->word = malloc((strlen(word) + 1) * sizeof(char))))
		{
			return 2;
		}
		strcpy((d->wc + d->size)->word, word);
		(d->wc + d->size)->counter = 1;
		d->size++;		
	}
	else
	{
		s->counter++;
	}
	
	return 0;
}
