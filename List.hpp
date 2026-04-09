#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

  // so adding these 4 below 

  List();

  ~List();

 // copy constrctor 
  List(const List &other);

  // assigns a copy of other to this
  List &operator=(const List &other);




  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty


  // define new var Lsize 
  int Lsize;

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.

    //construct  default iterator
    Iterator();



    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.



    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.


    //returns  by reference
    T &operator*() const;

    //make iterator to point to next element and
    //         returnr a reference to it
    Iterator &operator++();

    // postfix incemeent use dummy int
    Iterator operator++(int);

    //EFFECTS: returns true if this Iterator and other refer to the same
    //         position in the same List
    bool operator==(const Iterator &other) const;

    //EFFECTS: returns true if this Iterator and other do not refer to the
    //         same position in the same List
    bool operator!=(const Iterator &other) const;



    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(listPtr);
      assert(*this != listPtr->begin());
      if (nodePtr) {
        nodePtr = nodePtr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        nodePtr = listPtr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *listPtr; //pointer to the List associated with this Iterator
    Node *nodePtr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here

    friend class List;


    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np);

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const;

  // return an Iterator pointing to "past the end"
  Iterator end() const;

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i);

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


template <typename T>
List<T>::List() : first(nullptr), last(nullptr), Lsize(0) {}


template <typename T>
List<T>::~List() {
  clear();
}


template <typename T>
List<T>::List(const List &other) : first(nullptr), last(nullptr), Lsize(0) {
  copy_all(other);
}


template <typename T>
List<T> &List<T>::operator=(const List &other) {

  if (this == &other) {
    return *this;
    // if they're alr eq
  }

  clear();
  copy_all(other);

  return *this;

}

// two easy  implementations
template <typename T>
bool List<T>::empty() const {
  return (Lsize == 0);
}

template <typename T>
int List<T>::size() const {
  return Lsize;
}

/// first points to first Node in list, or nullptr if list is empty

template <typename T>
T &List<T>::front() {

  assert(!empty());

  return first->datum;
}

/// last points to last Node in list, or nullptr if list is empty

template <typename T>
T &List<T>::back() {

assert(!empty());

  return last->datum;
}


// push front adds a new datum at the front.
template <typename T>
void List<T>::push_front(const T &datum) {

  Node *n = new Node;

  n->datum = datum;
  // prev norhtingn, next first
  n->prev = nullptr;
  n->next = first;

  // if list isnt empty, prev now points to n
  if (first) {
    first->prev = n;
  } 
  // if list is empty
  else {
    last = n;
  }

  first = n;
  // iterate list size. 
  ++Lsize;
}



  // almost the same as pusHfront
template <typename T>
void List<T>::push_back(const T &datum) {
  Node *n = new Node;

  n->datum = datum;
  n->next = nullptr;
  n->prev = last;

  if (last) {
    last->next = n;
  } 
  // if empty
  else {
    first = n;
  }

  last = n;
  ++Lsize;
}


// pop front removes the first entry in the list. 
template <typename T>
void List<T>::pop_front() {
  // can't remove an entry from an empty list. 
  assert(!empty());

  Node *prev = first;
  first = first->next;


  if (first) {
    first->prev = nullptr;
  } 
    // if list had 1 element 
  else {
    last = nullptr;
  }

  delete prev;
  --Lsize;
}

// pop back removes the last entry in the list. 
template <typename T>
void List<T>::pop_back() {
  // can't remove an entry from an empty list.
  assert(!empty());

  Node *prev = last;
  last = last->prev;

  if (last) {
    last->next = nullptr;
  } 
      // if list had 1 element 
  else {
    first = nullptr;
  }

  delete prev;
  --Lsize;
}


template <typename T>
void List<T>::clear() {
  // just clear list through while loop and 
  // popping fronts
  while (!empty()) {
pop_front();
  }
}


// copy all nodes to another list other
template <typename T>
void List<T>::copy_all(const List<T> &other) {
  assert(empty()); // make sure this list is empty

  // for loop stop condition is n because 
  // it's while n != nullptr
  Node *n = other.first;
  while (n != nullptr) {
    push_back(n->datum);
  n = n->next;
}
}


// iterator funcs
  // return an Iterator pointing to the first element
template <typename T>
typename List<T>::Iterator List<T>::begin() const {

  return Iterator(this, first);
}

  // return an Iterator pointing to "past the end"
template <typename T>
typename List<T>::Iterator List<T>::end() const {

  return Iterator(this, nullptr);
}



  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator i) {

  if(i.nodePtr == nullptr){
    return i;
  }

  // iterate list size.
  --Lsize;

  if(Lsize == 0){
    first = nullptr;
    last = nullptr;
    delete i.nodePtr;
    return end();
  }

  if(i.nodePtr == first){
    i.nodePtr = first->next;
    delete i.nodePtr->prev;
    first = i.nodePtr;
    first->prev = nullptr;
    return i;
  }

  if(i.nodePtr == last){
    i.nodePtr = last->prev;
    delete i.nodePtr->next;
    last = i.nodePtr;
    last->next = nullptr;
    return end();
  }

  Iterator temp = i;

  i.nodePtr->prev->next = i.nodePtr->next;
  i.nodePtr->next->prev = i.nodePtr->prev;
  i.nodePtr = i.nodePtr->next;

  delete temp.nodePtr;

  return i;

}



  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
template <typename T>
typename List<T>::Iterator List<T>::insert(Iterator i, const T &datum) {
  
  if(i.nodePtr == nullptr){
    push_back(datum);
    i.nodePtr = last;
    return i;
  }

  if(i.nodePtr == first){
    push_front(datum);
    i.nodePtr = first;
    return i;
  }
  
  Node *n = new Node;

  n->datum = datum;
  // prev norhtingn, next first
  n->prev = i.nodePtr->prev;
  n->next = i.nodePtr;

  i.nodePtr->prev = n;
  n->prev->next = n;

  // iterate list size. 
  ++Lsize;

  i.nodePtr = n;
  return i;
}


template <typename T>
List<T>::Iterator::Iterator() : listPtr(nullptr), nodePtr(nullptr) {}


template <typename T>
List<T>::Iterator::Iterator(const List *lp, Node *np) : listPtr(lp), nodePtr(np) {}


// retuurn data, simple just access datum
template <typename T>
T &List<T>::Iterator::operator*() const {
  assert(nodePtr);
  return nodePtr->datum;
}


//prefix ++
template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
  assert(listPtr);
  assert(nodePtr);

  nodePtr = nodePtr->next;
  return *this;
}


template <typename T>
// postfix operator
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
  Iterator copy = *this;
  // call prefix.
  operator++();
  return copy;
}


template <typename T>
bool List<T>::Iterator::operator==(const Iterator &other) const {

  return listPtr == other.listPtr && nodePtr == other.nodePtr;

}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator &other) const {
  // use == previously defined
  return !(*this == other);
}



#endif // Do not remove this. Write all your code above this line.
