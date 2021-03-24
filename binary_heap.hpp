/*!
   \file "binary_heap.hpp"
   \brief "Code for priority queue: binary heap.
      Current implamentation use numeration for elements from 1 to N.
      Its make calculation parent/child index faster."
   \author "Oleksii Poltavets"
   \date "21"/"March"/"2021"
*/

#pragma once
#include <stdlib.h>
#include <stdexcept>
#include <type_traits>

template<class T, class Compare>
struct binary_heap {
public:
  // Check template class is_trivially_copyable
  // for safe usage realloc function
  static_assert(std::is_trivially_copyable<T>::value,
                  "Type must be trivially copyable");

  explicit binary_heap(size_t num_elements=10) // constructor
  : _capacity(num_elements), data((T*) calloc(_capacity+1, sizeof(T))) {}
  ~binary_heap() { free(data); }  // destructor
  T get_front() {
    if (qsize == 0) throw std::out_of_range("empty queue");
    return data[1];
  }
  T front() {
    // Unsafe: return a copy of first (min/max) element
    // w/o checking empty queue or not
    return data[1];
  }
  void push(T element) {
    /** Push element to back of heap then repair heap order */
    if (++qsize > _capacity) expand();
    data[qsize] = element;
    heapify_up(qsize);
  }
  void pop_front() noexcept {
    // Remove (move to back) the root element and then correcting heap
    if (qsize == 0) return;
    std::swap(data[1], data[qsize]);
    heapify_down(1); qsize--;
  }
  T push_pop_front(T element) noexcept {
    if (qsize == 0) return element;
    std::swap(data[1], element);
    heapify_down(1);
    return element;
  }
  T get_pop_front() {
    auto tmp = get_front();
    pop_front();
    return tmp;
  }
  const T* search(T element){
    // return const pointer on element or on end of heap
    auto p = begin();
    for (; p != end(); p++)
      if (*p == element) break;
    return p;
  }
  bool remove(T element){
    T* p = find(element);
    if (p == end()) return false;
    std::swap(*p, data[qsize--]);
    heapify_down(p - data);
    return true;
  }
  bool replace(T element, T new_element) noexcept {
    T* p = find(element);
    if (p == end()) return false;
    std::swap(*p, new_element);
    if ( cmp(*p, element)) { heapify_up( p - data ); }
    else { heapify_down( p - data ); };
    return true;
  }
  void reserve(size_t num_elements) {
    /** It is possible to use the function
     * as shrink_to_fit by passing 0 value.
     * Realloc - fast copy but requared
     * trivially copyable type as template class.
     */
    if (num_elements < qsize) num_elements = qsize;
    _capacity= num_elements;
    data= (T*) realloc(data, (_capacity+ 1) * sizeof(T));
    if (data == nullptr)
      throw std::runtime_error("Error: memory could not be allocated");
  }
  void expand() { reserve( (size_t) (qsize * expand_coef)); }
  const T* cbegin(){ return data + 1; }
  const T* cend(){ return data + qsize + 1; }
  bool empty() { return qsize == 0; }
  size_t size() { return qsize; }
  size_t capacity() { return _capacity; }

private:

  void heapify_down(size_t index) noexcept {
    for (size_t parent=index, child=parent*2; child < qsize; child*=2) {
      if ((child+1 < qsize) && cmp(data[child+1], data[child])) child++;
      if ( !cmp(data[child], data[parent]) ) break;
      std::swap(data[parent], data[child]);
      parent = child;
    };
  }
  void heapify_up(size_t index) noexcept {
    for (size_t child=index, parent=child/2; parent>0; parent /=2){
      if ( ! cmp(data[child], data[parent]) ) break;
      std::swap(data[parent], data[child]);
      child = parent;
    };
  }
  T* find(T element) noexcept {
    // return pointer on element or on end of heap
    auto p = begin();
    for (; p != end(); p++)
      if (*p == element) break;
    return p;
  }
  T* begin(){ return data + 1; }
  T* end(){ return data + qsize + 1; }
  Compare cmp = Compare();
  const int expand_coef = 2;
  size_t qsize= 0;
  size_t _capacity;
  T* data;
};

/** Template for fast creating min/max binary heap*/
template<class T>
using max_binary_heap = binary_heap<T, std::greater<T>>;
template<class T>
using min_binary_heap = binary_heap<T, std::less<T>>;
