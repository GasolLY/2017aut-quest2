#ifndef LAB_PRIORITY_QUEUE
#define LAB_PRIORITY_QUEUE

#include "labafx.hpp"

namespace Lab {

template <typename T, typename Comp = Lab::less<T>> class priority_queue {
public:
  priority_queue();
  int size();
  void push(void *key, int size);
  const T &top();
  void pop();
  void clear();
  ~priority_queue();
private:
  // add your data and function here
};
}

#endif