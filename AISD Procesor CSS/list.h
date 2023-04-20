#pragma once
#include "Node.h"
#include "BasicString.h"
#include <iostream>

template <typename Type>

class List {
private:
    Node<Type>* head;
    Node<Type>* tail;
    int size;
    int sectionSize;
public:
    List();
    void insert(Type data);
    void createSection();

    
    int getSize();
    int getSectionSize();
    
    Node<Type>* getHead() const;
    Node<Type>* getTail();
    Node<Type>* getBlock(int sectionCounter);
    
    bool isAttrExists(BasicString attribute, BasicString value);
    bool isSelectorExists(BasicString selector);
    
    void decrementSize();
    void setSize(int tempSize);
    void setHead(Node<Type>* newHead);
    void setTail(Node<Type>* newTail);

    ~List();

};