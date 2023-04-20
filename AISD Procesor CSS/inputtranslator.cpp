#include <iostream>
#include "BasicString.h"
#include "List.h"
#include "List.cpp"
#include "Node.cpp"
#include "Node.h"
#include "inputTranslator.h"

using std::cout;
using std::cin;
using std::endl;

void readCSS(List<BasicString>& example, BasicString& usrInput, int& wholeSections, int& sectionCounter, bool& addToSelector) {
    if (usrInput == ";") {
        return;
    }
    if (usrInput == "{") {
        addToSelector = false;
        return;
    }
    else if (usrInput.checkForChar("{")) {
        addToSelector = false;
    }

    if (usrInput == "}") {
        addToSelector = true;
        example.getTail()->usedSections += 1;
        sectionCounter++;
        wholeSections++;
        return;
    }
    
  
    
    if (addToSelector) {
        int arrayIndex = sectionCounter % ARRAY_SIZE;
        BasicString selector(usrInput);
        if (sectionCounter % ARRAY_SIZE == 0 && sectionCounter != 0 && sectionCounter / ARRAY_SIZE >= example.getSize()) {
            example.createSection();
        }

        Node<BasicString>* nodeToInsert = example.getTail();
        
        if (!selector.checkForChar(",")) {
            while (!selector.checkForChar(",")) {
                cin >> usrInput;
                BasicString tmpStr(usrInput);
                if (usrInput == "{") {
                    addToSelector = false;
                    break;
                }
                else if (usrInput.checkForChar("{") && tmpStr.separateWholeString("{") == "") {
                    addToSelector = false;
                    usrInput.replaceChar("{", "");
                    selector += usrInput;
                    break;

                }
                else if (usrInput.checkForChar("{")) {
                    addToSelector = false;
                    readAttributes(example, usrInput, *&wholeSections, *&sectionCounter, *&addToSelector);
                    break;
                }
                selector += usrInput;
            }
        }


        selector.replaceChar(",", "");
        if (nodeToInsert[arrayIndex].selectors.isSelectorExists(selector)) {
            return;
        }
        nodeToInsert[arrayIndex].selectors.insert(selector);
    }
    else {
        readAttributes(example, usrInput, *&wholeSections, *&sectionCounter, *&addToSelector);
    }
}
void readAttributes(List<BasicString>& example, BasicString& usrInput, int& wholeSections, int& sectionCounter, bool& addToSelector) {
    BasicString value;
    BasicString attribute = usrInput;
    Node<BasicString>* nodeToInsert = example.getTail();
    int arrayIndex = sectionCounter % ARRAY_SIZE;
    attribute.replaceChar("{", " ");
    
    if (attribute.checkForChar(":") && attribute.checkForChar(";")) {
        attribute.addSpace(":");
        value = attribute.separateWholeString(" ");
        value.replaceChar(";", " ");
        value.changeIntChar(0, " ");
        attribute = attribute.getFirstString();
        if (nodeToInsert[arrayIndex].attributes.isAttrExists(attribute, value)) {
            return;
        }
        nodeToInsert[arrayIndex].attributes.insert(attribute + value);
        return;
    }
    
    else {
        BasicString tempStr;
        tempStr = attribute.separateString(":", 0);
        value = attribute.separateString(":", 1);
        value.changeIntChar(0, " ");
        attribute = tempStr;
        
    }

    if (cin >> usrInput) {
        if (!usrInput.checkForChar(";")) {
            while (!usrInput.checkForChar(";")) {
                value += usrInput;
                cin >> usrInput;
            }
        }
        value += usrInput;

        value.replaceChar(";", " ");
        if (value.checkForChar("}")) {
            addToSelector = true;
            value.replaceChar("}", " ");
            nodeToInsert[arrayIndex].usedSections += 1;
            sectionCounter++;
            wholeSections++;
        }
        if (nodeToInsert[arrayIndex].attributes.isAttrExists(attribute, value)) {
            return;
        }
        nodeToInsert[arrayIndex].attributes.insert(attribute + value);
        

    }
}
void readCommands(List<BasicString>& example, BasicString usrInput, int& wholeSections, bool& CSSswitch, int& sectionCounter, int& deletedCounter) {
    if (usrInput == "****") {
        CSSswitch = true;
    }
    else if (usrInput == "?") {
        cout << "? == " << wholeSections << endl;
    }
    else {
        BasicString com1;
        BasicString com2;
        BasicString com3;
        BasicString word(usrInput);
        while (true) {

            if (word.countChars(",") < 2) {
                cin >> usrInput;
                word += usrInput;
                continue;
            }
            else if (word.countChars(",") == 2) {
                break;
            }
            else {
                return;
            }
            
            cin >> usrInput;
        }
        
        com1 = (word.separateString(",", 0));
        com2 = (word.separateString(",", 1));
        com3 = (word.separateString(",", 2));

        if (atoi(com1.str) && com2 == "S" && com3 == "?") {
            int inputNumber = atoi(com1.str);
            if (inputNumber > wholeSections) {
                return;
            }
            int j = 0;
            Node<BasicString>* searched = example.getHead();
            Node<BasicString>* searchedNode = &example.getHead()[0];
            for (int i = 0; i < inputNumber + j; i++) {
                if (i % ARRAY_SIZE == 0 && i != 0) {
                    searched = searched->next;
                }
                searchedNode = &searched[i % ARRAY_SIZE];

                if (searchedNode->deleted) {
                    j++;
                    if (i >= sectionCounter) {
                        return;
                    }
                }
            }
            int searchedSize;
            searchedSize = searchedNode->selectors.getSize();
            if (searched) {
                cout << atoi(com1.str) << ",S,? == " << searchedSize << std::endl;
            }

        }

        else if (atoi(com1.str) && com2 == "S" && atoi(com3.str)) {
            int inputNumber = atoi(com1.str);

            if (inputNumber > wholeSections) {
                return;
            }
            int j = 0;
            Node<BasicString>* searched = example.getHead();
            Node<BasicString>* searchedNode = &example.getHead()[0];
            for (int i = 0; i < inputNumber + j; i++) {
                if (i % ARRAY_SIZE == 0 && i != 0) {
                    searched = searched->next;
                }
                searchedNode = &searched[i % ARRAY_SIZE];

                if (searchedNode->deleted) {
                    j++;
                    if (i >= sectionCounter) {
                        return;
                    }
                }
            }
            if (atoi(com3.str) - 1 >= searchedNode->selectors.getSize()) {
                return;
            }

            searchedNode = searchedNode->selectors.getHead();
            for (int i = 0; i < atoi(com3.str) - 1; i++) {
                if (searchedNode->next == nullptr) {
                    return;
                }
                searchedNode = searchedNode->next;
            }
            
            cout << atoi(com1.str) << ",S," << atoi(com3.str) << " == " << searchedNode->value << std::endl;
            
        }
        
        
        else if (atoi(com1.str) && com2 == "A" && com3 == "?") {
            int inputNumber = atoi(com1.str);
            if (inputNumber > wholeSections) {
                return;
            }
            int j = 0;
            Node<BasicString>* searched = example.getHead();
            Node<BasicString>* searchedNode = &example.getHead()[0];
            for (int i = 0; i < inputNumber+j; i++) {
                if (i % ARRAY_SIZE == 0 && i != 0) {
                    searched = searched->next;
                }
                searchedNode = &searched[i % ARRAY_SIZE];
                
                if (searchedNode->deleted) {
                    j++;
                    if (i >= sectionCounter) {
                        return;
                    }
                }
            }
       
            
            int searchedSize;
            searchedSize = searchedNode->attributes.getSize();
            if (searched) {
                cout << atoi(com1.str) << ",A,? == " << searchedSize << std::endl;
            }
            
        }

        
        else if (atoi(com1.str) && com2 == "A" && atoi(com3.str) == 0) {
            int inputNumber = atoi(com1.str);

            if (inputNumber > wholeSections) {
                return;
            }
            int j = 0;
            Node<BasicString>* searched = example.getHead();
            Node<BasicString>* searchedNode = &example.getHead()[0];
            for (int i = 0; i < inputNumber + j; i++) {
                if (i % ARRAY_SIZE == 0 && i != 0) {
                    searched = searched->next;
                }
                searchedNode = &searched[i % ARRAY_SIZE];

                if (searchedNode->deleted) {
                    j++;
                    if (i >= sectionCounter) {
                        return;
                    }
                }
            }
            BasicString findedAttribute;
            int attrSize = searchedNode->attributes.getSize();
            searchedNode = searchedNode->attributes.getHead();
            for (int i = 0; i < attrSize; i++) {
                findedAttribute = searchedNode->value.separateString(" ", 0);
                if (findedAttribute == com3) {
                    BasicString temporary = (searchedNode->value).separateWholeString(" ");
                    cout << com1 << ",A," << com3 << " == " << (searchedNode->value).separateWholeString(" ") << endl;
                    break;
                }
                else {
                    searchedNode = searchedNode->next;
                }
            }
        }
        
        
        
        else if (atoi(com1.str) == 0 && com2 == "A" && com3 == "?") {
           
            int attrCounter = 0;
           
            Node<BasicString>* searched = example.getHead();
            Node<BasicString>* searchedNode = &example.getHead()[0];
            Node<BasicString>* attrNode;
            for (int i = 0; i < sectionCounter; i++) {
                if (i % ARRAY_SIZE == 0 && i != 0) {
                    searched = searched->next;
                }
                searchedNode = &searched[i % ARRAY_SIZE];

                if (searchedNode->deleted) {
                    continue;
                }
                attrNode = searchedNode->attributes.getHead();
                for (int k = 0; k < searchedNode->attributes.getSize(); k++) {
                    if ((attrNode->value).getFirstString() == com1.str) {
                        attrCounter++;
                        break;
                    }
                    attrNode = attrNode->next;
                }
            }
            cout << com1.str << ",A,? == " << attrCounter << endl;
        }
        else if (atoi(com1.str) == 0 && com2 == "S" && com3 == "?") {
            
            int selectCounter = 0;
            Node<BasicString>* searched = example.getHead();
            Node<BasicString>* searchedNode = &example.getHead()[0];
            Node<BasicString>* selectNode;
            for (int i = 0; i < sectionCounter; i++) {
                if (i % ARRAY_SIZE == 0 && i != 0) {
                    searched = searched->next;
                }
                searchedNode = &searched[i % ARRAY_SIZE];

                if (searchedNode->deleted) {
                    continue;
                }
                selectNode = searchedNode->selectors.getHead();
                for (int k = 0; k < searchedNode->selectors.getSize(); k++) {
                    if ((selectNode->value) == com1.str) {
                        selectCounter++;
                    }
                    selectNode = selectNode->next;
                }
            }
            cout << com1.str << ",S,? == " << selectCounter << endl;
        }

        else if (atoi(com1.str) == 0 && com2 == "E" && atoi(com3.str) == 0) {
            if (com3.str == nullptr) {
                return;
            }
            Node<BasicString>* tempSelect;
            Node<BasicString>* tempAttr;
            List<BasicString> tempAttrList;
            List<BasicString> tempSectList;
            int j = 1;
            Node<BasicString>* searched = example.getTail();
            Node<BasicString>* searchedNode = &example.getTail()[searched->usedSections];
            j = searched->usedSections;
            for(int i = 0; i < sectionCounter ; i++) {
                if (j<0) {
                    searched = searched->prev;
                    j = searched->usedSections;
                }
                searchedNode = &searched[j--];

                if (searchedNode == nullptr || searchedNode->deleted) {
                    continue;
                }
                tempSectList = searchedNode->selectors;
                tempSelect = searchedNode->selectors.getHead();
                if (tempSelect == nullptr) {
                    continue;
                }
                 for (int j = 0; j < tempSectList.getSize();j++) {
                    if (tempSelect != nullptr) {
                        if (tempSelect->value == com1.str) {
                            tempAttrList = searchedNode->attributes;
                            tempAttr = searchedNode->attributes.getHead();
                            for (int k = 0; k < tempAttrList.getSize(); k++) {
                                if ((tempAttr->value).getFirstString() == com3.str) {
                                    cout << com1.str << ",E," << com3.str << " == " << (tempAttr->value).separateWholeString(" ") << endl;
                                    return;
                                }
                                tempAttr = tempAttr->next;
                            }
                        }
                        tempSelect = tempSelect->next;
                    }
                    break;
                }
            }

        }
        else if (atoi(com1.str) && com2 == "D" && com3 == "*") {
            int inputNumber = atoi(com1.str);
            if (inputNumber > wholeSections) {
                return;
            }
            int j = 0;
            Node<BasicString>* searched = example.getHead();
            Node<BasicString>* searchedNode = &example.getHead()[0];
            for (int i = 0; i < inputNumber + j; i++) {
                if (i % ARRAY_SIZE == 0 && i != 0) {
                    searched = searched->next;
                }
                searchedNode = &searched[i % ARRAY_SIZE];

                if (searchedNode->deleted) {
                    j++;
                    if (i >= sectionCounter) {
                        return;
                    }
                }
            }
            if (searchedNode->deleted) {
                return;
            }
            Node<BasicString>* firstNode = &example.getHead()[0];
            
            if (searchedNode->deleteSection(searchedNode)) {
                searchedNode->deleted = true;
                wholeSections--;
                deletedCounter++;
                cout << com1.str << ",D,* == deleted" << endl;
            }
            

        }
        else if (atoi(com1.str) && com2 == "D" && atoi(com3.str) == 0) {
            int inputNumber = atoi(com1.str);
            int j = 0;
            Node<BasicString>* searched = example.getHead();
            Node<BasicString>* searchedNode = &example.getHead()[0];
            for (int i = 0; i < inputNumber + j; i++) {
                if (i % ARRAY_SIZE == 0 && i != 0) {
                    searched = searched->next;
                }
                searchedNode = &searched[i % ARRAY_SIZE];

                if (searchedNode->deleted) {
                    j++;
                    if (i >= wholeSections) {
                        return;
                    }
                }
            }
            if (searched->usedSections == 0 || searchedNode->deleted) {
                return;
            }
            if (searchedNode->deleteAttribute(atoi(com1.str), com3)) {
                searchedNode->deleteSection(searchedNode);
                searchedNode->deleted = true;
                wholeSections--;
                deletedCounter++;
            }
            

        }

    }
}
