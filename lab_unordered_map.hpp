#ifndef LAB_UNORDERED_MAP_HPP_
#define LAB_UNORDERED_MAP_HPP_

#include "labafx.hpp"
namespace Lab {
template <typename Key, typename Value, typename Hash = hash<Key>
          /*, typename KeyEqual=equal_to<Key> */>
// KeyEqual is not required by zht. Make him happy.
class unordered_map {
public:
  unordered_map();
  size_t size();
  void insert(pair<Key, Value> kvpair);
  void clear();
  class iterator {
  public:
    // assume Key won't be modified
    // actual priviledge control is hard
    // since zht doesn't require it. Make him happy
    pair<const Key, Value> &operator*();
    iterator operator++(int);
    iterator operator--(int);
    // prefix increment operator is not required by zht. Make him happy
    // iterator &operator++();
    // iterator &operator--();
  private:
    // add your data and function here
  };
  iterator begin();
  iterator end();
  iterator find(const Key &item);
  void erase(iterator iter);
  ~unordered_map();

private:
  // add your data and function here
};
}
#endif