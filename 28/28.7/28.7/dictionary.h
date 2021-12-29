#ifndef pliknag
#define pliknag

struct word_count_t 
{
	char *word;
	int counter;
};

struct dictionary_t
{
	int size;
	int capacity;
	struct word_count_t *wc;
};

struct dictionary_t* create_dictionary(int N);
void destroy_dictionary(struct dictionary_t** d);
struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word);
void dictionary_display(const struct dictionary_t *d);
int dictionary_add_word(struct dictionary_t *d, const char *word);

#endif