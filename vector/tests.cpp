#include "vector.h"
#include <iostream>
#include <cassert>


// Vector();
// Vector(size_t num_of_elements, const T& element = T());
// ~Vector();
// Vector(const Vector& vec);
// Vector& operator=(const Vector<T>& vec);
// size_t size() const;
// bool empty() const;
// Status clean();
// Status push_back(const T& element);
// Status pop_back();
// T& operator[](size_t index);
// bool operator==(const Vector<T>& vec) const;
// bool operator!=(const Vector<T>& vec) const;
void test0() {
  const unsigned int size = 5000;
  Vector<unsigned int> v1;
  for (size_t i = 0; i < size; i++) {
    assert(v1.push_back(i) == Vector<unsigned int>::Status::SUCCESS);
    assert(v1.push_back(i) == Vector<unsigned int>::Status::SUCCESS);
    assert(v1.pop_back() == Vector<unsigned int>::Status::SUCCESS);
  }
  assert(v1.size() == size);
  assert(v1.clean() == Vector<unsigned int>::Status::SUCCESS);
  assert(v1.empty());
  for (size_t i = 0; i < size; i++) {
    assert(v1.push_back(i) == Vector<unsigned int>::Status::SUCCESS);
  }
  Vector<unsigned int> v2;
  v2 = v1;
  Vector<unsigned int> v3(v1);
  const unsigned int value = 5;
  Vector<unsigned int> v4(size, value);
  assert((v1 == v2) && (v2 == v3) && (v3 != v4));
  for (size_t i = 0; i < size; i++) {
    assert(v4[i] == value);
  }
}


// void print() const;
// void sort();
// bool exists(const T& element) const;
// Status remove(const T& element);
void test1() {
  Vector<unsigned int> v1;
  const unsigned int size = 5000;
  for (size_t i = 0; i < size; i++) {
    assert(v1.push_back(i) == Vector<unsigned int>::Status::SUCCESS);
  }
  assert(v1.exists(size/2));
  assert(!v1.exists(size*2));
  assert(v1.remove(size) == Vector<unsigned int>::Status::ELEMENT_NOT_FOUND);
  for (size_t i = 0; i < size; i++) {
    assert(v1.remove(i) == Vector<unsigned int>::Status::SUCCESS);
  }
  for (size_t i = 0; i < size; i++) {
    assert(v1.remove(i) != Vector<unsigned int>::Status::SUCCESS);
  }
  assert(v1.empty());
  for (size_t i = size; i >= 1; i--) {
    v1.push_back(i);
  }
  v1.sort();
  for (size_t i = 0; i < size - 1; i++) {
    assert(v1[i] <= v1[i+1]);
  }
  for (size_t i = 50; i <= size; i++) {
    assert(v1.remove(i) == Vector<unsigned int>::Status::SUCCESS);
  }
  v1.print();
}


// Vector<T> operator+(const Vector<T>& vec) const;
// Vector<T>& operator+=(const Vector<T>& vec);
// Vector<T> operator-(const Vector<T>& vec) const;
// Vector<T>& operator-=(const Vector<T>& vec);
// Vector<T> operator*(const Vector<T>& vec);
// Vector<T>& operator*=(const Vector<T>& vec);
// Vector<T>& operator<<(const T& element);
// void operator>>(T& element);
void test2() {
  const unsigned int size = 200;
  const unsigned int value = 4;
  Vector<unsigned int> v1(size, value);
  Vector<unsigned int> v1_save(v1);
  Vector<unsigned int> v2(size, value);
  Vector<unsigned int> v3 = v1 + v2;
  assert(v3.size() == size*2);
  Vector<unsigned int> v4 = v1 - v2;
  assert(v4.empty());
  Vector<unsigned int> v5 = v1 * v2;
  for (size_t i = 0; i < size; i++) {
    assert(v5[i] == v1[i] * v2[i]);
  }
  v1 += v2;
  assert(v1.size() == size*2);
  v1 -= v2;
  assert(v1 == v1_save);
  v1 = Vector<unsigned int>(size, value);
  v2 = Vector<unsigned int>(size, value);
  v1 *= v2;
  assert(v5 == v1);
  v1 = Vector<unsigned int>();
  const unsigned int new_size = 6;
  v1 << 1 << 2 << 3 << 4 << 5 << 6;
  v1.print();
  assert(v1.size() == new_size);
  unsigned int element = 0;
  for (size_t i = new_size; i >= 1; i--) {
    v1 >> element;
    assert(i == element);
  }
}


// The following functions are not Vector methods
// Vector<U>& operator>>(const U& element, Vector<U>& vec);
// void operator<<(const U& element, Vector<U>& vec);
// std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);
void test3() {
  Vector<unsigned int> v1;
  (unsigned int)1 >> v1;
  (unsigned int)2 >> v1;
  (unsigned int)3 >> v1;
  (unsigned int)4 >> v1;
  (unsigned int)5 >> v1;
  std::cout << "size: " << v1.size() << std::endl;
  assert(v1.size() == 5);
  std::cout << "printing v1:" << std::endl;
  std::cout << v1 << std::endl;
  unsigned int element = 0;
  for (size_t i = 1; i <= 5; i++) {
    element << v1;
    assert(element == i);
    std::cout << "next element: " << element << std::endl;
  }
}
