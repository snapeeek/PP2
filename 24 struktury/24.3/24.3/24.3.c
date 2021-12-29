#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct student_t
{
	char name[20];
	char surname[40];
	int index;
	char field[50];
	char faculty[80];
	int year;
};

struct student_t* read(struct student_t* p, int *err_code)
{
	if (p == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return NULL;
	}
	char tab[200];
	printf("Podaj dane: ");
	fgets(tab, 200, stdin);
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
				if (err_code != NULL)
					*err_code = 3;
			}
			else if (type == 3)
			{
				*((p->field) + counter) = '\0';
				if (err_code != NULL)
					*err_code = 4;
			}
			else if (type == 4)
			{
				*((p->faculty) + counter) = '\0';
				if (err_code != NULL)
					*err_code = 5;
			}
			else if (type == 5)
			{
				*(helper + counter) = '\0';
				p->year = atoi(helper);
				if (err_code != NULL)
					*err_code = 0;
			}

			type++;
			if (type > 5)
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
			else if (type == 3)
				*((p->field) + counter) = *(tab + i);
			else if (type == 4)
				*((p->faculty) + counter) = *(tab + i);
			else if (type == 5)
				*(helper + counter) = *(tab + i);
			counter++;
		}

		if (*(tab + i) == '\0')
			break;

		i++;
	}
	return p;
}

struct student_t* set_name(struct student_t* student, const char * name, int *err_code)
{
	if ((student == NULL) || (name == NULL) || (strlen(name) > 19))
	{
		if (err_code != NULL)
			*err_code = 1;
		return student;
	}
	strcpy(student->name, name);
	if (err_code != NULL)
		*err_code = 0;
	return student;
}

struct student_t* set_surname(struct student_t* student, const char * surname, int *err_code)
{
	if ((student == NULL) || (surname == NULL) || (strlen(surname) > 39))
	{
		if (err_code != NULL)
			*err_code = 1;
		return student;
	}
	strcpy(student->surname, surname);
	if (err_code != NULL)
		*err_code = 0;
	return student;
}

struct student_t* set_field(struct student_t* student, const char * field, int *err_code)
{
	if ((student == NULL) || (field == NULL) || (strlen(field) > 49))
	{
		if (err_code != NULL)
			*err_code = 1;
		return student;
	}
	strcpy(student->field, field);
	if (err_code != NULL)
		*err_code = 0;
	return student;
}

struct student_t* set_faculty(struct student_t* student, const char * faculty, int *err_code)
{
	if ((student == NULL) || (faculty == NULL) || (strlen(faculty) > 79))
	{
		if (err_code != NULL)
			*err_code = 1;
		return student;
	}
	strcpy(student->faculty, faculty);
	if (err_code != NULL)
		*err_code = 0;
	return student;
}

struct student_t* set_year(struct student_t* student, int year, int *err_code)
{
	if ((student == NULL))
	{
		if (err_code != NULL)
			*err_code = 1;
		return student;
	}
	student->year = year;
	if (err_code != NULL)
		*err_code = 0;
	return student;
}

struct student_t* set_index(struct student_t* student, int index, int *err_code)
{
	if ((student == NULL))
	{
		if (err_code != NULL)
			*err_code = 1;
		return student;
	}
	student->index = index;
	if (err_code != NULL)
		*err_code = 0;
	return student;
}

struct student_t* set(struct student_t* student, const char * name, const char * surname, int index, const char * field, const char * faculty, int year, int *err_code)
{
	if ((student == NULL) || (name == NULL) || (surname == NULL) || (field == NULL) || (faculty == NULL) || (strlen(name) > 20) || (strlen(surname) > 40) || (strlen(field) > 50) || (strlen(faculty) > 80))
	{
		if (err_code != NULL)
			*err_code = 1;
		return student;
	}
	set_name(student, name, NULL);
	set_surname(student, surname, NULL);
	set_index(student, index, NULL);
	set_field(student, field, NULL);
	set_faculty(student, faculty, NULL);
	set_year(student, year, NULL);
	
	if (err_code != NULL)
		*err_code = 0;

	return student;
}

void display(const struct student_t* p)
{
	if (p != NULL)
	{
		if ((tolower(p->field[0]) == 'a') || (tolower(p->field[0]) == 'e') || (tolower(p->field[0]) == 'i') || (tolower(p->field[0]) == 'o') || (tolower(p->field[0]) == 'u') || (tolower(p->field[0]) == 'y'))
			printf("%s %s, index number: %d, was an %s student at the %s in %d.\n", p->name, p->surname, p->index, p->field, p->faculty, p->year);
		else
			printf("%s %s, index number: %d, was a %s student at the %s in %d.\n", p->name, p->surname, p->index, p->field, p->faculty, p->year);
	}
}

void display_name(const struct student_t* student)
{
	if (student != NULL)
	{
		printf("Student name: %s\n", student->name);
	}
}

void display_surname(const struct student_t* student)
{
	if (student != NULL)
	{
		printf("Student surname: %s\n", student->surname);
	}
}

void display_field(const struct student_t* student)
{
	if (student != NULL)
	{
		printf("Field: %s\n", student->field);
	}
}

void display_faculty(const struct student_t* student)
{
	if (student != NULL)
	{
		printf("Faculty: %s\n", student->faculty);
	}
}

void display_index(const struct student_t* student)
{
	if (student != NULL)
	{
		printf("Index: %d\n", student->index);
	}
}

void display_year(const struct student_t* student)
{
	if (student != NULL)
	{
		printf("Year: %d\n", student->year);
	}
}

int main()
{
	struct student_t *p, karta, karta2, *p2;
	p = &karta; p2 = &karta2;
	int error = 0, *err;
	err = &error;
	set(p, "Maciej", "Wozniak", 215925, "Informatyka", "WEEiA", 2018, NULL);
	if ((read(p2, err) == NULL) || (error != 0))
	{
		printf("Error\n");
		display(p);
		
	}
	else
	{
		display(p2);
		display(p);
		display_name(p2);
		display_surname(p2);
		display_index(p2);
		display_field(p2);
		display_faculty(p2);
		display_year(p2);
	}
	
	return error;
}