#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct image_t {
	char type[3];
	int **ptr;
	int width;
	int height;
};

enum sauce {input, horizo, verti, negat};

//wymagane
struct image_t* image_flip_horizontal(const struct image_t *m1);
struct image_t* image_flip_vertical(const struct image_t *m1);
struct image_t* image_negate(const struct image_t *m1);
struct image_t* load_image_t(const char *filename, int *err_code);
int save_image_t(const char * filename, const struct image_t *m1);
void destroy_image(struct image_t **m);

//moje
void sauce_delloc(char **sauces);
int sauce_alloc(char **sauces);

int main()
{
	int error = 0, *err;
	err = &error;
	struct image_t *s, *hor, *ver, *neg;
	char **sauces;

	if (!(sauces = calloc(sizeof(char*), 5)))
	{
		printf("Failed to allocate memory");
		return 4;
	}

	if (!(*(sauces + input) = malloc(40)))
	{
		printf("Failed to allocate memory");
		sauce_delloc(sauces);
		return 4;
	}
	printf("Podaj zrodlo: ");
	scanf("%39s", *(sauces + input));

	if (sauce_alloc(sauces)) {
		printf("Failed to allocate memory");
		sauce_delloc(sauces);
		return 4;
	}


	if (!(s = load_image_t(*(sauces + input), err))) 
	{
		switch (*err) 
		{
		case 1:
			printf("Error");
			sauce_delloc(sauces);
			return 1;
		case 2:
			printf("File not found");
			sauce_delloc(sauces);
			return 2;
		case 3:
			printf("File corrupted");
			sauce_delloc(sauces);
			return 3;
		case 4:
			printf("Failed to allocate memory");
			sauce_delloc(sauces);
			return 4;
		}
	}
	
	if (!(neg = image_negate(s))) 
	{
		printf("Failed to allocate memory");
		destroy_image(&s);
		sauce_delloc(sauces);
		return 4;
	}

	if (!(hor = image_flip_horizontal(s))) 
	{
		printf("Failed to allocate memory");
		destroy_image(&s);
		destroy_image(&neg);
		sauce_delloc(sauces);
		return 4;
	}

	if (!(ver = image_flip_vertical(s))) 
	{
		printf("Failed to allocate memory");
		destroy_image(&s);
		destroy_image(&neg);
		destroy_image(&hor);
		sauce_delloc(sauces);
		return 4;
	}

	if (save_image_t(*(sauces + verti), ver)) 
	{
		printf("Couldn't create file\n");
	}
	else {
		printf("File saved\n");
	}

	if (save_image_t(*(sauces + horizo), hor)) 
	{
		printf("Couldn't create file\n");
	}
	else {
		printf("File saved\n");
	}

	if (save_image_t(*(sauces + negat), neg)) 
	{
		printf("Couldn't create file\n");
	}
	else {
		printf("File saved\n");
	}

	destroy_image(&s);
	destroy_image(&neg);
	destroy_image(&hor);
	destroy_image(&ver);
	sauce_delloc(sauces);


	return 0;
}

struct image_t* load_image_t(const char *filename, int *err_code)
{
	if (!filename)
	{
		if (err_code)
			*err_code = 1;
		return NULL;
	}

	FILE *fp;

	fp = fopen(filename, "r");
	if (!fp)
	{
		if (err_code)
			*err_code = 2;
		return NULL;
	}

	struct image_t *image;
	image = (struct image_t*)malloc(sizeof(struct image_t));
	if (!image)
	{
		if (err_code)
			*err_code = 4;
		fclose(fp);
		return NULL;
	}

	if (fscanf(fp, "%c%c", image->type, image->type + 1) != 2 || *(image->type) != 'P' || *(image->type + 1) != '2')
	{
		if (err_code)
			*err_code = 3;
		free(image);
		fclose(fp);
		return NULL;
	}

	*(image->type + 2) = '\0';

	if (fscanf(fp, "%d %d", &image->width, &image->height) != 2 || image->height < 1 || image->width < 1)
	{
		if (err_code)
			*err_code = 3;
		free(image);
		fclose(fp);
		return NULL;
	}

	image->ptr = malloc(sizeof(int*) * image->height);
	if (!image->ptr)
	{
		if (err_code)
			*err_code = 4;
		free(image);
		fclose(fp);
		return NULL;
	}

	for (int i = 0; i < image->height; i++)
	{
		*(image->ptr + i) = malloc(image->width * sizeof(int));
		if (!(*(image->ptr + i)))
		{
			if (err_code)
				*err_code = 4;
			for (int j = 0; j < i; j++)
			{
				free(*(image->ptr + j));
			}
			free(image->ptr);
			free(image);	
			fclose(fp);
			return NULL;
		}
	}

	int check;
	if (fscanf(fp, "%d", &check) != 1 || check != 255)
	{
		if (err_code)
			*err_code = 3;
		for (int i = 0; i < image->height; i++)
		{
			free(*(image->ptr + i));
		}
		free(image->ptr);
		free(image);
		fclose(fp);
		return NULL;
	}

	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			if (fscanf(fp, "%d", *(image->ptr + i) + j) != 1 || *(*(image->ptr + i) + j) > 255 || *(*(image->ptr + i) + j) < 0 || feof(fp)) 
			{
				if (err_code) 
				{
					*err_code = 3;
				}
				for (int j = 0; j < image->height; j++) 
				{
					free(*(image->ptr + j));
				}
				free(image->ptr);
				free(image);
				fclose(fp);
				return NULL;
			}
		}
	}

	if (err_code)
	{
		*err_code = 0;
	}
	fclose(fp);
	return image;
}

