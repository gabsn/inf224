#include "multimediaobj.h"
#include <iostream>
#include <string>
#include <limits>

MultimediaObj::MultimediaObj(string _name, string _pathName) {
    media = "video_media";
    name = _name;
    pathName = _pathName;
}

void MultimediaObj::print(ostream & s) const {
    s << "name : " << name << " and pathName : " << pathName << endl;
}
