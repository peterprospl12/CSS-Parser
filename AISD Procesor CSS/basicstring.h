#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class BasicString {
public:
    char* str;
public:
    BasicString();
    BasicString(char* orig);
    BasicString(const char* orig);
    BasicString(const BasicString& cpy);
    BasicString(BasicString&& cpy);
    BasicString& operator=(const BasicString& right);
    BasicString& operator=(const char* right);
    BasicString& operator=(BasicString&& right);

    BasicString separateString(const char* sepChar, int sepFrom);
    BasicString separateWholeString(const char* sepChar);
    BasicString getFirstString();
    void replaceChar(const char* oldChar, const char* newChar);
    void addSpace(const char* oldChar);
    bool checkForChar(const char* checkChar);
    void changeIntChar(int charToChange, const char* newChar);
    int countChars(const char* countChar);
    friend std::ostream& operator<<(std::ostream& os, const BasicString& orig);
    friend std::istream& operator>>(std::istream& is, BasicString& orig);
    bool operator==(const BasicString& str2);
    bool operator!=(const BasicString& str2);
    BasicString operator+(const BasicString& orig) const;
    BasicString& operator+=(const BasicString& orig);



    ~BasicString();
};