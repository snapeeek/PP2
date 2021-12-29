#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct matrix_t {
	int **ptr;
	int width;
	int height;
};

int create(struct matrix_t *m, int width, int height);
void destroy(struct matrix_t *m);
void display(const struct matrix_t *m);
int read(struct matrix_t *m);

int main()
{
	struct matrix_t m;
		
	int width, height;
	printf("Podaj wymiary: ");
	scanf("%d", &width);
	scanf("%d", &height);
	
	if (create(&m, width, height) != 0)
	{
		printf("Failed to allocate memory");
		return 1;
	}

	read(&m);
	display(&m);
	destroy(&m);
		
	return 0;
}




int create(struct matrix_t *m, int width, int height)
{
	if (width <= 0 || height <= 0 || !m)
		return 1;	
	
	m->width = width;
	m->height = height;

	if (!(m->ptr = (int**)malloc(m->height * sizeof(int*))))
	{
		return 2;
	}

	for (int i = 0; i < m->height; i++)
	{
		if  (!(*(m->ptr + i) = (int*)malloc(m->width * sizeof(int))))
		{
			
			for (int j = 0; j < i; j++)
			{
				free((*(m->ptr + j)));
			}
			free(m->ptr);			
			return 2;
		}
	}
	
	return 0;
}

void destroy(struct matrix_t *m)
{
	if (m && m->width > 0 && m->height > 0)
	{
		if (m->ptr != NULL)
		{
			
			for (int i = 0; i < m->height; i++)
				free(*(m->ptr + i));
			
			free(m->ptr);
		}
	}
}


void display(const struct matrix_t *m)
{
	if (m && m->ptr && m->width > 0 && m->height > 0)
	{
		for (int i = 0; i < m->height; i++)
		{
			for (int j = 0; j < m->width; j++)
			{
				printf("%d ", *(*(m->ptr + i) + j));
			}
			printf("\n");
		}
	}
}

int read(struct matrix_t *m)
{
	if (!m || !(m->ptr) || (m->width) <= 0 || (m->height) <= 0)
		return 1;

	printf("Podaj liczby:");
	for (int i = 0; i < m->height; i++)
	{
		for (int j = 0; j < m->width; j++)
		{
			scanf("%d", (*(m->ptr + i) + j));
		}
	}

	return 0;
}