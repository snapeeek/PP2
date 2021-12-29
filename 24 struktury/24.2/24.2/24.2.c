#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student_t
{
	char name[20];
	char surname[40];
	int index;
};

struct student_t* read(struct student_t* p, int *err_code)
{
	if (p == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return NULL;
	}
	char tab[100];
	printf("Podaj dane: ");
	fgets(tab, 100, stdin);
	if (strchr(tab, ',') == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return NULL;
	}

	int counter = 0, i = 0, type = 0; char helper[10];
	while (1)
	{
		if ((*(tab + i) == ',') || (*(tab + i) == '\0'))
		{
			if ((*(tab + i) == ',') && (*(tab + i + 1) == ' '))
			{
				i++;
			}
			if (type == 0)
			{
				*((p->name) + counter) = '\0';
				if (err_code != NULL)
					*err_code = 1;
			}
			else if (type == 1)
			{
				*((p->surname) + counter) = '\0';
				if (err_code != NULL)
					*err_code = 2;
			}
			else if (type == 2)
			{
				*(helper + counter) = '\0';
				p->index = atoi(helper);
				*err_code = 0;
			}

			type++;
			if (type > 2)
				break;
			counter = 0;
		}
		else
		{
			if (type == 0)
				*((p->name) + counter) = *(tab + i);
			else if (type == 1)
				*((p->surname) + counter) = *(tab + i);
			else if (type == 2)
				*(helper + counter) = *(tab + i);
			counter++;
		}
	
	if (*(tab + i) == '\0')
		break;

	i++;
	}
	return p;
}
void show(const struct student_t* p)
{
	if (p != NULL)
		printf("%s %s, %d", p->name, p->surname, p->index);
}

int main()
{
	struct student_t *p, karta;
	p = &karta;
	int error = 0, *err;
	err = &error;
	if ((read(p, err) == NULL) || (error != 0))
	{
		printf("Error");
		return error;
	}
	show(p);



	return 0;
}