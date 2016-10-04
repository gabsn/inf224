#include <memory>
#include <sstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>

#include "table.h"

using namespace std;

Photo_ptr Table_p::create_photo(string name = "") {
    Photo_ptr photo(new Photo(name,name));
    try {
        if (objs.find(name) != objs.end()) {
            throw runtime_error("(Table_p::create_photo) "+name+" is already in the table.");
        } else {
            objs.insert(make_pair(name,photo));
        }
    } catch (exception& e) {
        cerr << "exception caught: " << e.what() << '\n';
    }

    return photo;
}

Video_ptr Table_p::create_video(string name = "") {
    Video_ptr video(new Video(name,name));
    try {
        if (objs.find(name) != objs.end()) {
            throw runtime_error("(Table_p::create_video) "+name+" is already in the table.");
        } else {
            objs.insert(make_pair(name,video));
        }
    } catch (exception& e) {
        cerr << "exception caught: " << e.what() << '\n';
    }


    return video;
}

Film_ptr Table_p::create_film(string name = "") {
    Film_ptr film(new Film(name));
    try {
        if (objs.find(name) != objs.end()) {
            throw runtime_error("(Table_p::create_film) "+name+" is already in the table.");
        } else {
            objs.insert(make_pair(name,film));
        }
    } catch (exception& e) {
        cerr << "exception caught: " << e.what() << '\n';
    }


    return film;
}

Group_ptr Table_p::create_group(string name) {
    Group_ptr group(new Group(name));
    try {
        if (groups.find(name) != groups.end()) {
            throw runtime_error("(Table_p::create_group) "+name+" is already in the table.");
        } else {
            groups.insert(make_pair(name,group));
        }
    } catch (exception& e) {
        cerr << "exception caught: " << e.what() << '\n';
    }


    return group;
}

void Table_p::delete_obj(string name) {
    try {
        if (objs.find(name) == objs.end()) {
            throw runtime_error("(Table_p::delete_obj) No "+name+" in the table.");
        } else {
            objs.erase(name);
            for (Group_map::iterator it=groups.begin(); it!=groups.end(); it++) {
                Group_ptr group = (*it).second;
                for (Group::iterator itg=group->begin(); itg!=group->end(); itg++) {
                    if ((*itg)->getName() == name) {
                        itg = group->erase(itg);
                    }
                }
            }
        }
    } catch (exception& e) {
        cerr << "exception caught: " << e.what() << '\n';
    }
}

void Table_p::delete_group(string name) {
    groups.erase(name);
}

void Table_p::find_obj(string name, stringstream& ss) {
    try {
        map<string,shared_ptr<MultimediaObj> >::iterator it = objs.find(name);
        if (it != objs.end()) {
            MultimediaObj_ptr obj = (*it).second;
            obj->print(ss);
        } else {
            throw runtime_error("(Table_p::find_obj) No "+name+" in the table.");
        }
    } catch (exception& e) {
        cerr << "exception caught: " << e.what() << '\n';
    }
}

void Table_p::find_group(string name) {
    try {
        map<string,shared_ptr<Group> >::iterator it = groups.find(name);
        if (it != groups.end()) {
            Group_ptr group = (*it).second;
            cout << group->getName() << " contains :" << endl;
            group->display();
        } else {
            throw runtime_error("(Table_p::find_group) No "+name+" in the table.");
        }
    } catch (exception& e) {
        cerr << "exception caught: " << e.what() << '\n';
    }
}

void Table_p::play_obj(string name) {
    map<string,shared_ptr<MultimediaObj> >::iterator it = objs.find(name);
    MultimediaObj_ptr obj = (*it).second;
    obj->play();
}

void Table_p::play_group(string name) {
    map<string,shared_ptr<Group> >::iterator it = groups.find(name);
    Group_ptr group = (*it).second;
    group->play();
}

bool Table_p::save(const string & fileName) {
    ofstream ofs(fileName);
    if (!ofs) {
        cerr << "Can't open file " << fileName << endl;
        return false;
    }
    for (auto it : objs) {
        it.second->write(ofs);
    }
    ofs.close();
    return true;
}

bool Table_p::load(const string & fileName) {
    ifstream ifs(fileName);
    if (!ifs) {
        cerr << "Can't open file " << fileName << endl;
        return false;
    }
    while (ifs.good()) { // pas d’erreur et pas en fin de fichier
        MultimediaObj_ptr obj;
        string media, name;
        getline(ifs,media);
        getline(ifs, name);
        //cout << "media : " << media << " and name : " << name << endl;
        if (media.compare("photo_media") == 0) {
            obj = create_photo(name);
            //cout << "***photo***" << endl;
        } else if (media.compare("video_media") == 0) {
            obj = create_video(name);
            //cout << "***video***" << endl;
        } else if (media.compare("film_media") == 0) {
            obj = create_film(name);
            //cout << "***film***" << endl;
        } else {
            ifs.close();
            return true;
        }
        obj->read(ifs);
        //cout << "object read." << endl;
        if (ifs.fail()) { // erreur de lecture
            cerr << "Read error in " << fileName << endl;
            return false;
        } else {
            objs.insert(pair<string, MultimediaObj_ptr>(obj->getName(), obj));
            //cout << "object inserted" << endl;
        }
    }
    //cout << "sortie du while" << endl;
    ifs.close();
    return true;
}

bool Table_p::is_in_table(const string& name) {
    bool response = false;
    if (objs.find(name) != objs.end() || groups.find(name) != groups.end())
        response = true;
    return response;
}


