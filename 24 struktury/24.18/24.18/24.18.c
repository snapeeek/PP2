#include <stdio.h>
#include<stdlib.h>
#include <string.h>

struct file_t
{
	FILE *f;
	int size;
};

int open_file(struct file_t* f, const char *filename)
{
	if ((f == NULL) || (filename == NULL)) 
	{
		return 0;
	}

	FILE *help = fopen(filename, "r+");

	if (help == NULL)
	{
		return 0;
	}

	fseek(help, 0, SEEK_END);
	f->size = ftell(help);
	f->f = help;

	return 1;
}

struct file_t* find_min(const struct file_t* files, int size)
{
	if ((files == NULL) || (size < 1)) 
	{
		return NULL;
	}

	int min_size = files->size;
	int min = 0;

	for (int i = 0; i < size; i++) {
		if ((files + i)->size < min_size) {
			min_size = (files + i)->size;
			min = i;
		}
	}

	return (struct file_t*)files + min;
}

void close_file(struct file_t* f)
{
	if ((f != NULL) && (f->f != NULL))
	{
		fclose(f->f);
	}
}

int main()
{
	char sauce[30];
	struct file_t pliczki[5];
	int counter = 0;
	struct file_t *min;

	printf("Podaj pliki:\n");
	fgets(sauce, 30, stdin);

	while (*sauce != '\n') 
	{
		*(sauce + strlen(sauce) - 1) = '\0';

		if (((counter) < 5) && (open_file(pliczki + counter, sauce))) 
		{
			counter++;
		}

		fgets(sauce, 30, stdin);
	}

	if (counter == 0) 
	{
		printf("Error");
		return 1;
	}

	min = find_min(pliczki, counter);
	char temp;
	int end = 0, choice = 0;

	printf("Wprowadz tekst do zapisania:\n");

	while ((end < 2) && (temp = getchar())) 
	{

		choice = 0;

		if (temp == '\n') 
		{
			end++;
			choice = 1;
		}
		else 
		{
			end = 0;
		}

		if (end < 2) 
		{
			fputc(temp, min->f);
			min->size++;
		}

		if (choice) 
		{
			min = find_min(pliczki, counter);
		}
	}

	printf("Files saved");

	for (int i = 0; i < counter; i++) 
	{
		close_file(pliczki + i);
	}

	return 0;
}

