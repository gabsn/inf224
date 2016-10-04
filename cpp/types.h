#ifndef TYPES_H
#define TYPES_H

#include <memory>

#include "photo.h"
#include "video.h"
#include "film.h"
#include "group.h"

typedef shared_ptr<Photo> Photo_ptr;
typedef shared_ptr<Video> Video_ptr;
typedef shared_ptr<Film> Film_ptr;
typedef shared_ptr<MultimediaObj> MultimediaObj_ptr;
typedef shared_ptr<Group> Group_ptr;

typedef map<string, shared_ptr<MultimediaObj> > Multimediaobj_map;
typedef map<string, shared_ptr<Group> > Group_map;

#endif // TYPES_H
