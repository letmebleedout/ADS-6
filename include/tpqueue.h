// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
  char ch;
  int prior;
};

template<typename T>
class TPQueue {
  private:
    struct Node {
      T data;
      Node* next;
      explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;

  public:
    TPQueue() : head(nullptr) {}
    ~TPQueue();

    void push(const T& value);
    T pop();
    bool isEmpty() const;
};

template<typename T>
TPQueue<T>::~TPQueue() {
  while (!isEmpty()) {
    pop();
  }
}

template<typename T>
void TPQueue<T>::push(const T& value) {
  Node* newNode = new Node(value);

  if (!head || value.prior > head->data.prior) {
    newNode->next = head;
    head = newNode;
    return;
  }

  Node* current = head;
  while (current->next && current->next->data.prior >= value.prior) {
    current = current->next;
  }

  newNode->next = current->next;
  current->next = newNode;
}

template<typename T>
T TPQueue<T>::pop() {
  if (isEmpty()) {
    throw std::runtime_error("Queue is empty");
  }

  Node* temp = head;
  T result = temp->data;
  head = head->next;
  delete temp;
  return result;
}

template<typename T>
bool TPQueue<T>::isEmpty() const {
  return head == nullptr;
}

#endif  // INCLUDE_TPQUEUE_H_
