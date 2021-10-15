#include <iostream>


static size_t calc_array_size(size_t num_of_elements);


static size_t calc_array_size(size_t num_of_elements) {
  for (size_t array_size = 2; ; array_size *= 2) {
    if (array_size / 2 >= num_of_elements) {
      return array_size;
    }
  }
  return 0;
}


template <class T>
Vector<T>::Vector() :
  array(nullptr),
  array_size(0),
  num_of_elements(0) {}


template <class T>
Vector<T>::Vector(size_t num_of_elements, const T& element) :
  array(new T*[calc_array_size(num_of_elements)]),
  array_size(calc_array_size(num_of_elements)),
  num_of_elements(num_of_elements) {
  for (size_t i = 0; i < num_of_elements; i++) {
    array[i] = new T(element);
  }
}


template <class T>
Vector<T>::~Vector() {
  clean();
}


template <class T>
Vector<T>::Vector(const Vector<T>& vec) :
  array(new T*[vec.array_size]),
  array_size(vec.array_size),
  num_of_elements(vec.num_of_elements) {
  for (size_t i = 0; i < num_of_elements; i++) {
    array[i] = new T(*vec.array[i]);
  }
}


template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& vec) {
  if (this == &vec) {
    return *this;
  }
  clean();
  array = new T*[vec.array_size];
  array_size = vec.array_size;
  num_of_elements = vec.num_of_elements;
  for (size_t i = 0; i < num_of_elements; i++) {
    array[i] = new T(*vec.array[i]);
  }
  return *this;
}


template <class T>
size_t Vector<T>::size() const {
  return num_of_elements;
}


template <class T>
bool Vector<T>::empty() const {
  return (num_of_elements == 0);
}


template <class T>
typename Vector<T>::Status Vector<T>::clean() {
  if (!empty()) {
    for (size_t i = 0; i < num_of_elements; i++) {
      delete array[i];
    }
    delete[] array;
    array = nullptr;
    array_size = 0;
    num_of_elements = 0;
    return Vector<T>::Status::SUCCESS;
  }
  return Vector<T>::Status::VECTOR_IS_EMPTY;
}


template <class T>
void Vector<T>::print() const {
  std::cout << "printing vector:" << std::endl;
  if (empty()) {
    std::cout << "vector is empty." << std::endl;
    return;
  }
  std::cout << "vector contains " << num_of_elements << " elements." << std::endl;
  for (size_t i = 0; i < num_of_elements; i++) {
    std::cout << "element[" << i << "]: " << *array[i] << std::endl;;
  }
}


template <class T>
void Vector<T>::sort() {
  if (empty()) {
    return;
  }
  for (size_t i = num_of_elements - 1; i > 0; i--) {
    for (size_t j = 0; j < i; j++) {
      if (*array[j] > *array[j+1]){
        T* temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
      }
    }
  }
}


template <class T>
bool Vector<T>::exists(const T& element) const {
  for (size_t i = 0; i < num_of_elements; i++) {
    if (*array[i] == element) {
      return true;
    }
  }
  return false;
}


template <class T>
typename Vector<T>::Status Vector<T>::push_back(const T& element) {
  if (empty()) {
    return push_back_first_element(element);
  } else if (need_resize(Vector<T>::ResizeType::ENLARGE)) {
    return enlrge_and_push_back(element);
  } else {
    return normal_push_back(element);
  }
}


template <class T>
typename Vector<T>::Status Vector<T>::pop_back() {
  if (empty()) {
    return Vector<T>::Status::VECTOR_IS_EMPTY;
  } else if (num_of_elements == 1) {
    return pop_back_single_element();
  } else if (need_resize(Vector<T>::ResizeType::SHRINK)) {
    return shrink_and_pop_back();
  } else {
    return normal_pop_back();
  }
}


template <class T>
typename Vector<T>::Status Vector<T>::pop_front() {
  if (empty()) {
    return Vector<T>::Status::VECTOR_IS_EMPTY;
  }
  return remove(*array[0]);
}


template <class T>
typename Vector<T>::Status Vector<T>::remove(const T& element) {
  if (empty()) {
    return Vector<T>::Status::VECTOR_IS_EMPTY;
  }
  if (exists(element) && num_of_elements == 1) {
    clean();
    return Vector<T>::Status::SUCCESS;
  }
  for (size_t i = 0; i < num_of_elements; i++) {
    if (*array[i] == element) {
      T* to_delete = array[i];
      if (need_resize(Vector<T>::ResizeType::SHRINK)) {
        size_t new_array_size = array_size / 2;
        resize_array(new_array_size);
      }
      for (size_t j = i; j < num_of_elements - 1; j++) {
        array[j] = array[j + 1];
      }
      num_of_elements--;
      delete to_delete;
      return Vector<T>::Status::SUCCESS;
    }
  }
  return Vector<T>::Status::ELEMENT_NOT_FOUND;
}


template <class T>
T& Vector<T>::operator[](size_t index) {
  if (index >= num_of_elements) {
    print_error(Vector<T>::Error::INVALID_ACCESS);
    exit(1);
  }
  return *array[index];
}


template <class T>
const T& Vector<T>::operator[](size_t index) const {
  if (index >= num_of_elements) {
    print_error(Vector<T>::Error::INVALID_ACCESS);
    exit(1);
  }
  return *array[index];
}


