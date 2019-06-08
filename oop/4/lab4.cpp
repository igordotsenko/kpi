#include <algorithm>
#include <string>
#include <iostream>
#include <random>
#include "DailyBalance.h"
#include "Container.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

int number_of_character = sizeof(alphanum) - 1;
std::default_random_engine rng(std::random_device{}());
std::uniform_int_distribution<> dist(0, number_of_character);

char genRandom() {
    return alphanum[dist(rng)];
//    return alphanum[rand() % number_of_character];
}

string get_random_string(int str_len) {
    srand(time(0));
    std::string str;
    for(unsigned int i = 0; i < str_len; ++i) {
        str += genRandom();
    }
    return str;
}


char* to_char_ar(const string s) {
    char* ar = new char[s.length()+1];
    strcpy(ar, s.c_str());
    return ar;
}

auto cstr_compare = [](const char* s1, const char* s2) {
    return strcmp(s1,s2) < 0;
};

void sort_test() {


    int n = 200000;
    int str_len = 20;
    string str_arr[n];
    for (int i = 0; i < n; i++) {
        str_arr[i] = get_random_string(str_len);
    }

    // sort string
    cout << "Sorting " << n << " strings " << endl;
    high_resolution_clock::time_point str_sort_start = high_resolution_clock::now();
    sort(str_arr, str_arr+n);
    high_resolution_clock::time_point str_sort_end = high_resolution_clock::now();
    auto str_sort_duration = duration_cast<microseconds>( str_sort_end - str_sort_start ).count();
    cout << "Sorting took " << str_sort_duration << " microseconds" << endl;
//    for (const string el : str_arr) {
//        cout << el << endl;
//    }

    // sort char arrays
    char* char_arr[n];
    for (int i = 0; i < n; i++) {
        char_arr[i] = to_char_ar(str_arr[i]);
    }

    cout << "Sorting " << n << " char arrays " << endl;
    high_resolution_clock::time_point char_arr_sort_start = high_resolution_clock::now();
    sort(char_arr, char_arr+n, cstr_compare);
    high_resolution_clock::time_point char_arr_sort_end = high_resolution_clock::now();
    auto char_arr_sort_duration = duration_cast<microseconds>( char_arr_sort_end - char_arr_sort_start ).count();
    cout << "Sorting took " << char_arr_sort_duration << " microseconds" << endl;

//    for (auto a : char_arr) {
//        cout << a << endl;
//    }
}

void container_test() {
    DailyBalance* dailyBalance = new DailyBalance(5);

    for (int i = 0; i < 10; i++) {
        dailyBalance->put(new Checkout(
                new Operator("operator_name", "operator_lastname", new Date(2000, 1, 1)),
                new Fuel(DIESEL, 26.5), i,
                new Date(2018, 1, 1)));
    }

    for (int i = 0; i < 10; i++) {
        cout << *((*dailyBalance)[i]) << endl;
    }

    cout << dailyBalance->calculate_deviation(3.2) << endl;

    dailyBalance->write_bin();


    delete dailyBalance;

    DailyBalance* newDailyBalance = new DailyBalance(5);
    newDailyBalance->read_bin();

    for (int i = 0; i < 10; i++) {
        cout << *((*newDailyBalance)[i]) << endl;
    }
}


int main() {
//    sort_test();
    container_test();
}
