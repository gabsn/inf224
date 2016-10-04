#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>

#include "multimediaobj.h"

class Video : public MultimediaObj {
protected:
    int duration;

public:
    Video(string name = "", string pathName = "", int _duration = 0) :
        MultimediaObj(name, pathName) { duration = _duration; }

    virtual ~Video() {}

    virtual int getDuration() const { return duration; }
    virtual void setDuration(int _duration) { duration = _duration; }

    void print(ostream &s) const override {
        s << "name : " << name << ", pathName : " << pathName << ", duration : " << duration;
    }
    void play() const override {
        system(("vlc "+ getPathName() + " &").c_str());
    }
    virtual void read (istream &f) {
        try {
            string d;
            getline(f, d);
            duration = stoi(d);
            getline(f, pathName);
        } catch (exception& e) {
            cerr << "exception caught in Video::read : " << e.what() << '\n';
        }
    }
    virtual void write(ostream &f) const {
        f << media << '\n' << name << '\n' << duration << '\n' << pathName << endl;
    }
};

#endif // VIDEO_H

