#include<stdio.h>

#include<stdlib.h>
#include<string.h>

int main() {
	FILE *fp1, *fp2;
	int ch; char tab1[50], tab2[50];
	
	printf("Podaj zrodlo pierwszego pliku: ");
	scanf("%49s", tab1);
	fp1 = fopen(tab1, "r");
	if (fp1 == NULL)
	{
		printf("Error");
		exit(1);
	}
	printf("Podaj zrodlo drugiego pliku: ");
	scanf("%49s", tab2);	
	fp2 = fopen(tab2, "w");
	if (fp2 == NULL)
	{
		printf("Error");
		exit(1);
	}

	while (1) {
		ch = fgetc(fp1);

		if (ch == EOF)
			break;
		else
			putc(ch, fp2);
	}

	printf("File copied");
	fclose(fp1);
	fclose(fp2);
	return 0;
}