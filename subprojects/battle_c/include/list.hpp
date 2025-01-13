#ifndef LIST_HPP
#define LIST_HPP

class LinkedList {
private:
  LinkedList *next_ = nullptr;
  LinkedList *prev_ = nullptr;
  void *value_;

public:
  LinkedList(void *value)
      : value_(value) {

        };

  static LinkedList *Next(LinkedList *linked_list);
  static LinkedList *Prev(LinkedList *linked_list);
  static void *Value(LinkedList *linked_list);

  static LinkedList *Rewind(LinkedList *linked_list);
  static LinkedList *WalkToEnd(LinkedList *linked_list);
  static void Free(LinkedList *linked_list);

  static void Add(LinkedList *previous, LinkedList *next);
};

#endif
