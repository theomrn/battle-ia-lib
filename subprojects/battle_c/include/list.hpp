#ifndef LIST_HPP
#define LIST_HPP

#include <cstdlib>
class LinkedList {
private:
  LinkedList *next_ = nullptr;
  LinkedList *prev_ = nullptr;
  void *value_;

public:
  explicit LinkedList(void *value) : value_(value) {}

  ~LinkedList() { free(value_); };

  LinkedList *Next() const;
  LinkedList *Prev() const;
  void *Value() const;

  LinkedList *Rewind();
  LinkedList *WalkToEnd();
  static void Free(LinkedList *linked_list);

  void Add(LinkedList *next);
};

#endif // LIST_HPP
