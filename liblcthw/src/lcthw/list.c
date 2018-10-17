#include "list.h"
#include "dbg.h"

List* List_create() {
  // malloc vs calloc ? calloc allocate the memory and init the memory with 0
  // so malloc could be lazy-init but calloc actually touches memory when invoked
  return calloc(1, sizeof(List));
}

void List_destroy(List* list) {
  LIST_FOREACH(list, first, next, cur) {
    if (cur->prev) {
      // NOTE: different from the below List_clear(), ListNode* is dynamically allocated.
      free(cur->prev);
    }
  }
  free(list->last);
  free(list);
}

void List_clear(List* list) {
  LIST_FOREACH(list, first, next, cur) {
    // NOTE: when cur->value points to a string, int, etc on stack,
    // NOTE: rather than dynamically allocated objects on heap,
    // NOTE: free() would throw EXCEPTION: pointer being freed was not allocated.
    // free(cur->value);
  }
}

void List_clear_destroy(List* list) {
  List_clear(list);
  List_destroy(list);
}

void List_push(List* list, void* value) {
  ListNode* node = calloc(1, sizeof(ListNode));
  node->value = value;
  if (list->last == NULL) {
    list->first = node;
    list->last = node;
  } else {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }
  list->count++;
error:
  return ;
}

void* List_pop(List* list) {
  ListNode* node = list->last;
  return node != NULL ? List_remove(list, node) : NULL;
}

// insert at the beginning
void List_unshift(List* list, void* value) {
  ListNode* node = calloc(1, sizeof(ListNode));
  node->value = value;

  if (list->first == NULL) {
    list->first = node;
    list->last = node;
  } else {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
  }
  list->count++;
error:
  return ;
}

// remove the first node
void* List_shift(List* list) {
  ListNode* node = list->first;
  return node != NULL ? List_remove(list, node) : NULL;
}

void* List_remove(List* list, ListNode* node) {
  void* result = NULL;

  check(list->first && list->last, "Empty list is invalid for remove operation.");
  check(node, "the target node for removal cannot be NULL.");

  if (node == list->first && node == list->last) {
    list->first = NULL;
    list->last = NULL;
  } else if (node == list->first) {
    list->first = node->next;
    check(list->first != NULL, "Invalid list.");
    list->first->prev = NULL;
  } else if (node == list->last) {
    list->last = node->prev;
    check(list->last != NULL, "Invalid list.");
    list->last->next = NULL;
  } else {
    ListNode* after = node->next;
    ListNode* before = node->prev;
    before->next = after;
    after->prev = before;
  }
  list->count--;
  result = node->value;
  free(node);
error:
  return result;
}




















// end
