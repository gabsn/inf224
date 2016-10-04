#ifndef TABLE_H
#define TABLE_H

#include <map>
#include <memory>

#include "multimediaobj.h"
#include "group.h"
#include "types.h"

using namespace std;

class Table_p {
private:
    Multimediaobj_map objs;
    Group_map groups;

public:
    Table_p() {}
    ~Table_p(){ cout << "Table détruite." << endl; }

    Photo_ptr create_photo(string);
    Video_ptr create_video(string);
    Film_ptr create_film(string);
    Group_ptr create_group(string);
    void delete_obj(string);
    void delete_group(string);
    void find_obj(string, stringstream&);
    void find_group(string);
    void play_obj(string);
    void play_group(string);
    bool save(const string&);
    bool load(const string&);
    bool is_in_table(const string&);
};

#endif // TABLE_H

