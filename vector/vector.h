#ifndef VECTOR_H
#define VECTOR_H


#include <iostream>


template <class T>
class Vector {
public:
  enum class Status {
    SUCCESS,
    FAILURE,
    NULL_ARG,
    VECTOR_IS_EMPTY,
    ELEMENT_NOT_FOUND
  };
  Vector();
  Vector(size_t num_of_elements, const T& element = T());
  ~Vector();
  Vector(const Vector& vec);
  Vector& operator=(const Vector<T>& vec);
  size_t size() const;
  bool empty() const;
  Status clean();
  void print() const;
  void sort();
  bool exists(const T& element) const;
  Status push_back(const T& element);
  Status pop_back();
  // TO-DO:
  // push_front() will be implemented using insert(iterator, element)
  // method which will be available after adding iterator support
  // Status push_front(const T& element);
  Status pop_front();
  // TO-DO:
  // insert() will be implemented after adding iterator support
  // Status insert(Iterator& it, const T& element);
  Status remove(const T& element);
  T& operator[](size_t index);
  const T& operator[](size_t index) const;
  Vector<T> operator+(const Vector<T>& vec) const;
  Vector<T>& operator+=(const Vector<T>& vec);
  Vector<T> operator-(const Vector<T>& vec) const;
  Vector<T>& operator-=(const Vector<T>& vec);
  Vector<T> operator*(const Vector<T>& vec) const;
  Vector<T>& operator*=(const Vector<T>& vec);
  bool operator==(const Vector<T>& vec) const;
  bool operator!=(const Vector<T>& vec) const;
  Vector<T>& operator<<(const T& element);
  void operator>>(T& element);
private:
  enum class ResizeType {
    ENLARGE,
    SHRINK
  };
  enum class Error {
    INVALID_ACCESS
  };
  T** array;
  size_t array_size;
  size_t num_of_elements;
  bool need_resize(ResizeType resize_type) const;
  void resize_array(size_t new_array_size);
  Status push_back_first_element(const T& element);
  Status enlrge_and_push_back(const T& element);
  Status normal_push_back(const T& element);
  Status pop_back_single_element();
  Status shrink_and_pop_back();
  Status normal_pop_back();
  void print_error(Error error) const;
  void do_sort();
};


#include "vector_imp.h"


#endif
