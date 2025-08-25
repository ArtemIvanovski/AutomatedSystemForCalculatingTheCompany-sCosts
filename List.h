#pragma once
#include "Liberies.h"
#include "ListNode.h"
#include "CustomException.h"

template <typename T>
class List {
private:
    ListNode<T>* head;

public:
    List();
    ~List();
    int length() const;
    T getDataById(int id);
    int getOwnValueProject(int id);
    int getValueProject(int id);
    int checkAuthorize(const string& inputLogin, const string& inputPassword);
    void removeFirst();
    void removeLast();
    void append(const T& value);
    void clear();
    void removeData(const T& value);
    
    void sortByDescription() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getDescription() > nextNode->data.getDescription()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }

    void sortById() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getId() > nextNode->data.getId()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }
    void sortByDate() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getStartDate() > nextNode->data.getStartDate()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }

    void sortByStatus() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getStatus() > nextNode->data.getStatus()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }

    void sortByName() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getName() > nextNode->data.getName()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }

    void sortByEmail() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getEmail() > nextNode->data.getEmail()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }

    void sortBySpecializationLevel() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getSpecializationLevel() > nextNode->data.getSpecializationLevel()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }

    void sortByCompletedAnalysesCount() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getCompletedAnalysesCount() > nextNode->data.getCompletedAnalysesCount()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }

    void sortByAmount() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getAmount() > nextNode->data.getAmount()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }

    void sortByDirectExpenseType() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getDirectExpenseType() > nextNode->data.getDirectExpenseType()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }
    
    void sortByIndirectExpenseType() {
        int n = length();
        if (n <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            ListNode<T>* current = head;
            ListNode<T>* nextNode = head->next;

            for (int i = 0; i < n - 1; ++i) {
                if (current->data.getIndirectExpenseType() > nextNode->data.getIndirectExpenseType()) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;
            }
            --n;

        } while (swapped);
    }


    bool find(int value) {
        ListNode<T>* current = head;
        while (current != nullptr) {
            if (current->data.getId() == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool findByUserId(int value) {
        ListNode<T>* current = head;
        while (current != nullptr) {
            if (current->data.getUserId() == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    List<T>& operator=(const List<T>& other) {
        if (this != &other) {
            clear();

            ListNode<T>* otherCurrent = other.head;
            while (otherCurrent != nullptr) {
                append(otherCurrent->data);
                otherCurrent = otherCurrent->next;
            }
        }
        return *this;
    }
    T& operator[](int index) {
        if (index < 0 || index >= length()) {
            throw CustomException("Index out of bounds.");
        }

        ListNode<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        return current->data;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= length()) {
            throw CustomException("Index out of bounds.");
        }

        ListNode<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        return current->data;
    }
};

template <typename T>
List<T>::List() : head(nullptr) {}

template <typename T>
List<T>::~List() {
    //clear();
}


template <typename T>
int List<T>::length() const {
    int count = 0;
    ListNode<T>* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    
    return count;
}

template<typename T>
T List<T>::getDataById(int id)
{
    ListNode<T>* current = head;
    while (current != nullptr) {
        if (current->data.getId() == id)
            return current->data;
        current = current->next;
    }
    return T();
}

template<typename T>
int List<T>::getOwnValueProject(int id)
{
    int value = 0;
    ListNode<T>* current = head;
    while (current != nullptr) {
        if (current->data.getIdCreator() == id)
            value++;
        current = current->next;
    }
    return value;
}

template<typename T>
int List<T>::getValueProject(int id)
{
    int value = 0;
    ListNode<T>* current = head;
    while (current != nullptr) {
        if (current->data.hasManagerId(id) || current->data.hasAnalystId(id))
            value++;
        current = current->next;
    }
    return value;
}

template<typename T>
int List<T>::checkAuthorize(const string& inputLogin, const string& inputPassword)
{
    ListNode<T>* current = head;
    int id;
    while (current != nullptr) {
        id = current->data.verify(inputLogin, inputPassword);
        if (id != 0)
            return id;
        current = current->next;
    }
    throw CustomException("Неправильный логин или пароль");
}

template <typename T>
void List<T>::removeFirst() {
    if (head == nullptr) {
        throw CustomException("List is empty.");
        return;
    }

    ListNode<T>* temp = head;
    head = head->next;
    delete temp;
}

template <typename T>
void List<T>::removeLast() {
    if (head == nullptr) {
        throw CustomException("List is empty.");
        return;
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    ListNode<T>* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
}

template <typename T>
void List<T>::append(const T& value) {
    ListNode<T>* newNode = new ListNode<T>(value);
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
        return;
    }

    ListNode<T>* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
}

template <typename T>
void List<T>::clear() {
    while (head != nullptr) {
        removeFirst();
    }
}

template <typename T>
void List<T>::removeData(const T& value) {
    ListNode<T>* current = head;
    ListNode<T>* prev = nullptr;

    while (current != nullptr) {
        if (current->data.getId() == value.getId()) {
            if (prev == nullptr) {
                removeFirst();
                current = head;
            }
            else {
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

