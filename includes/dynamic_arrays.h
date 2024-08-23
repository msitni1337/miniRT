#ifndef DYNAMIC_ARRAYS_H
# define DYNAMIC_ARRAYS_H
# define DA_DEFAULT_CAPACITY 5
#include <stddef.h>
#include <stdlib.h>

typedef struct s_darr
{
	void			*data;
	size_t			count;
	size_t			elem_size;
	size_t			capacity;
}					t_darr;

t_darr		init_da(size_t elem_size);
t_darr		*add_to_arr(t_darr *arr, void *data);
t_darr		*expand_arr(t_darr *arr);

#endif