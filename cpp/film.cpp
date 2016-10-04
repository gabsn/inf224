#include "film.h"

#include <memory>

using namespace std;

void Film::setChapters(const int * _chapters, int _nbChapters) {
    if (chapters)
        delete [] chapters;
    chapters = new int[_nbChapters];
    for (int i=0; i<_nbChapters; ++i) {
        chapters[i] = _chapters[i];
    }
}

void Film::displayChapters() const {
    for (int i = 0; i < nbChapters; ++i)
        cout << "Chapter " << i << " : " << chapters[i] << " minutes" << endl;
}

void Film::read(std::istream & f) {
    try {
        string nb, d;
        getline(f, nb);
        //cout << "nb : " << nb << endl;
        nbChapters = stoi(nb);
        if (nbChapters <= 0) {
            throw runtime_error(name+" : "+nb+" chapters is impossible.");
        }
        getline(f, d);
        //cout << "d : " << d << endl;
        duration = stoi(d);
        if (duration <= 0) {
            throw runtime_error(name+" : "+d+" minutes is impossible.");
        }
        getline(f, pathName);
    } catch (exception& e) {
        cerr << "exception caught in Film::read : " << e.what() << '\n';
    }
}

void Film::write(ostream &f) const {
    f << media << '\n' << name << '\n' << nbChapters << '\n' << duration << '\n' << pathName << endl;
}
