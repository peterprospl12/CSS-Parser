#pragma once
class BasicString;
template <typename Type> class List;
template <typename Type> class Node;


void readAttributes(List<BasicString>& example, BasicString& usrInput, int& wholeSections, int& sectionCounter, bool& addToSelector);


void readCSS(List<BasicString>& example, BasicString& usrInput, int& wholeSections, int& sectionCounter, bool& addToSelector);

void readCommands(List<BasicString>& example, BasicString usrInput, int& wholeSections, bool& CSSswitch, int& sectionCounter, int& deletedCounter);