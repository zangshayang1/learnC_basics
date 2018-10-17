#include "list_sort.h"
#include "dbg.h"

void list_node_swap(ListNode* a, ListNode* b) {
  void* temp = a->value;
  a->value = b->value;
  b->value = temp;
}
int List_bubble_sort(List* list, List_compare cmp) {
  int i = 0;
  ListNode* cur;
  while (i < List_count(list)) {
    cur = list->first;
    while (cur->next) {
      if (cmp((char*)cur->value, (char*)cur->next->value) > 0) {
        list_node_swap(cur, cur->next);
      }
      cur = cur->next;
    }
    i++;
  }
  return 0;
}

List* List_merge_sort(List* list, List_compare cmp) {
  if (List_count(list) <= 1) {
    return list;
  }
  
  // don't move ListNode around
  // use LinkedList functionalities, such as create, push
  int half = List_count(list) / 2;
  List* a = List_create();
  List* b = List_create();
  ListNode* cur = list->first;
  while (cur) {
    if (half > 0) {// first half
      List_push(a, cur->value);
    } else {
      List_push(b, cur->value);
    }
    half--;
    cur = cur->next;
  }

  List_clear_destroy(list); // NOTE the position and the target

  List* sa = List_merge_sort(a, cmp);
  List* sb = List_merge_sort(b, cmp);

  List* c = List_create();
  ListNode* na = sa->first;
  ListNode* nb = sb->first;
  while (na && nb) {
    if (cmp(na->value, nb->value) > 0) {
      List_push(c, nb->value);
      nb = nb->next;
    } else {
      List_push(c, na->value);
      na = na->next;
    }
  }
  while (na) {
    List_push(c, na->value);
    na = na->next;
  }
  while (nb) {
    List_push(c, nb->value);
    nb = nb->next;
  }

  List_clear_destroy(sa); // NOTE the position and the target
  List_clear_destroy(sb); // NOTE the position and the target

  return c;
}
