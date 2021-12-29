#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "dictionary.h"
#include "vector.h"

int crt_dic(struct dictionary_t **dict);
struct dictionary_t* con_dic(struct dictionary_t *dict1, struct dictionary_t *dict2);
int crt_prb_vec(struct array_t **vec, struct dictionary_t *dict, struct dictionary_t *together);
int clc_wrd_nm(struct dictionary_t *dict);
float clc_sim(struct array_t *vec1, struct array_t *vec2);

int main()
{
	struct dictionary_t *dict1, *dict2, *dcommon;
	struct array_t *vec1, *vec2;
	float sim;

	switch (crt_dic(&dict1)) 
	{
	case 1:
		printf("Error w pliku 1");
		return 1;
	case 2:
		printf("File not found");
		return 2;
	case 4:
		printf("Failed to allocate memory");
		return 4;
	}

	switch (crt_dic(&dict2)) 
	{
	case 1:
		printf("Error w pliku 2");
		destroy_dictionary(&dict1);
		return 1;
	case 2:
		printf("File not found");
		destroy_dictionary(&dict1);
		return 2;
	case 4:
		printf("Failed to allocate memory");
		destroy_dictionary(&dict1);
		return 4;
	}

	if (!(dcommon = con_dic(dict1, dict2))) 
	{
		printf("Failed to allocate memory");
		destroy_dictionary(&dict1);
		destroy_dictionary(&dict2);
		return 4;
	}

	switch (crt_prb_vec(&vec1, dict1, dcommon)) 
	{
	case 1:
		printf("Error w slowniku 3");
		destroy_dictionary(&dict1);
		destroy_dictionary(&dict2);
		destroy_dictionary(&dcommon);
		return 1;
	case 2:
		printf("Failed to allocate memory");
		destroy_dictionary(&dict1);
		destroy_dictionary(&dict2);
		destroy_dictionary(&dcommon);
		return 4;
	}

	switch (crt_prb_vec(&vec2, dict2, dcommon)) 
	{
	case 1:
		printf("Error 4");
		destroy_array(&vec1);
		destroy_dictionary(&dict1);
		destroy_dictionary(&dict2);
		destroy_dictionary(&dcommon);
		
		return 1;
	case 2:
		printf("Failed to allocate memory");
		destroy_array(&vec1);
		destroy_dictionary(&dict1);
		destroy_dictionary(&dict2);
		destroy_dictionary(&dcommon);
		
		return 4;
	}

	sim = clc_sim(vec1, vec2);

	if (sim == -1) 
	{
		printf("Error 5");
		destroy_array(&vec1);
		destroy_array(&vec2);
		destroy_dictionary(&dict1);
		destroy_dictionary(&dict2);
		destroy_dictionary(&dcommon);
		
		return 1;
	}

	printf("Wynik: %.5f", sim);

	destroy_array(&vec1);
	destroy_array(&vec2);
	destroy_dictionary(&dict1);
	destroy_dictionary(&dict2);
	destroy_dictionary(&dcommon);
	

	return 0;
}

int crt_dic(struct dictionary_t **dict)
{
	FILE *f;
	char *path;

	if (!(path = malloc(50))) 
	{
		return 4;
	}

	printf("Podaj plik: ");
	scanf("%49s", path);

	if (!(f = fopen(path, "r"))) 
	{
		free(path);
		return 2;
	}

	if (!(*dict = create_dictionary(10))) 
	{
		free(path);
		fclose(f);
		return 4;
	}

	
	char *wrd;
	if (!(wrd = malloc(50 * sizeof(char))))
	{
		free(path);
		fclose(f);
		return 2;
	}

	while (1)
	{
		fscanf(f, "%49s", wrd);

		if (isalpha(*(wrd + strlen(wrd) - 1)) == 0)
			*(wrd + strlen(wrd) - 1) = '\0';

		if (dictionary_add_word(*dict, wrd) != 0)
			break;

		int ch;
		if ((ch = fgetc(f)) == EOF)
			break;
		fpos_t help;
	

		fgetpos(f, &help);

		if ((ch = fgetc(f)) == EOF)
			break;
		else
			fsetpos(f, &help);
	}

	
	free(wrd);	
	fclose(f);
	free(path);

	return 0;
}

struct dictionary_t* con_dic(struct dictionary_t *dict1, struct dictionary_t *dict2)
{
	if (!dict1 || !dict2) 
	{
		return NULL;
	}

	struct dictionary_t *end;

	if (!(end = create_dictionary(10))) 
	{
		return NULL;
	}

	for (int i = 0; i < dict1->size; i++) 
	{
		if (dictionary_add_word(end, (dict1->wc + i)->word)) 
		{
			destroy_dictionary(&end);
			return NULL;
		}
	}

	for (int i = 0; i < dict2->size; i++) 
	{
		if (dictionary_add_word(end, (dict2->wc + i)->word)) 
		{
			destroy_dictionary(&end);
			return NULL;
		}
	}

	return end;
}

int crt_prb_vec(struct array_t **vec, struct dictionary_t *dict, struct dictionary_t *together)
{
	if (!vec || !dict || !together) 
	{
		return 1;
	}

	int error;

	error = create_array(vec, together->size);
	if (error) 
	{
		return error;
	}

	struct word_count_t  *temporary;
	int word_count = clc_wrd_nm(dict);
	float prob;

	if (word_count == -1) 
	{
		destroy_array(vec);
		return 1;
	}

	for (int i = 0; i < together->size; i++) 
	{
		if (temporary = dictionary_find_word(dict, (together->wc + i)->word)) 
		{
			prob = (float)temporary->counter / word_count;
			error = add(*vec, prob);
			if (error) 
			{
				destroy_array(vec);
				return error;
			}
		}
		else 
		{
			error = add(*vec, 0);
			if (error) 
			{
				destroy_array(vec);
				return error;
			}
		}
	}

	return 0;
}

int clc_wrd_nm(struct dictionary_t *dict)
{
	if (!dict) 
	{
		return -1;
	}

	int sum = 0;
	int temporary;

	for (int i = 0; i < dict->size; i++) 
	{
		temporary = (dict->wc + i)->counter;
		if (temporary > 0) 
		{
			sum += temporary;
		}
		else 
		{
			return -1;
		}
	}

	return sum;
}

float clc_sim(struct array_t *vec1, struct array_t *vec2)
{
	if (!vec1 || !vec2) 
	{
		return -1;
	}

	float dot = dot_product(vec1, vec2);

	if (dot == -1) 
	{
		return -1;
	}

	float length1 = length(vec1);
	float length2 = length(vec2);

	if (length1 == -1 || length2 == -1 || length1 * length2 == 0) 
	{
		return -1;
	}

	return dot / (length1 * length2);
}