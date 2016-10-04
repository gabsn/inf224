#ifndef FILM_H
#define FILM_H

#include "video.h"

class Film : public Video {
private:
    int nbChapters;
    int* chapters;

public:
    Film(string name = "", string pathName = "", int _duration = 0, int _nbChapters = 0, int* _chapters = NULL) :
        Video(name, pathName, _duration) {
            media = "film_media";
            nbChapters = _nbChapters;
            chapters = new int[_nbChapters];
            for (int i=0; i<_nbChapters; ++i) {
                chapters[i] = _chapters[i];
            }
        }
    ~Film() { delete [] chapters; }  
    int getNbChapters() const { return nbChapters; }
    const int* getChapters() const { return chapters; }
    const int* getChapters(int& length) const {
        length = nbChapters;
        return chapters;
    }

    void displayChapters() const;
    void setChapters(const int* _chapters, int _nbChapters);
    virtual void read(istream &);
    virtual void write(ostream &) const;
};

#endif // FILM_H
