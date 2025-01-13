#include "list.hpp"

LinkedList *LinkedList::Next(LinkedList *linked_list) {
  return linked_list->next_;
}

LinkedList *LinkedList::Prev(LinkedList *linked_list) {
  return linked_list->prev_;
}

void *LinkedList::Value(LinkedList *linked_list) { return linked_list->value_; }

LinkedList *LinkedList::Rewind(LinkedList *linked_list) {
  LinkedList *current = linked_list;
  do {
    LinkedList *new_current = LinkedList::Prev(current);
    if (new_current == nullptr) {
      return current;
    }
    current = new_current;
  } while (current != nullptr);
  return nullptr;
}
LinkedList *LinkedList::WalkToEnd(LinkedList *linked_list) {
  LinkedList *current = linked_list;
  do {
    LinkedList *new_current = LinkedList::Next(current);
    if (new_current == nullptr) {
      return current;
    }
    current = new_current;
  } while (current != nullptr);
  return nullptr;
}

void LinkedList::Free(LinkedList *linked_list) {
  LinkedList *next = LinkedList::Rewind(linked_list);

  while (next != nullptr) {
    LinkedList *temp_current = next;
    next = LinkedList::Next(next);
    delete temp_current;
  }
}

void LinkedList::Add(LinkedList *previous, LinkedList *next) {
  if (previous != nullptr) {
    previous->next_ = next;
  }
  if (next != nullptr) {
    next->prev_ = previous;
  }
}
