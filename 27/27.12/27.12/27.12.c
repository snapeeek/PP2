#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"format_type.h"

struct statistic_t
{
	int min;
	int max;
	float average;
	float standard_deviation;
	int range;
};

//stare, byc moze potrzebne (do checkawdzenia)
int statistics(int **ptr, struct statistic_t **stats);
void display(int **ptr);
int save(const char *filename, int **ptr, enum save_format_t format);

//nufki
int load(const char *filename, int ***ptr, enum save_format_t format);
int statistics_row(int **ptr, struct statistic_t **stats);
void destroy(int ***ptr);

int main()
{
	int **ptr;
	char *sauce;
	struct statistic_t *stats;
	if (!(sauce = malloc(40)))
	{
		printf("Failed to allocate memory");
		return 4;
	}
	printf("Podaj sciezke pliku: ");
	scanf("%39s", sauce);
	
	int err;
	if (strstr(sauce, ".txt") == sauce + strlen(sauce) - 4)
	{
		err = load(sauce, &ptr, fmt_text);
		switch (err)
		{
		case 2:
			printf("Couldn't open file");
			free(sauce);
			return 2;
		case 3:
			printf("File corrupted");
			free(sauce);
			return 3;
		case 4:
			printf("Failed to allocate memory");
			free(sauce);
			return 4;
		}

		err = statistics_row(ptr, &stats);
		if (err == -2)
		{
			printf("Failed to allocate memory");
			destroy(&ptr);
			free(sauce);
			return 4;
		}
		else
			for (int j = 0; j < err; j++)
			{
				printf("%d %d %d %.2f %.2f\n", (stats + j)->min, (stats + j)->max, (stats + j)->range, (stats + j)->average, (stats + j)->standard_deviation);
			}
	}
	else if (strstr(sauce, ".bin") == sauce + strlen(sauce) - 4)
	{
		err = load(sauce, &ptr, fmt_binary);
		switch (err)
		{
		case 2:
			printf("Couldn't open file");
			free(sauce);
			return 2;
		case 3:
			printf("File corrupted");
			free(sauce);
			
			return 3;
		case 4:
			printf("Failed to allocate memory");
			free(sauce);
			
			return 4;
		}

		err = statistics_row(ptr, &stats);
		if (err == -2)
		{
			printf("Failed to allocate memory");
			destroy(&ptr);
			free(sauce);
			return 4;
		}
		else
			for (int j = 0; j < err; j++)
			{
				printf("%d %d %d %.2f %.2f\n", (stats + j)->min, (stats + j)->max, (stats + j)->range, (stats + j)->average, (stats + j)->standard_deviation);
			}
	}
	else
	{
		printf("Wrong filename");
		free(sauce);
		return 1;
	}

	destroy(&ptr);
	free(stats);
	free(sauce);
	return 0;
}

void display(int **ptr)
{
	int i = 0, j = 0;
	if (ptr)
	{
		while (*(ptr + i))
		{
			for (j = 0; *(*(ptr + i) + j) != -1; j++)
				printf("%d ", *(*(ptr + i) + j));
			printf("\n");
			i++;
		}
	}
}

int save(const char *filename, int **ptr, enum save_format_t format)
{
	if (!filename || !ptr)
	{
		//printf("Incorrect input");
		return 1;
	}
	FILE *fp;
	if (format == fmt_text)
	{
		if (!(fp = fopen(filename, "w")))
		{
			return 2;
		}

		int i = 0, j = 0;
		while (*(ptr + i))
		{
			for (j = 0; *(*(ptr + i) + j) != -1; j++)
			{
				fprintf(fp, "%d ", *(*(ptr + i) + j));
			}

			fprintf(fp, "-1\n");
			i++;
		}
		fclose(fp);
	}
	else if (format == fmt_binary)
	{
		if (!(fp = fopen(filename, "wb")))
		{
			//printf("CouldnÂt create files");
			return 2;
		}
		int j = 0;
		for (int i = 0; *(ptr + i); i++) {
			j = 0;
			do {
				fwrite((*(ptr + i) + j), sizeof(int), 1, fp);
			} while (*(*(ptr + i) + j++) != -1);
		}
		fclose(fp);
	}
	else
		return 1;


	return 0;
}

