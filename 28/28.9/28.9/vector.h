#ifndef vector
#define vector



struct array_t
{
	float *ptr;
	int size;
	int capacity;
};

int create(struct array_t *a, int N);
int add(struct array_t *a, float value);
void display(const struct array_t *a);
void destroy(struct array_t *a);
void destroy_array(struct array_t **a);
int create_array(struct array_t **a, int N);
float dot_product(const struct array_t *a, const struct array_t *b);
float length(const struct array_t *a);

#endif