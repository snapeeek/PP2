#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student_t
{
	char *name;
	char *surname;
	int index;
};

struct student_t* read(int *err_code);
void destroy(struct student_t **s);
void show(const struct student_t* p);

int main()
{
	struct student_t *p;

	int error = 0, *err;
	err = &error;
	if (!(p = read(err)) || error != 0)
	{
		printf("Error");
		destroy(&p);
		return error;
	}
	show(p);
	destroy(&p);


	return error;
}

struct student_t* read(int *err_code)
{
	struct student_t *p;
	if (!(p = malloc(sizeof(struct student_t))))
	{
		if (err_code)
			*err_code = 1;
		return NULL;
	}

	char *tab;
	if (!(tab = malloc(100 * sizeof(char))))
	{
		if (err_code)
			*err_code = 1;
		free(p);
		return NULL;
	}

	printf("Podaj dane: ");
	fgets(tab, 100, stdin);
	if (strchr(tab, ',') == NULL)
	{
		if (err_code)
			*err_code = 1;
		destroy(&p);
		free(tab);
		return NULL;
	}
	int przec = 0;
	for (int a = 0; a < (int)strlen(tab); a++)
	{
		if (*(tab + a) == ',')
			przec++;
	}

	switch (przec)
	{
		case 1:
			if (err_code)
				*err_code = 2;
			destroy(&p);
			free(tab);
			return NULL;
		case 2:
			break;
		default:
			if (err_code)
				*err_code = 1;
			destroy(&p);
			free(tab);
			return NULL;

	}

	if (!(p->name = malloc(30 * sizeof(char))))
	{
		if (err_code)
			*err_code = 1;
		destroy(&p);
		free(tab);
		return NULL;
	}


	if (!(p->surname = malloc(30 * sizeof(char))))
	{
		if (err_code)
			*err_code = 1;
		destroy(&p);
		free(tab);
		return NULL;
	}
	char *helper;
	if (!(helper = malloc(10 * sizeof(char))))
	{
		if (err_code)
			*err_code = 1;
		destroy(&p);
		free(tab);
		return NULL;
	}

	int i = 0, j = 0;
	while (*(tab + i) != ',')
	{
		*(p->name + i) = *(tab + i);
		i++;
	}
	*(p->name + i) = '\0';
	i++;
	while (*(tab + i) != ',')
	{
		if (j == 0 && *(tab + i) == ' ')
			i++;
		*(p->surname + j) = *(tab + i);
		i++;
		j++;
	}
	*(p->surname + j) = '\0';
	i++;
	j = 0;

	while (*(tab + i) != '\0')
	{
		*(helper + j) = *(tab + i);
		i++;
		j++;
	}
	*(helper + j) = '\0';
	p->index = atoi(helper);

	if (*(p->name + strlen(p->name) - 1) == ',')
	{
		*(p->name + strlen(p->name) - 1) = '\0';
	}
	if (*(p->surname + strlen(p->surname) - 1) == ',')
	{
		*(p->surname + strlen(p->surname) - 1) = '\0';
	}
	free(helper);
	free(tab);
	return p;
}

void destroy(struct student_t **s)
{
	if (s)
		if (*s)
		{
			free((*(s))->name);
			free((*(s))->surname);
			free(*s);
		}
}

void show(const struct student_t* p)
{
	if (p)
		printf("%s %s, %d", p->name, p->surname, p->index);
}