int statistics(int **ptr, struct statistic_t **stats)
{
	if (!ptr || !stats)
		return 1;

	int min, max, sum = 0, counter = 0, started = 0;

	for (int i = 0; *(ptr + i); i++)
	{
		for (int j = 0; *(*(ptr + i) + j) != -1; j++)
		{
			if (!started)
			{
				min = max = *(*(ptr + i) + j);
				started = 1;
			}

			if (*(*(ptr + i) + j) < min)
			{
				min = *(*(ptr + i) + j);
			}
			else if (*(*(ptr + i) + j) > max)
			{
				max = *(*(ptr + i) + j);
			}

			sum = sum + *(*(ptr + i) + j);
			counter++;
		}
	}

	if (!started)
		return 3;

	if (!(*stats = malloc(sizeof(struct statistic_t))))
		return 2;

	(*stats)->min = min;
	(*stats)->max = max;
	(*stats)->average = (float)sum / (float)counter;
	(*stats)->range = max - min;
	
	float deviation_sum = 0.0;
	for (int i = 0; *(ptr + i); i++) 
	{
		for (int j = 0; *(*(ptr + i) + j) != -1; j++) 
		{
			deviation_sum = deviation_sum + ((float)*(*(ptr + i) + j) - (*stats)->average) * ((float)*(*(ptr + i) + j) - (*stats)->average);
		}
	}

	(*stats)->standard_deviation = sqrtf(deviation_sum / counter);

	return 0;
}

int load(const char *filename, int ***ptr, enum save_format_t format)
{
	if (filename == NULL || ptr == NULL) return 1;

	if (format == fmt_text)
	{
		int check = 0;
		
		FILE *fp;
		if (!(fp = fopen(filename, "r")))
			return 2;
		
		int counter = 0, num;

		if (fscanf(fp, "%d", &check) != 1)
		{
			fclose(fp);
			return 3;
		}
		fseek(fp, 0, SEEK_SET);

		for (int i = 0; feof(fp) == 0; i++)
		{
			num = 0;
			fscanf(fp, "%d", &num);
			
			if (num == -1) 
				counter++;
		}
		
		fseek(fp, 0, SEEK_SET);
		
		if (!(*ptr = (int**)malloc(sizeof(int*) * (counter + 1))))
		{
			fclose(fp);
			return 4;
		}

		for (int i = 0; i < counter; i++)
		{
			for (int j = 0;; j++)
			{
				num = 0;
				check = fscanf(fp, "%d", &num);
				
				if (check != 1)
				{
					for (int j = 0; j <= i; j++)
						free(*((*ptr) + j));
					free(*ptr);
					fclose(fp);
					return 3;
				}
				if (num == -1)
				{
					if (!(*((*ptr) + i) = (int*)malloc(sizeof(int)*(j + 1))))
					{
						for (int j = 0; j <= i; j++)
							free(*((*ptr) + j));
						free(*ptr);
						fclose(fp);
						return 4;
					}
					break;
				}
			}
		}
		
		fseek(fp, 0, SEEK_SET);
		for (int i = 0; i < counter; i++)
		{
			for (int j = 0;; j++)
			{
				check = fscanf(fp, "%d", &num);
				if (check == 1) *(*((*ptr) + i) + j) = num;
				else
				{
					for (int k = 0; k < i; i++)
						free(*((*ptr) + k));
					free((*ptr));
					fclose(fp);
					return 3;
				}
				
				if (num == -1) 
					break;
			}
			
		}
		
		(*((*ptr) + counter)) = NULL;
		fclose(fp);
	}
	else if (format == fmt_binary)
	{
		
		FILE *fp;
		if (!(fp = fopen(filename, "rb")))
			return 2;
		
		int counter = 0, num, check = 0;

		if (fread(&check, sizeof(int), 1, fp) != 1)
		{
			fclose(fp);
			return 3;
		}

		fseek(fp, 0, SEEK_SET);
		
		for (int i = 0; feof(fp) == 0; i++)
		{
			num = 0;
			fread(&num, sizeof(int), 1, fp);
			
			if (num == -1) 
				counter++;
		}
		
		fseek(fp, 0, SEEK_SET);
		if (!(*ptr = (int**)malloc(sizeof(int*) * (counter + 1))))
		{
			fclose(fp);
			return 4;
		}

		for (int i = 0; i < counter; i++)
		{
			for (int j = 0;; j++)
			{
				num = 0;
				check = fread(&num, sizeof(int), 1, fp);
				
				if (check != 1)
				{
					for (int j = 0; j <= i; j++)
						free(*((*ptr) + j));
					free(*ptr);
					fclose(fp);
					return 3;
				}
				if (num == -1)
				{
					
					
					if (!(*((*ptr) + i) = (int*)malloc(sizeof(int)*(j + 1))))
					{
						for (int j = 0; j <= i; j++)
							free(*((*ptr) + j));
						free(*ptr);
						fclose(fp);
						return 4;
					}
					break;
				}
			}
		}
		
		fseek(fp, 0, SEEK_SET);
		for (int i = 0; i < counter; i++)
		{
			for (int j = 0;; j++)
			{
				check = fread(&num, sizeof(int), 1, fp);
				if (check == 1) 
					*(*((*ptr) + i) + j) = num;
				else
				{
					for (int k = 0; k < i; k++)
						free(*((*ptr) + k));
					free((*ptr));
					fclose(fp);
					return 3;
				}
				
				if (num == -1) 
					break;
			}
			
		}
	
		(*((*ptr) + counter)) = NULL;
		fclose(fp);
	}
	else 
		return 1;	
	
	return 0;
}

