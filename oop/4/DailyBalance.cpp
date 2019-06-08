#include "DailyBalance.h"

static const string file = "/tmp/balance.txt";

DailyBalance::~DailyBalance() {}

void DailyBalance::write_bin() {
    ofstream fout;
    try {
        fout.open(file);
        if (!fout) {
            throw "File cannot be opened";
        }

        for (int i = 0; i < size(); i++) {
            (*this)[i]->serialize(fout);
        }

        fout.close();
    } catch (char err) { // обробка виключних ситуацій
        cout << err << endl;
    }
}

void DailyBalance::read_bin() {
    ifstream fin;
    try {
        fin.open(file, ios::binary | ios::in);
        if (!fin) {
            throw "File cannot be opened.";
        }

        while(!fin.eof()) {
            Checkout* checkout = new Checkout();
            checkout->deserialize(fin);
            put(checkout);
        }


        fin.close();
    } catch (char err) { // обробка виключних ситуацій
        cout << err << endl;
    }
}
