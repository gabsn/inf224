#ifndef PHOTO_H
#define PHOTO_H

#include "multimediaobj.h"

class Photo : public MultimediaObj {

private:
    float longitude;
    float latitude;

public:
    Photo(string name = "", string pathName = "", float _longitude = 0, float _latitude = 0) :
        MultimediaObj(name, pathName) { media = "photo_media"; longitude =_longitude; latitude = _latitude; }

    int getLatitude() const { return latitude; }
    int getLongitude() const {return longitude; }

    void setLatitude(float _latitude) { latitude = _latitude; }
    void setLongitude(float _longitude) {longitude = _longitude; }

    void print(ostream &s) const override {
        s << "name : " << name << ", pathName : " << pathName << ", longitude : " << longitude << ", latitude : " << latitude;
    }

    void play() const override {
        system(("imagej "+ getPathName() + " &").c_str());
    }
    virtual void read (istream &f) {
        try {
            string lo, la;
            getline(f, lo);
            longitude = stoi(lo);
            getline(f, la);
            latitude = stoi(la);
            getline(f, pathName);
        } catch (exception& e) {
            cerr << "exception caught: " << e.what() << '\n';
        }
    }
    virtual void write(ostream &f) const {
        f << media << '\n' << name << '\n' << longitude << '\n' << latitude << '\n' << pathName << endl;
    }
};
#endif // PHOTO_H