void destroy_image(struct image_t **m)
{
	if (m) {
		if ((*m)->ptr && (*m)->width > 0 && (*m)->height > 0)
		{
			for (int i = 0; i < (*m)->height; i++) 
			{
				free(*((*m)->ptr + i));
			}
			free((*m)->ptr);
			free(*m);
		}
	}
}

int save_image_t(const char * filename, const struct image_t *m1)
{
	if (!filename || !m1 || !m1->ptr || m1->height < 1 || m1->width < 1)
		return 1;
	
	FILE *fp;
	fp = fopen(filename, "w");
	if (!fp)
		return 2;
	fputs(m1->type, fp);
	fputs("\n", fp);
	fprintf(fp, "%d %d\n", m1->width, m1->height);
	fprintf(fp, "255\n");
	for (int i = 0; i < m1->height; i++)
	{
		for (int j = 0; j < m1->width; j++)
		{
			fprintf(fp, "%d ", *(*(m1->ptr + i) + j));
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
	fclose(fp);
	return 0;
}

struct image_t* image_flip_horizontal(const struct image_t *m1)
{
	if (!m1 || (!(m1->ptr && m1->height > 0 && m1->width > 0)))
		return NULL;
	
	struct image_t *copyhor;
	if (!(copyhor = (struct image_t *)malloc(sizeof(struct image_t))))
	{
		return NULL;
	}
	
	memcpy(copyhor, m1, sizeof(struct image_t));

	if (!(copyhor->ptr = malloc(copyhor->height * sizeof(int *)))) {
		free(copyhor);
		return NULL;
	}

	for (int i = 0; i < m1->height; i++) {
		if (!(*(copyhor->ptr + i) = malloc(m1->width * sizeof(int)))) {
			for (int j = 0; j < i; j++) {
				free(*(copyhor->ptr + j));
			}
			free(copyhor->ptr);
			free(copyhor);
			return NULL;
		}
	}

	int temp;

	for (int i = 0; i < m1->height; i++) 
	{
		for (int j = 0; j < m1->width; j++) 
		{
			temp = *(*(m1->ptr + i) + j);
			*(*(copyhor->ptr + i) + j) = *(*(m1->ptr + m1->height - i - 1) + j);
			*(*(copyhor->ptr + m1->height - i - 1) + j) = temp;
		}
	}

	return copyhor;
}

struct image_t* image_flip_vertical(const struct image_t *m1)
{
	if (!m1 || (!(m1->ptr && m1->height > 0 && m1->width > 0)))
		return NULL;

	struct image_t *copyver;
	if (!(copyver = (struct image_t *)malloc(sizeof(struct image_t))))
	{
		return NULL;
	}

	memcpy(copyver, m1, sizeof(struct image_t));

	if (!(copyver->ptr = malloc(copyver->height * sizeof(int *)))) {
		free(copyver);
		return NULL;
	}

	for (int i = 0; i < m1->height; i++) {
		if (!(*(copyver->ptr + i) = malloc(m1->width * sizeof(int)))) {
			for (int j = 0; j < i; j++) {
				free(*(copyver->ptr + j));
			}
			free(copyver->ptr);
			free(copyver);
			return NULL;
		}
	}

	int temp;

	for (int i = 0; i < m1->height; i++) 
	{
		for (int j = 0; j < m1->width; j++) 
		{
			temp = *(*(m1->ptr + i) + j);
			*(*(copyver->ptr + i) + j) = *(*(m1->ptr + i) + m1->width - j - 1);
			*(*(copyver->ptr + i) + m1->width - j - 1) = temp;
		}
	}

	return copyver;
}

struct image_t* image_negate(const struct image_t *m1)
{
	if (!m1 || (!(m1->ptr && m1->height > 0 && m1->width > 0)))
		return NULL;

	struct image_t *copyneg;
	if (!(copyneg = (struct image_t *)malloc(sizeof(struct image_t))))
	{
		return NULL;
	}

	memcpy(copyneg, m1, sizeof(struct image_t));

	if (!(copyneg->ptr = malloc(copyneg->height * sizeof(int *)))) {
		free(copyneg);
		return NULL;
	}

	for (int i = 0; i < m1->height; i++) {
		if (!(*(copyneg->ptr + i) = malloc(m1->width * sizeof(int)))) {
			for (int j = 0; j < i; j++) {
				free(*(copyneg->ptr + j));
			}
			free(copyneg->ptr);
			free(copyneg);
			return NULL;
		}
	}


	for (int i = 0; i < m1->height; i++)
	{
		for (int j = 0; j < m1->width; j++)
		{			
			*(*(copyneg->ptr + i) + j) = 255 - *(*(m1->ptr + i) + j);
		}
	}

	return copyneg;
}

int sauce_alloc(char **sauces) 
{
	if (!(*(sauces + verti) = malloc(strlen("mirror_v_") + strlen(*(sauces + input)) + 1))) {
		return 1;
	}
	strcpy(*(sauces + verti), "mirror_v_");
	strcat(*(sauces + verti), *(sauces + input));

	if (!(*(sauces + horizo) = malloc(strlen("mirror_h_") + strlen(*(sauces + input)) + 1))) {
		return 1;
	}
	strcpy(*(sauces + horizo), "mirror_h_");
	strcat(*(sauces + horizo), *(sauces + input));

	if (!(*(sauces + negat) = malloc(strlen("invert_") + strlen(*(sauces + input)) + 1))) {
		return 1;
	}
	strcpy(*(sauces + negat), "invert_");
	strcat(*(sauces + negat), *(sauces + input));

	return 0;
}

void sauce_delloc(char **sauces)
{
	int i = 0;
	while (i < 4 && *(sauces + i)  )
	{
		free(*(sauces + i));
		i++;
	}
	free(sauces);
}