int statistics_row(int **ptr, struct statistic_t **stats)
{
	if (ptr == NULL || stats == NULL) return -1;

	int rows = 0;
	for (int i = 0; *(ptr + i) != NULL; i++)
	{
		rows++;		
	}

	if (!(*stats = (struct statistic_t*)malloc(sizeof(struct statistic_t)*rows)))
		return -2;
	
	float min, max, average, deviation, range, sum = 0, how_many = 0;

	for (int i = 0; i < rows; i++)
	{
		min = *(*(ptr + i));
		max = *(*(ptr + i));
		average = 0;
		deviation = 0;
		range = 0;
		sum = 0;
		how_many = 0;
		
		for (int j = 0; *(*(ptr + i) + j) != -1; j++)
		{
			sum = sum + *(*(ptr + i) + j);
			if (*(*(ptr + i) + j) > max) 
				max = *(*(ptr + i) + j);
			
			if (*(*(ptr + i) + j) < min) 
				min = *(*(ptr + i) + j);
			
			how_many++;
		}
		
		if (how_many == 0)
		{
			(*stats + i)->average = -1;
			(*stats + i)->max = -1;
			(*stats + i)->min = -1;
			(*stats + i)->range = -1;
			(*stats + i)->standard_deviation = -1;
		}
		else
		{
			average = sum / how_many;
			sum = 0;
			range = max - min;

			for (int j = 0; *(*(ptr + i) + j) != -1; j++)
			{
				sum = sum + (*(*(ptr + i) + j) - average)*(*(*(ptr + i) + j) - average);
			}

			deviation = sqrt(sum / how_many);
			(*stats + i)->average = average;
			(*stats + i)->max = max;
			(*stats + i)->min = min;
			(*stats + i)->range = range;
			(*stats + i)->standard_deviation = deviation;
		}		
	}
	return rows;
}

void destroy(int ***ptr)
{
	for (int i = 0; *((*ptr) + i) != NULL; i++)
	{
		if (*((*ptr) + i) != NULL) 
			free(*((*ptr) + i));
	}	
	free(*ptr);
}