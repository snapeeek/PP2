#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int marks_counter(const char* text, int* uppercase, int* lowercase, int* whitespace)
{
	int i = 0;
	if (text == NULL)
		return -1;
	else if ((uppercase == NULL) || (lowercase == NULL) || (whitespace == NULL))
		return -2;
	else
	{
		while ((*(text + i) != '\0'))
		{
			if (isspace(*(text + i)) != 0)
				*whitespace= *whitespace + 1;
			else if (islower(*(text + i)) != 0)
				*lowercase = *lowercase + 1;
			else if (isupper(*(text + i)) != 0)
				*uppercase = *uppercase + 1;
			i++;
		}
		return 1;
	}
	
}


int main()
{
	const char* t1 = "Ala Ma Kota a kot Ma AlE";
	int *p1, *p2, *p3, up, low, white;

	p1 = &up;
	p2 = &low;
	p3 = &white;
	*p1 = 0; *p2 = 0; *p3 = 0;
	
	marks_counter(t1, p1, p2, p3);

	printf("%d %d %d\n", *p1, *p2, *p3);


	return 0;
}