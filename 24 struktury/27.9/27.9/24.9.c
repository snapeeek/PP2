#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

struct complex_t
{
	float re;
	float im;
};

struct complex_t* set(struct complex_t* cp, float re, float im, int *err_code)
{
	if (cp == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return NULL;
	}

	cp->re = re;
	cp->im = im;
	if (err_code != NULL)
		*err_code = 0;

	return cp;
}

void show(const struct complex_t* cp)
{
	if (cp != NULL)
	{
		printf("%f", cp->re);
		
		if (cp->im < 0)
		{
			printf(" - i%f", fabs(cp->im));
		}
		else if (cp->im >= 0)
		{
			printf(" + i%f", fabs(cp->im));
		}
		
		printf("\n");
	}
}

float complex_abs(struct complex_t* cp, int * err_code)
{
	if (cp == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return -1;
	}
	else
	{
		float mod;
		mod = (float)sqrt(((cp->re)*(cp->re)) + ((cp->im)*(cp->im)));
		if (err_code != NULL)
			*err_code = 0;
		return mod;
	}
}

int add(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
	if ((first == NULL) || (second == NULL) || (result == NULL))
		return 0;
	
	result->re = first->re + second->re;
	result->im = first->im + second->im;
	return 1;
}

int subtract(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
	if ((first == NULL) || (second == NULL) || (result == NULL))
		return 0;

	result->re = first->re - second->re;
	result->im = first->im - second->im;
	return 1;
}

int read(struct complex_t* cp)
{
	if (cp == NULL)
		return 0;
	char tab[50], helper[15];
	printf("Podaj liczbe zespolona: ");
	fgets(tab, 50, stdin);
	
	if (strchr(tab, 'i') == NULL)
		return 0;
	if ((strchr(tab, '-') == NULL) && (strchr(tab, '+') == NULL))
		return 0;	
	
	int type = 0, i = 0, counter = 0, sign = 0;
	while (*(tab + i) != '\0')
	{
		if ((isdigit((int)(*(tab+i))) != 0) || (*(tab+i) == '.') || ((i == 0) && (*tab + i == '-')))
		{
			*(helper + counter) = *(tab + i);
			counter++;
		}
		else if (*(tab + i) == '+')
		{
			if (*(tab + i + 1) != 'i')
				return 0;
			sign = 0;
		}
		else if (*(tab + i) == '-')
		{
			if (*(tab + i + 1) != 'i')
				return 0;
			sign = 1;
		}
			
		else
		{
			*(helper + counter) = '\0';			
			
			if (type == 0)
			{
				cp->re = (float)atof(helper);
				if (*(tab + i) == 'i')
				{
					type = 1;
					if (isdigit((int)(*(tab + i + 1))) == 0)
						return 0;
				}
			}

			
			else if (type == 1)
			{
				if (sign == 0)
					cp->im = (float)atof(helper);
				else if (sign == 1)
					cp->im = (float)atof(helper) * (-1);
			}
			counter = 0;
		}		
		i++;
	}
	return 1;

}

int multiply(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
	if ((first == NULL) || (second == NULL) || (result == NULL))
		return 0;
	result->re = (first->re * second->re) + ((first->im)*(second->im)*(-1));
	result->im = (first->re * second->im) + ((first->im)*(second->re));
	return 1;
}

int divide(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
	if ((first == NULL) || (second == NULL) || (result == NULL))
		return 0;

	if ((((second->re * second->re) + (second->im * second->im)) == 0) || (((second->re * second->re) + (second->im * second->im)) == 0))
		return 0;

	result->re = ((first->re*second->re) + (first->im * second->im)) / ((second->re * second->re) + (second->im * second->im));
	result->im = ((first->im * second->re) - (first->re * second->im)) / ((second->re * second->re) + (second->im * second->im));
	
	return 1;
}

int main()
{
	srand(rand());
	struct complex_t first, second, result, *p1, *p2, *p3;
	p1 = &first; p2 = &second; p3 = &result;
	int error = 0, *err;
	err = &error;

	if (!read(p1))
	{
		printf("Error");
		return 1;
	}
	if (!read(p2))
	{
		printf("Error");
		return 1;
	}
	complex_abs(p1, err);
	
	if ((p1->re == p2->re) && (p1->im == p2->im))
	{
		printf("Error");
		return 1;
	}	

	if (add(p1, p2, p3))
		show(p3);
	else
		printf("Error");
	
	if (subtract(p1, p2, p3))
		show(p3);
	else
		printf("Error"); 
	
	if (multiply(p1, p2, p3))
		show(p3);
	else
		printf("Error");
	
	if (divide(p1, p2, p3))
		show(p3);
	else
		printf("Error");

	return 0;
}