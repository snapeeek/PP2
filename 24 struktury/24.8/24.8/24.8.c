#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct date_t
{
	int day;
	int month;
	int year;
};
struct date_t* set_date(struct date_t* d, int day, int month, int year, int *err_code)
{
	if ((d == NULL) || (day > 31) || (day < 1) || (month < 1) || (month > 12))
	{
		if (err_code != NULL)
			*err_code = 1;
		return NULL;
	}
	else 
	{
		if (err_code != NULL)
			*err_code = 0;
		d->day = day;
		d->month = month;
		d->year = year;
	}
	return d;
}

struct date_t* read(struct date_t* d, int *err_code)
{
	if (d == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return NULL;
	}
	
	char data[15], helper[15];
	printf("Podaj date (dd-mm-yyyy): ");
	scanf("%14s", data);
	if (strchr(data, '-') == NULL)
		return NULL;
	int type = 0, counter = 0;
	for (int i = 0; i <= (int)strlen(data); i++)
	{
		if ((*(data + i) == '-') || (i == (int)strlen(data)))
		{
			if (type == 0)
			{
				*(helper + counter) = '\0';
				d->day = atoi(helper);
				counter = 0;
				type++;
			}
			else if (type == 1)
			{
				*(helper + counter) = '\0';
				d->month = atoi(helper);
				counter = 0;
				type++;
			}
			else if (type == 2)
			{
				*(helper + counter) = '\0';
				d->year = atoi(helper);
				counter = 0;
				type++;
			}
		}
		else
		{
			*(helper + counter) = *(data + i);
			counter++;
		}
	}

	if (err_code != NULL)
		*err_code = 0;
	return d;
}

int validate(const struct date_t* d)
{
	if (d == NULL)
		return -1;
	if ((d->month < 1) || (d->month > 12))
		return 0;
	if ((d->day < 1) || (d->day > 31))
		return 0;
	if (((d->month == 7) || (d->month == 8)) && (d->day == 31))
		return 1;
	if ((d->month % 2 != 0) && (d->month > 8) && (d->day > 30))
		return 0;
	if ((d->month % 2 == 0) && (d->month < 7) && (d->day > 30))
		return 0;
	if ((d->month == 2) && (d->day == 29) && (d->year % 4 == 0))
		return 1;
	if ((d->month == 2) && (d->day > 28))
		return 0;

	return 1;
}

void show(const struct date_t* d)
{
	if (d != NULL)
	{
		printf("%d-%d-%d\n", d->day, d->month, d->year);
	}
		
}

int main()
{
	struct date_t *p, karta;
	int error = 0, *err;
	err = &error;
	p = &karta;

	if (read(p, err) == NULL)
	{
		printf("Incorrect input");
		return 1;
	}
	
	if (validate(p))
	{
		printf("Podana data: ");
		show(p);
		printf("Correct");		
	}
	else if (!validate(p))
		printf("Incorrect");
	else
	{
		printf("Incorretct input");
		return 1;
	}
	return 0;
}