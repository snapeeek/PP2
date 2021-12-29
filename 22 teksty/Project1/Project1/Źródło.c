for (int i = 0; (*(tablica + i) == ' ') || ((*(tablica + i) >= 9) && (*(tablica + i) <= 13)); )
{
	for (int k = 0; *(tablica + k) != 0; k++)
	{
		*(tablica + k) = *(tablica + k + 1);
	}
}
//usuwanie spacji za wyrazem

for (int g = rozmiar - 1; *(tablica + g) == '\0'; g--)
{
	for (int m = g; (*(tablica + m) == ' ') || ((*(tablica + m) >= 9) && (*(tablica + m) <= 13)); m--)
	{
		*(tablica + m) = 0;
	}
}


return 1;
}


int change_letter_size(const char* src, char* dest)
{
	int i = 0;
	if ((src == NULL) || (dest == NULL))
		return 0;

	while (*(src + i - 1) != '\0')
	{
		if ((*(src + i) >= 65) && (*(src + i) <= 90))
			*(dest + i) = *(src + i) + 32;
		else if ((*(src + i) >= 97) && (*(src + i) <= 122))
			*(dest + i) = *(src + i) - 32;
		else
			*(dest + i) = *(src + i);
		i++;
	}

	return 1;

}

int main()
{
	char txt1[1010], txt2[1010];
	printf("Podaj tekst:\t");
	fgets(txt1, 1010, stdin);
	change_letter_size(txt1, txt2);
	int size = strlen(txt2);
	usun_spacje(txt2, size);
	printf("%s", txt2);




	return 0;
}