template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& vec) const {
  Vector<T> new_vec(*this);
  for (size_t i = 0; i < vec.num_of_elements; i++) {
    new_vec.push_back(*vec.array[i]);
  }
  return new_vec;
}


template <class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& vec) {
  for (size_t i = 0; i < vec.num_of_elements; i++) {
    push_back(*vec.array[i]);
  }
  return *this;
}


template <class T>
Vector<T> Vector<T>::operator-(const Vector<T>& vec) const {
  Vector<T> new_vec(*this);
  for (size_t i = 0; i < vec.num_of_elements; i++) {
    new_vec.remove(*vec.array[i]);
  }
  return new_vec;
}


template <class T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& vec) {
  for (size_t i = 0; i < vec.num_of_elements; i++) {
    remove(*vec.array[i]);
  }
  return *this;
}


template <class T>
Vector<T> Vector<T>::operator*(const Vector<T>& vec) const {
  if (num_of_elements != vec.num_of_elements) {
    return *this;
  }
  Vector<T> new_vec;
  for (size_t i = 0; i < num_of_elements; i++) {
    T prod = *array[i] * *vec.array[i];
    new_vec.push_back(prod);
  }
  return new_vec;
}


template <class T>
Vector<T>& Vector<T>::operator*=(const Vector<T>& vec) {
  if (num_of_elements != vec.num_of_elements) {
    return *this;
  }
  for (size_t i = 0; i < num_of_elements; i++) {
    T prod = (*array[i]) * (*vec.array[i]);
    delete array[i];
    array[i] = new T(prod);
  }
  return *this;
}


template <class T>
bool Vector<T>::operator==(const Vector<T>& vec) const {
  if (num_of_elements != vec.num_of_elements) {
    return false;
  }
  for (size_t i = 0; i < num_of_elements; i++) {
    if (*array[i] != *vec.array[i]) {
      return false;
    }
  }
  return true;
}


template <class T>
bool Vector<T>::operator!=(const Vector<T>& vec) const {
  return !(*this == vec);
}


template <class T>
Vector<T>& Vector<T>::operator<<(const T& element) {
  push_back(element);
  return *this;
}


template <class T>
void Vector<T>::operator>>(T& element) {
  if (empty()) {
    return;
  }
  element = *array[num_of_elements - 1];
  pop_back();
}


template <class T>
Vector<T>& operator>>(const T& element, Vector<T>& vec) {
  // TO-DO: enable push_front after implementing this method
  // vec.push_front(element);
  vec.push_back(element);
  return vec;
}


template <class T>
void operator<<(T& element, Vector<T>& vec) {
  if (vec.empty()) {
    return;
  }
  element = vec[0];
  vec.pop_front();
}


template <class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  if (vec.empty()) {
    return os;
  }
  for (size_t i = 0; i < vec.size() - 1; i++) {
    os << vec[i] << ", ";
  }
  os << vec[vec.size() - 1];
  return os;
}


template <class T>
bool Vector<T>::need_resize(Vector<T>::ResizeType resize_type) const {
  if (resize_type == Vector<T>::ResizeType::ENLARGE) {
    return (num_of_elements >= array_size / 2);
  } else if (resize_type == Vector<T>::ResizeType::SHRINK) {
    return (num_of_elements <= array_size / 4);
  }
  return false;
}


template <class T>
void Vector<T>::resize_array(size_t new_array_size) {
  T** new_array = new T*[new_array_size];
  for (size_t i = 0; i < num_of_elements; i++) {
    new_array[i] = array[i];
  }
  delete[] array;
  array = new_array;
  array_size = new_array_size;
}


template <class T>
typename Vector<T>::Status Vector<T>::push_back_first_element(const T& element) {
  array = new T*[2];
  array[0] = new T(element);
  array_size = 2;
  num_of_elements++;
  return Vector<T>::Status::SUCCESS;
}


template <class T>
typename Vector<T>::Status Vector<T>::enlrge_and_push_back(const T& element) {
  size_t new_array_size = array_size * 2;
  resize_array(new_array_size);
  array[num_of_elements] = new T(element);
  num_of_elements++;
  return Vector<T>::Status::SUCCESS;
}


template <class T>
typename Vector<T>::Status Vector<T>::normal_push_back(const T& element) {
  array[num_of_elements] = new T(element);
  num_of_elements++;
  return Vector<T>::Status::SUCCESS;
}


template <class T>
typename Vector<T>::Status Vector<T>::pop_back_single_element() {
  clean();
  return Vector<T>::Status::SUCCESS;
}


template <class T>
typename Vector<T>::Status Vector<T>::shrink_and_pop_back() {
  size_t new_array_size = array_size / 2;
  resize_array(new_array_size);
  delete array[num_of_elements - 1];
  num_of_elements--;
  return Vector<T>::Status::SUCCESS;
}


template <class T>
typename Vector<T>::Status Vector<T>::normal_pop_back() {
  delete array[num_of_elements - 1];
  num_of_elements--;
  return Vector<T>::Status::SUCCESS;
}


template <class T>
void Vector<T>::print_error(Vector<T>::Error error) const {
  switch (error) {
    case Vector<T>::Error::INVALID_ACCESS:
      std::cout << "invalid access to vector" << std::endl;
      break;
    default:
      std::cout << "undefined error" << std::endl;
  }
}
