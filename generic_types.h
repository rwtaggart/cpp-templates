/**
 *  Generics Example
 *  Define custom types in example
 */

#ifndef _GENERICS_EXAMPLE_H_ 
#define _GENERICS_EXAMPLE_H_

#include <cmath>

namespace cgen {

/**
  * Define some custom types to be used later
  */

/** Simple object representing any geometric shape */
struct Shape
{
  const char* category;
  Shape(const char* c): category(c) {}
  Shape(): Shape("") {}
};

/** Circle inherits from type Shape. 
  * Adds radius property and circumference function 
  */
struct Circle : public Shape
{
  int radius;
  int d() { return radius *2; }
  double area();
  Circle(int r): Shape("circle"), radius(r) {}
};

/** Person represents any person */ 
struct Person
{
  const char* name;
  Person(const char* n): name(n) {}
};


// TODO: Stuff this in another header file?
/** 
 * ====================================================
 *   Demonstrate generic typing by defining templates
 * ====================================================
 */


/** Define simple stack container interface */
// TODO: Define StackContainer abstract-base class
// struct StackContainer; 


/** Define nieve array implementation of a stack */
// TODO: Rename -> struct ArrayStack : public StackContainer
template<class C>
struct ArrayContainer
{
  C** _items;
  int _size;
  int _capacity;
  bool add(C* obj);
  C*   pop();
  void clear();
  int  size()     { return _size; }
  int  capacity() { return _capacity; }
  ArrayContainer(int size): _size(0), _capacity(size) { _items = new C*[size](); }
 ~ArrayContainer() { delete[] _items; }
};


/** Define linked-list implementation of a stack */
// TODO: Rename -> struct ArrayStack : public StackContainer
template<class C>
struct StackContainer
{
  struct ListNode;
  struct Iterator;

  ListNode* _items;
  int       _size;

  void  add(C* obj);
  C*    pop();
  void  clear();
  int   size()     { return _size; }
  Iterator begin() { return Iterator(_items); }
  Iterator end()   { return Iterator(NULL); }
  StackContainer(): _items(NULL), _size(0) {}
 // ~StackContainer() { clear(); }

  /* Nested Helper Types */
  struct ListNode
  {
    C* _item;
    ListNode* _next;
    ListNode(C* item, ListNode* next): _item(item), _next(next) {}
    // ~ListNode() { delete _item; }
  };
  struct Iterator
  {
    ListNode* _current;
    Iterator operator++() { return _current = _current->_next; return *this; }
    C&   operator*() { return *_current->_item; }
    // TODO: Implement C* operator->() { return &(*this); }
    bool operator==( const Iterator& rhs ) { return _current == rhs._current; }
    bool operator!=( const Iterator& rhs ) { return !(*this == rhs); }
    Iterator(ListNode* node): _current(node) {}
  };
};

}

/** ArrayContainer implementation */
template<class C>
inline bool cgen::ArrayContainer<C>::add(C* obj)
{
  if( _size == _capacity) { return false; }
  _items[_size] = obj;
  ++_size;
  return true;
}

template<class C>
inline C* cgen::ArrayContainer<C>::pop()
{
  if( _size <= 0 )  return NULL;
  C* tmp = _items[_size - 1];
  _items[_size - 1] = NULL;
  _size--;
  return tmp;
}

template<class C>
inline void cgen::ArrayContainer<C>::clear()
{
  for( int i=_size; i>0; i--)
  {
    delete _items[_size - 1];
    _items[_size - 1] = NULL;
    --_size;
  }
}

/** StackContainer definitions of methods */
inline double cgen::Circle::area()
{
  return 3.14 * std::pow(radius, 2);
}

template<class C>
inline void cgen::StackContainer<C>::add(C* obj)
{ 
  _items = new ListNode(obj, _items); ++_size;
}

template<class C>
inline C* cgen::StackContainer<C>::pop()
{ 
  if( _items == NULL ) return NULL;
  ListNode* tmp = _items;
  C* item = _items->_item;
  _items = _items->_next;
  delete tmp;
  --_size;
  return item;
}

template<class C>
inline void cgen::StackContainer<C>::clear()
{
  //FIXME: We don't need another temp variable. Can just refer to _items
  ListNode* node = _items;
  ListNode* tmp = NULL;
  // for( ListNode* node = _items; node != NULL; node = node->_next)
  while( node != NULL )
  {
    tmp = node;
    node = node->_next;
    delete tmp->_item;
    delete tmp;
    --_size;
  }
  _items = NULL; 
}

#endif /* _GENERICS_EXAMPLE_H_ */

