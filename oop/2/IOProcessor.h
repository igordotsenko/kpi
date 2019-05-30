//
// Created by Igor on 5/30/19.
//

#ifndef UNTITLED_IOPROCESSOR_H
#define UNTITLED_IOPROCESSOR_H

#include <vector>
#include <iostream>
#include <cstdlib>

#include "Enterprise.h"

using namespace std;

class IOProcessor {
private:
    vector<Enterprise*>* enterprises;

private:
    void show_menu();
    void add_enterprise();
    Enterprise* create_new_enterprise();
    Enterprise* merge_new_enterprises();
    void copy_last_enterprise();
    void add_workers();
    void clear_enterprises();
    void print_table();
    void quit();

public:
    IOProcessor();
    ~IOProcessor();

    void start();

    friend void operator +=(IOProcessor& processor, Enterprise* enterprise);
    friend ostream &operator<<(ostream &os, const IOProcessor &processor);
};


#endif //UNTITLED_IOPROCESSOR_H
