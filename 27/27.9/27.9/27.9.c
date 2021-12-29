#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct image_t {
	char type[3];
	int **ptr;
	int width;
	int height;
};

//z 27.7
struct image_t* load_image_t(const char *filename, int *err_code);
int save_image_t(const char * filename, const struct image_t *m1);
void destroy_image(struct image_t **m);

//nufka(/-i)
int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty);

int main()
{
	int error, how_many;
	char *first;
	if (!(first = malloc(30)))
	{
		printf("Failed to allocate memory");
		return 4;
	}
	printf("Podaj obraz: ");
	scanf("%29s", first);

	struct image_t *ori;
	if (!(ori = load_image_t(first, &error)))
	{
	switch (error)
	{
	case 1:
		printf("Error");		
		free(first);
		return 1;
	case 2:
		printf("File not found");		
		free(first);
		return 2;
	case 3:
		printf("File corrupted");		
		free(first);
		return 3;
	case 4:
		printf("Failed to allocate memory");
		free(first);
		return 4;
	}
	}


	printf("Podaj ile obrazow chcesz wczytac: ");
	scanf("%d", &how_many);
	if (how_many < 1)
	{
		printf("Incorrect input");
		free(first);
		destroy_image(&ori);
		return 1;
	}
	char *temp;
	for (int i = 0; i < how_many; i++)
	{
		if (!(temp = malloc(30 * sizeof(char))))
		{
			printf("Failed to allocate memory");
			free(first);
			destroy_image(&ori);
			return 4;
		}

		printf("Podaj zrodlo pliku: ");
		scanf("%30s", temp);
		struct image_t *timg;
		if (!(timg = load_image_t(temp, &error)))
		{
			switch (error)
			{
			case 1:
				printf("Error\n");
				free(temp);
				continue;
			case 2:
				printf("File not found\n");
			
				free(temp);
				continue;
			case 3:
				printf("File corrupted\n");				
				free(temp);
				continue;
			case 4:
				printf("Failed to allocate memory\n");
				destroy_image(&ori);
				free(temp);
				free(first);
				return 4;
			}
		}

		int x, y;
		printf("Podaj x i y: ");
		scanf("%d%d", &x, &y);

		if (draw_image(ori, timg, x, y))
		{
			printf("Incorrect input\n");
			destroy_image(&timg);
			free(temp);
			continue;
		}

		free(temp);
		destroy_image(&timg);
	}

	char *output; char *mod;
	mod = malloc(50);
	strcpy(mod, "_modified");
	if (!(output = malloc(50)))
	{
		printf("Failed to allocate memory\n");
		destroy_image(&ori);
		free(mod);
		free(first);
		return 4;
	}
	int i = 0, j = 0;
	for (i = 0; i < (int)strlen(first); i++)
	{
		if (*(first + i) == '.' && *(first + i + 4) == '\0')
		{
			for (j = 0; j < (int)strlen(mod); j++)
			{
				*(output + i + j) = *(mod + j);
			}
		}
		*(output + i + j) = *(first + i);
	}

	*(output + i + j) = '\0';
		
	if (save_image_t(output, ori))
	{
		printf("Couldn't save file\n");
		free(output);
		free(first);
		free(mod);
		destroy_image(&ori);
		return 2;
	}
	printf("File saved\n");

	free(output);	
	free(first);
	free(mod);
	destroy_image(&ori);
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

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty)
{
	if (!img || !src || destx < 0 || desty < 0 || 
		src->height <= 0 || src->width <= 0 || !(src->ptr) || img->height <= 0 || 
		img->width <= 0 || (!img->ptr) || (src->width + destx)>img->width || (src->height + desty)>img->height)
		return 1;


	for (int i = desty, i1 = 0; i1 < src->height; i1++, i++)
	{
		for (int j = destx, j1 = 0; j1 < src->width; j1++, j++)
		{
			*(*(img->ptr + i) + j) = *(*(src->ptr + i1) + j1);
		}
	}
	
	return 0;
}

