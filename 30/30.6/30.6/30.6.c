#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

unsigned int swap_bits(unsigned int * pvalue, int b1, int b2);
int isset_bit(const uint32_t* pvalue, int b);
int toggle_bit(uint32_t* pvalue, int b);


int main()
{
	uint32_t *p, a;
	p = &a;
	printf("Wprowadz liczbe 32-bitowa: ");
	scanf("%u", &a);
	int b1, b2;
	printf("Podaj bit pierwszy: ");
	scanf("%d", &b1);
	printf("Podaj bit drugi: ");
	scanf("%d", &b2);

	if (swap_bits(p, b1, b2))
	{
		printf("Error");
		return 1;
	}

	printf("Wynik: %u", a);


	return 0;
}

unsigned int swap_bits(unsigned int * pvalue, int b1, int b2)
{
	if (!pvalue || b1 < 0 || b2 < 0 || b1 >=32 || b2 >= 32)
		return 1;

	if (isset_bit(pvalue, b1) != isset_bit(pvalue, b2))
	{
		toggle_bit(pvalue, b1);
		toggle_bit(pvalue, b2);
	}

	return 0;
}

int isset_bit(const uint32_t* pvalue, int b)
{
	if (!pvalue || b < 0 || b > 31)
		return -1;

	uint32_t help = *pvalue;
	for (int i = 0; i < b; i++)
	{
		help = help / 2;
	}


	return help % 2;
}

int toggle_bit(uint32_t* pvalue, int b)
{
	if (!pvalue || b < 0 || b>31)
		return -1;

	int bi = 1;
	for (int i = 0; i < b; i++)
	{
		bi = bi * 2;
	}

	*pvalue = *pvalue  ^ bi;
	

	return 0;
}