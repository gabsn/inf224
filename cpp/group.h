#ifndef GROUP_H
#define GROUP_H

#include <list>
#include <iostream>
#include <memory>

#include "multimediaobj.h"


typedef std::list<shared_ptr<MultimediaObj> > objList;

class Group : public objList {  
private:
    string groupName;

public:
    Group(string s = "") { groupName = s; }  
    ~Group() { cout << groupName << " détruit." << endl; }
    string getName() const { return groupName; }

    void display() const;
    void play() const;
};


#endif // GROUP_H
