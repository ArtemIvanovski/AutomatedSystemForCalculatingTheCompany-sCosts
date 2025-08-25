#pragma once

template <typename T>
class ListNode {
public:
    T data;
    ListNode* next;
    ListNode(const T& value);
};

template <typename T>
ListNode<T>::ListNode(const T& value) : data(value), next(nullptr) {}
