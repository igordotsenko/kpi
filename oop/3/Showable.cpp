
#include "Showable.h"

using namespace std;

Showable::Showable() {
    cout << "Showable is created. Size is " << sizeof(Showable) << endl;
}

Showable::~Showable() {
    cout << "Showable is deleted" << endl;
}
