#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "BasicString.h"
#include "Node.h"
#include "Node.cpp"
#include "List.h"
#include "List.cpp"
#include "inputTranslator.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    List<BasicString> example;
    BasicString usrInput;
    int wholeSections = 0;
    int sectionCounter = 0;
    int deletedCounter = 0;
    bool addToSelector = true;
    bool CSSswitch = true;
    example.createSection();
    while (cin >> usrInput) {
        if (usrInput == "????") {
            CSSswitch = false;
            continue;
        }
        

        if (CSSswitch) {
            readCSS(example, usrInput, wholeSections, sectionCounter, addToSelector);
        }
        else {
            readCommands(example, usrInput, wholeSections, CSSswitch, sectionCounter, deletedCounter);
        }
       
    }
     Node<BasicString>* searched = example.getHead();
    for (int i = 0; i < example.getSize(); i++) {
        Node<BasicString>* tempAttr = searched;
        for (int j = 0; j < ARRAY_SIZE; j++) {
            Node<BasicString>* temp = &tempAttr[j];
            if (temp == nullptr || temp->deleted) {
                continue;
            }
            temp->deleteSection(temp);
        }
        searched = searched->next;
        delete[] tempAttr;

    }
    return 0;
}