#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

void print_lin(long long n, int p);
int toggle_bit(uint32_t* pvalue, int b);
int set_bit(uint32_t* pvalue, int b);
int clear_bit(uint32_t* pvalue, int b);
int isset_bit(const uint32_t* pvalue, int b);


int main()
{
	uint32_t value, *p;
	p = &value;
	
	printf("Podaj licze 32-bitowa: ");
	scanf("%ui", &value);
	int bit;
	printf("Podaj bit: ");
	scanf("%d", &bit);
	
	uint32_t help; int counter = 0;
	help = value;
	while (1)
	{
		if (help > 0)
		{
			help = help / 2;
			counter++;
		}
		else
			break;
	}
	
	if (bit < 0 || bit > counter)
	{
		printf("Invalid bit index");
		return 1;
	}

	int choice;
	printf("Podaj operacje: ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 0:
		toggle_bit(p, bit);
		break;
	case 1:
		set_bit(p, bit);
		break;
	case 2:
		clear_bit(p, bit);
		break;
	case 3:
		printf("%d", isset_bit(p, bit));
		break;
	default:
		printf("Invalid operation");
		return 1;
	}




	return 0;
}

void print_lin(long long n, int p)
{
	if (n>0)
	{
		print_lin(n / p, p); 
		if (n%p>9)
			switch (n%p)
			{
			case 10:
				printf("a"); break;
			case 11:
				printf("b"); break;
			case 12:
				printf("c"); break;
			case 13:
				printf("d"); break;
			case 14:
				printf("e"); break;
			case 15:
				printf("f"); break;
			}
		else
			printf("%lld",n % p);
	}
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
	print_lin(*pvalue, 16);

	return 0;
}

int set_bit(uint32_t* pvalue, int b) 
{
	if (!pvalue || b < 0 || b>31)
		return -1;

	int bi = 1;
	for (int i = 0; i < b; i++)
	{
		bi = bi * 2;
	}

	*pvalue = *pvalue | bi;
	print_lin(*pvalue, 16);

	return 0;
}

int clear_bit(uint32_t* pvalue, int b)
{
	if (!pvalue || b < 0 || b > 31)
		return -1;

	long long int bi = 1, suma = 0;
	for (int i = 0; i < 32; i++)
	{
		if (i != b)
			suma = suma + bi;
		bi = bi * 2;
				
	}	
	*pvalue = *pvalue & suma;	
	print_lin(*pvalue, 16);
	
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


	return help%2;
}