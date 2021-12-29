#include"char_operations.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* letter_modifier(const char* text, char(*p)(char))
{
	if (!text || !(*p))
		return NULL;
	
	char *help;
	if (!(help = malloc((strlen(text) + 1) * sizeof(char))))
		return NULL;
	
	int i = 0;
	while (i < (int)strlen(text))
	{
		*(help + i) = (*p)(*(text + i));
		i++;
	}
	*(help + i) = '\0';
	
	return help;
}
char lower_to_upper(char ch)
{
	if (islower(ch) != 0)
	{
		ch = toupper(ch);
		return ch;
	}
	return ch;
}
char upper_to_lower(char ch)
{
	if (isupper(ch) != 0)
	{
		ch = tolower(ch);
		return ch;
	}
	return ch;
}
char space_to_dash(char ch)
{
	if (ch == ' ')
	{
		ch = '_';
		return ch;
	}
	return ch;
}
char reverse_letter(char ch)
{
	if (ch >= 97 && ch <= 122)
	{
		ch = 122 - ch + 97;
		return ch;
	}
	if (ch >= 65 && ch <= 90)
	{
		ch = 90 - ch + 65;
		return ch;
	}
	return ch;
}