#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"format_type.h"

int A[] = { 10,20,30,40,50,60,70,-1 };
int B[] = { 100,200,300,400,500,600,700,800,-1 };
int C[] = { 1000,2000,3000,4000,5000,6000,7000,8000,9000,-1 };
int* D[] = { A, B, C, NULL };


struct statistic_t
{
  int min;
  int max;
  float avg;
  float standard_deviation;
  int range;
};

int statistics(int **ptr, struct statistic_t **stats);
void display(int **ptr);
int save(const char *filename, int **ptr, enum save_format_t format);

int main()
{
	display(D);
	char *sauce;
	if (!(sauce = malloc(40)))
	{
		printf("Failed to allocate moemory");
		return 1;
	}
	printf("Podaj zrodlo: ");
	scanf("%39s", sauce);

	char *txt, *bin;
	if ((!(txt = malloc(45))) || (!(bin = malloc(45))))
	{
		printf("Failed to allocate memory");
		return 1;
	}
	strcpy(txt, sauce);
	strcat(txt, ".txt");
	strcpy(bin, sauce);
	strcat(bin, ".bin");

	if (save(txt, D, fmt_text) || save(bin, D, fmt_binary))
	{
		printf("Couldn't create files");
		return 1;
	}

	struct statistic_t *c;
	statistics(D, &c);
	printf("%d\n%d\n%d\n%f\n%f", c->min, c->max, c->range, c->avg, c->standard_deviation);


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
			//printf("Couldn’t create files");
			return 1;
		}

		int i = 0, j = 0;
		while (*(ptr + i))
		{
			for (j = 0; *(*(ptr + i) + j) != -1; j++)
			{
				fprintf(fp, "%d ", *(*(ptr + i) + j));
			}
			fprintf(fp, "\n");
			i++;
		}		
	}
	else if (format == fmt_binary)
	{
		if (!(fp = fopen(filename, "wb")))
		{
			//printf("Couldn’t create files");
			return 1;
		}
		int j = 0;
		for (int i = 0; *(ptr + i); i++) {
			j = 0;
			do {
				fwrite((*(ptr + i) + j), sizeof(int), 1, fp);
			} while (*(*(ptr + i) + j++) != -1);
		}
	}
	
	fclose(fp);
	return 0;
}

int statistics(int **ptr, struct statistic_t **stats)
{
	if (!ptr || !stats)
		return 1;

	if (!(*stats = malloc(sizeof(struct statistic_t))))
		return 2;

	int min, max,
	sum = 0, counter = 0;
	int started = 0;

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

			sum += *(*(ptr + i) + j);
			counter++;
		}
	}

	(*stats)->min = min;
	(*stats)->max = max;
	(*stats)->avg = (float)sum / (float)counter;
	(*stats)->range = max - min;
	float dev_sum = 0.0;
	for (int i = 0; *(ptr + i); i++) {
		for (int j = 0; *(*(ptr + i) + j) != -1; j++) {
			dev_sum += ((float)*(*(ptr + i) + j) - (*stats)->avg) * ((float)*(*(ptr + i) + j) - (*stats)->avg);
		}
	}

	(*stats)->standard_deviation = sqrtf(dev_sum / counter);

	return 0;
}