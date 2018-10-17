#ifndef lcthw_List_sort_h
#define lcthw_List_sort_h

#include "list.h"

typedef int (*List_compare) (const void* a, const void* b);

int List_bubble_sort(List* l, List_compare cmp);

List* List_merge_sort(List* l, List_compare cmp);

#endif
