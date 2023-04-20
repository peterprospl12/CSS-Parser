#include "BasicString.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>


BasicString::BasicString()
    :str(nullptr) {
    str = new char[1];
    str[0] = '\0';
}

BasicString::BasicString(char* orig) {
    str = new char[strlen(orig) + 1];
    strcpy(str, orig);
    str[strlen(orig)] = '\0';
}

BasicString::BasicString(const char* orig) {
    str = new char[strlen(orig) + 1];
    strcpy(str, orig);
    str[strlen(orig)] = '\0';
}

BasicString::BasicString(const BasicString& cpy) {
    str = new char[strlen(cpy.str) + 1];
    strcpy(str, cpy.str);
    str[strlen(cpy.str)] = '\0';
}

BasicString::BasicString(BasicString&& cpy)
    :str(cpy.str) {
    cpy.str = nullptr;
}

BasicString& BasicString::operator=(const BasicString& right) {

    delete[] str;
    str = new char[strlen(right.str) + 1];
    strcpy(str, right.str);
    str[strlen(right.str)] = '\0';
    return *this;
}

BasicString& BasicString::operator=(const char* right) {

    delete[] str;
    str = new char[strlen(right) + 1];
    strcpy(str, right);
    str[strlen(right)] = '\0';
    return *this;
}



BasicString& BasicString::operator=(BasicString&& right)
{
    delete[] str;
    str = right.str;
    right.str = nullptr;
    return *this;
}

bool BasicString::operator==(const BasicString& str2) {
    return !strcmp(str, str2.str);
}

bool BasicString::operator!=(const BasicString& str2) {
    return strcmp(str, str2.str);
}

std::ostream& operator<<(std::ostream& os, const BasicString& orig) {
    os << orig.str;
    return os;
}


std::istream& operator>>(std::istream& is, BasicString& orig) {
    char* str = new char[200];

    is >> str;

    orig = BasicString(str);
    delete[] str;
    return is;
}



BasicString BasicString::operator+(const BasicString& orig) const {
    int len1 = strlen(str);
    int len2 = strlen(orig.str);
    char* newStr = new char[len1 + len2 + 1];
    strcpy(newStr, str);
    strcpy(newStr + len1, orig.str);
    BasicString result(newStr);
    delete[] newStr;
    return result;
}

BasicString& BasicString::operator+=(const BasicString& orig) {
    int len1 = strlen(str);
    int len2 = strlen(orig.str);
    char* newStr = new char[len1 + len2 + 2];
    strcpy(newStr, str);
    newStr[len1] = ' ';
    newStr[len1 + 1] = '\0';
    strcpy(newStr + len1 + 1, orig.str);
    BasicString result(newStr);
    delete[] newStr;
    *this = result;
    return *this;
}

void BasicString::replaceChar(const char* oldChar, const char* newChar) {
    if (newChar == " ") {
        int counter = 0;
        for (int i = 0; i < strlen(this->str); i++) {
            if (this->str[i] == *oldChar) {
                counter++;
                break;
            }
        }

        if (counter == 0) {
            return;
        }

        char* newStr = new char[strlen(this->str) - counter + 1];
        int j = 0;
        for (int i = 0; i < strlen(this->str); i++) {
            if (this->str[i] != *oldChar) {
                newStr[j++] = this->str[i];
            }
        }
        newStr[j] = '\0';

        delete[] this->str;
        this->str = newStr;
    }

    else {
        for (int i = 0; i < strlen(this->str); i++) {
            if (this->str[i] == *oldChar) {
                this->str[i] = *newChar;
            }
        }
    }
}

bool BasicString::checkForChar(const char* checkChar) {
    for (int i = 0; i < strlen(this->str); i++) {
        if (this->str[i] == *checkChar) {
            return true;
        }
    }
    return false;
}

void BasicString::addSpace(const char* oldChar) {
    char* newStr = new char[strlen(this->str) + 1];
    bool addSpace = true;
    for (int i = 0; i < strlen(this->str); i++) {
        if (this->str[i] == *oldChar && addSpace) {
            newStr[i] = ' ';
        }
        else {
            newStr[i] = this->str[i];
        }
    }
    newStr[strlen(this->str)] = '\0';
    delete[] this->str;
    this->str = newStr;
}

void BasicString::changeIntChar(int changePlace, const char* newChar) {
    int charLength = strlen(this->str);
    if (changePlace >= charLength || changePlace < 0) {
        return;
    }
    char* tempStr = new char[charLength + 2];
    int j = 0;
    for (int i = 0; i < charLength+1; i++) {
        if (i == changePlace) {
            tempStr[i] = *newChar;
        }
        else {
            tempStr[i] = this->str[j++];
        }
    }
    tempStr[charLength+1] = '\0';
    delete[] this->str;
    this->str = tempStr;
}

BasicString BasicString::separateString(const char* sepChar, int sepFrom) {
    if (this == nullptr || this->str == nullptr ) {
        return BasicString();
    }
    int startCounter = 0, endCounter = 0;
    while (sepFrom > 0 && this->str[startCounter] != '\0') {
        if (this->str[startCounter] == *sepChar) {
            sepFrom--;
        }
        startCounter++;
    }
    if (sepFrom > 0) {
        return BasicString("");
    }
    while (this->str[startCounter + endCounter] != '\0' && this->str[startCounter + endCounter] != *sepChar) {
        endCounter++;
    }
    char* tempStr = new char[endCounter + 1];
    for (int i = 0; i < endCounter; i++) {
        tempStr[i] = this->str[startCounter + i];
    }
    tempStr[endCounter] = '\0';
    BasicString result(tempStr);
    delete[] tempStr;
    return result;
}

BasicString BasicString::separateWholeString(const char* sepChar) {
    int counter = 0;
    bool goNext = false;
    for (int i = 0; i < strlen(this->str); i++) {
        if (this->str[i] != ' ') {
            goNext = true;
        }
        if (goNext) {
            if (this->str[i] == *sepChar) {
                counter = i;
                break;
            }
        }

    }
    int newArrSize = strlen(this->str) - counter;
    char* tempStr = new char[newArrSize];
    for (int i = 0; i < newArrSize - 1; i++) {
        tempStr[i] = this->str[counter + 1 + i];
    }
    tempStr[newArrSize - 1] = '\0';
    BasicString result(tempStr);
    return result;
}

BasicString BasicString::getFirstString() {
    if (this == nullptr || this->str == "") {
        return BasicString();
    }
    int startIndex = 0;
    int endIndex = 0;
    bool stop = false;
    int len = strlen(this->str);
    for (int i = 0; i < len; i++) {
        if (this->str[i] != ' ') {
            startIndex = i;
            break;
        }
    }
    for (int i = startIndex; i < len; i++) {
        if (this->str[i] == ' ') {
            endIndex = i;
            break;
        }
    }
    char* tempStr = new char[endIndex - startIndex + 1];
    memcpy(tempStr, &this->str[startIndex], endIndex - startIndex);
    tempStr[endIndex - startIndex] = '\0';
    BasicString result(tempStr);
    return result;
}


int BasicString::countChars(const char* countChar) {
    if (this == nullptr || this->str == "") {
        return 0;
    }
    int length = strlen(this->str);
    int counter = 0;
    for (int i = 0; i < length; i++) {
        if (this->str[i] == *countChar) {
            counter++;
        }
    }
    return counter;

}



BasicString::~BasicString() {
    delete[] str;
}