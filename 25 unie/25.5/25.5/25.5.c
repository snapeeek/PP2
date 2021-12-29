#include<stdio.h>

struct probka {
	unsigned char a : 1;
	unsigned char b : 1;
	unsigned char c : 1;
	unsigned char d : 1;
	unsigned char e : 1;
	unsigned char f : 1;
	unsigned char g : 1;
	unsigned char h : 1;
};

union bit_set {
	unsigned int number;
	struct probka bity[10];
};

int main()
{
	union bit_set unia;
	printf("Podaj bajt: ");
	scanf("%u", &(unia.number));
	struct probka *p;
	p = unia.bity;
	int counter = 0;
	for (int i = 0; i < 10; i++) 
	{
		if (p->a) 
			counter++;
		if (p->b) 
			counter++;
		if (p->c) 
			counter++;
		if (p->d) 
			counter++;
		if (p->e) 
			counter++;
		if (p->f) 
			counter++;
		if (p->g) 
			counter++;
		if (p->h) 
			counter++;
		p++;
	}
	
	
	if (counter % 2)
		printf("NO");
	else
		printf("YES");





	return 0;
}