// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& data) : data(data), next(nullptr) {}
  };
  Node* head;

 public:
  TPQueue() : head(nullptr) {}
  bool is_empty() const {
    return head == nullptr;
  }
  void push(const T& data) {
    Node* newNode = new Node(data);
    if (is_empty() || data.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
    } else {
      Node* current = head;
      while (current->next != nullptr &&
        data.prior <= current->next->data.prior) {
        current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;
    }
  }
  T pop() {
    if (is_empty()) {
      throw std::runtime_error("Queue is empty");
    }
    Node* temp = head;
    T data = temp->data;
    head = head->next;
    delete temp;
    return data;
  }
  ~TPQueue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
