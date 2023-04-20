#include "Node.h"
#include "List.h"
#include "BasicString.h"
#include <iostream>
#define ARRAY_SIZE 15
template <typename Type>

List<Type>::List() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template <typename Type>
void List<Type>::insert(Type data) {
    Node<Type>* section = new Node<Type>(data);
    if (this->head == nullptr) {
        this->head = section;
        this->tail = section;
    }
    else {
        this->tail->next = section;
        section->prev = this->tail;
        this->tail = section;
    }
    this->size++;

}

template <typename Type>
void List<Type>::createSection() {
    Node<Type>* section = new Node<Type>[ARRAY_SIZE];
    if (this->head == nullptr) {
        this->head = section;
        this->tail = section;
    }
    else {
        this->tail->next = section;
        section->prev = this->tail;
        this->tail = section;
    }
    this->size++;
}

template <typename Type>
bool List<Type>::isAttrExists(BasicString attribute, BasicString value) {
    Node<Type>* tempNode = this->head;
    for (int i = 0; i < this->size; i++) {
        if ((tempNode->value).getFirstString() == attribute) {
            BasicString tempStr(attribute + value);
            tempNode->value = tempStr;
            
            return true;
        }
        tempNode = tempNode->next;
    }
    return false;
}

template <typename Type>
bool List<Type>::isSelectorExists(BasicString selector) {
    Node<Type>* tempNode = this->head;
    for (int i = 0; i < this->size; i++) {
        if ((tempNode->value) == selector) {
            BasicString tempStr(selector);
            tempNode->value = tempStr;

            return true;
        }
        tempNode = tempNode->next;
    }
    return false;
}


template <typename Type>
int List<Type>::getSize() {
    return this->size;
}

template <typename Type>
int List<Type>::getSectionSize() {
    return this->sectionSize;
}

template <typename Type>
Node<Type>* List<Type>::getHead() const {
    return this->head;
}

template <typename Type>
Node<Type>* List<Type>::getTail() {
    return this->tail;
}

template <typename Type>
Node<Type>* List<Type>::getBlock(int sectionCounter) {
    Node<Type>* nodeToInsert = this->head;
    for (int i = 0; i < sectionCounter / ARRAY_SIZE; i++) {
        nodeToInsert = nodeToInsert->next;
    }
    return nodeToInsert;
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, const List<Type>& list) {
    Node<Type>* current = list.getHead();
    while (current != nullptr) {
        os << current->value;
        current = current->next;
        os << std::endl;
    }
    return os;
}

template <typename Type>
void List<Type>::setSize(int tempSize) {
    this->size = tempSize;
}

template <typename Type>
void List<Type>::decrementSize() {
    this->size--;
}

template <typename Type>
void List<Type>::setHead(Node<Type>* newHead) {
    this->head = newHead;
}

template <typename Type>
void List<Type>::setTail(Node<Type>* newTail) {
    this->tail = newTail;
}

template <typename Type>
List<Type>::~List() {

}