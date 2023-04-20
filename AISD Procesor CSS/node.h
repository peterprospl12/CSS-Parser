#pragma once
#include <iostream>
#include "BasicString.h"
template <typename Type> class List; 


template <typename Type> 

class Node {
public:
	Node<Type>* prev;
	Node<Type>* next;
	List<Type> attributes;
	List<Type> selectors;
	Type value;
	bool deleted;
	int usedSections = 0;
public:
	Node();
	Node(Type value);
	Type GetValue();
	void SetValue(Type* value);
	
	Node<Type>* GetPrev() const;
	Node<Type>* GetNext() const;
	bool deleteSection(Node<Type>* firstSection);
	bool deleteAttribute(int sectionNumber, BasicString attribute);
	void SetPrevNode(Node<Type>* prevNode);
	void SetNextNode(Node<Type>* nextNode);
	
	Node<Type>* GetPrevNode() const;
	Node<Type>* GetNextNode() const;
	void writeList();
	friend std::ostream& operator<<(std::ostream& os, const Node<Type>& node);
	~Node<Type>();
};