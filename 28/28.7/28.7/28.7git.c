#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"dictionary.h"

int main()
{
	char *sauce;
	if (!(sauce = malloc(50 * sizeof(char))))
	{
		printf("Failed to allocate memory");
		return 2;
	}

	printf("Podaj zrodlo: ");
	scanf("%49s", sauce);

	FILE *fp;
	if (!(fp = fopen(sauce, "r")))
	{
		printf("File not found");
		free(sauce);
		return 1;
	}

	char *wrd;
	if (!(wrd = malloc(50 * sizeof(char))))
	{
		printf("Failed to allocate memory");
		free(sauce);
		fclose(fp);
		return 2;
	}

	struct dictionary_t *d;
	if (!(d = create_dictionary(10)))
	{
		printf("Failed to allocate memory");
		free(sauce);
		free(wrd);
		fclose(fp);
		return 2;
	}

	
	while (1)
	{
		fscanf(fp, "%49s", wrd);
		
		if (isalpha(*(wrd + strlen(wrd) - 1)) == 0)
			*(wrd + strlen(wrd) - 1) = '\0';
		
		if (dictionary_add_word(d, wrd) != 0)
			break;		
		
		int ch;		
		if ((ch = fgetc(fp)) == EOF)
			break;
		fpos_t help, *p;
		p = &help;

		fgetpos(fp, p);

		if ((ch = fgetc(fp)) == EOF)
			break;
		else
			fsetpos(fp, p);
		
	}

	dictionary_display(d);
	destroy_dictionary(&d);

	free(sauce);
	free(wrd);
	fclose(fp);
	return 0;
}