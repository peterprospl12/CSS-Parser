#include <iostream>
#include "Node.h"
#include "BasicString.h"
template <typename Type>
Node<Type>::Node() {
    this->prev = nullptr;
    this->next = nullptr;
    this->deleted = false;
}

template <typename Type>
Node<Type>::Node(Type value) {
	this->prev = nullptr;
	this->next = nullptr;
	this->value = value;
    this->deleted = false;
}


template <typename Type>

bool Node<Type>::deleteSection(Node<Type>* firstSection) {
    Node<Type>* tempAttrNode = attributes.getHead();
    Node<Type>* tempSelectNode = selectors.getHead();
    Node<Type>* tempNode;

    for (int i = 0; i < selectors.getSize(); i++) {
        tempNode = tempSelectNode->next;
        if (tempSelectNode != nullptr) {
            delete tempSelectNode;
        }
        tempSelectNode = tempNode;
    }

    for (int i = 0; i < attributes.getSize(); i++) {
        tempNode = tempAttrNode->next;
        if (tempAttrNode != nullptr) {
            delete tempAttrNode;
        }
        tempAttrNode = tempNode;
    }
    firstSection->usedSections -= 1;

    return true;
}

template <typename Type>
bool Node<Type>::deleteAttribute(int sectionNumber, BasicString attribute) {
    Node<Type>* tempAttrNode = attributes.getHead();
    bool removed = false;
    if (this->deleted) {
        return false;
    }

    for (int i = 1; i <= attributes.getSize(); i++) {
        if (tempAttrNode == nullptr) {
            return false;
        }
        if (tempAttrNode->value.getFirstString() == attribute) {
            if (i > 1) {
                tempAttrNode->prev->next = tempAttrNode->next;
            }
            else {
                this->attributes.setHead(tempAttrNode->next);
            }
            if (i < attributes.getSize()) {
                tempAttrNode->next->prev = tempAttrNode->prev;
            }
            else {
                this->attributes.setTail(tempAttrNode->prev);
            }
            attributes.decrementSize();
            delete tempAttrNode;
            removed = true;
            break;
        }
        tempAttrNode = tempAttrNode->next;
    }
    if (attributes.getSize() == 0) {
        std::cout << sectionNumber << ",D," << attribute << " == deleted" << std::endl;
        return true;
    }
    if (removed) {
        std::cout << sectionNumber << ",D," << attribute << " == deleted" << std::endl;
    }
    return false;

}

template <typename Type>
void Node<Type>::writeList() {
    std::cout << "Znaczniki:" << std::endl;
    std::cout << this->selectors << std::endl;
    std::cout << "Atrybuty:" << std::endl;
    std::cout << this->attributes << std::endl;
}

template <typename Type>
Node<Type>::~Node() {

}
