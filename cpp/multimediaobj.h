#ifndef MULTIMEDIAOBJ_H
#define MULTIMEDIAOBJ_H

#include <string>
#include <iostream>

using namespace std;

class MultimediaObj {

protected:
    string name;
    string pathName;
    string media;

public:
    MultimediaObj(string name = "", string pathName = "");
    virtual ~MultimediaObj() { cout << name << " détruit." << endl; }

    string getName() const { return name; }
    string getPathName() const { return pathName; }
    void setName(string _name) { name = _name; }
    void setPathName(string _pathName) { pathName = _pathName;}

    virtual void print(ostream & s) const;
    virtual void play() const = 0;
    virtual void write(ostream &) const = 0;
    virtual void read(istream &) = 0;
};

#endif // MULTIMEDIAOBJ_H
