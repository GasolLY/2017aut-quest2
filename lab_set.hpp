#ifndef LAB_SET_HPP_
#define LAB_SET_HPP_

#include "labafx.hpp"

// DO NOT MODIFY BELOW

namespace Lab {
template <typename T> class set {
  set();
  int size();
  void insert(const T &item);
  class iterator {
    const T &operator*();
    iterator operator++(int); // for iter++
    iterator operator--(int);
    // prefix increment operator is not required by zht. Make him happy
    // iterator &operator++();
    // iterator &operator--();
  private:
    // add your data and function here
  };
  iterator find(const T &item);
  void erase(iterator it);
  iterator begin();
  iterator end();
  void clear();
  ~set();

private:
  // add your data and function here
};
}
#endif