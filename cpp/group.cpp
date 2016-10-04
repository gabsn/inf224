#include <iostream>

#include "group.h"

using namespace std;

void Group::display() const {
    for (Group::const_iterator it = this->begin(); it != this->end(); ++it)
        (*it)->print(cout);
}

void Group::play() const {
    for (Group::const_iterator it = this->begin(); it != this->end(); ++it)
        (*it)->play();
}
