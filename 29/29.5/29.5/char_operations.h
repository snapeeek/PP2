#ifndef pliknag
#define pliknag

char* letter_modifier(const char* text, char (*p)(char));
char lower_to_upper(char ch);
char upper_to_lower(char ch);
char space_to_dash(char ch);
char reverse_letter(char ch);

#endif