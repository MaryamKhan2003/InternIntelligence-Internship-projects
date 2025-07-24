// #pragma once

// template <typename T>
// Stack<T>::Stack(int size) : capacity(size), top(-1) {
//     arr = new T[capacity];
// }

// template <typename T>
// Stack<T>::~Stack() {
//     delete[] arr;
// }

// template <typename T>
// void Stack<T>::push(T value) {
//     if (isFull()) throw std::overflow_error("Stack overflow");
//     arr[++top] = value;
// }

// template <typename T>
// T Stack<T>::pop() {
//     if (isEmpty()) throw std::underflow_error("Stack underflow");
//     return arr[top--];
// }

// template <typename T>
// T Stack<T>::peek() const {
//     if (isEmpty()) throw std::underflow_error("Stack is empty");
//     return arr[top];
// }

// template <typename T>
// bool Stack<T>::isEmpty() const {
//     return top == -1;
// }

// template <typename T>
// bool Stack<T>::isFull() const {
//     return top == capacity - 1;
// }
