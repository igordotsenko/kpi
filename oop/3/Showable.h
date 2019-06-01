//
// Created by Igor on 6/1/19.
//

#ifndef UNTITLED_SHOWABLE_H
#define UNTITLED_SHOWABLE_H

#include <iostream>

class Showable {
public:

    Showable();
    virtual ~Showable();

    virtual void show() = 0;
    virtual void display() = 0;
};


#endif //UNTITLED_SHOWABLE_H
