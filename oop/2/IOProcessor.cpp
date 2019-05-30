//
// Created by Igor on 5/30/19.
//

#include "IOProcessor.h"

IOProcessor::IOProcessor() {
    this->enterprises = new vector<Enterprise*>();
    enterprises->reserve(3);
}

IOProcessor::~IOProcessor() {
    cout << "Deleting enterprises" << endl;
    delete enterprises;
}

void IOProcessor::start() {
    while (true) {
        show_menu();
    }
}

void IOProcessor::show_menu() {
    cout << "Enter 1 to add enterprise" << endl;
    cout << "Enter 2 to show all enterprises" << endl;
    cout << "Enter 3 to add workers to all enterprises" << endl;
    cout << "Enter 4 to clear enterprises" << endl;
    cout << "Enter 0 quit" << endl;

    int option;
    cin >> option;

    switch (option) {
        case 1:
            add_enterprise();
            break;
        case 2:
            print_table();
            break;
        case 3:
            add_workers();
            break;
        case 4:
            clear_enterprises();
            break;
        case 0:
            quit();
            break;
        default:
            cout << "Repeat your choice: ";
            break;
    }
}

void IOProcessor::add_enterprise() {
    cout << "Enter 1 to create new enterprises" << endl;
    cout << "Enter 2 merge enterprises" << endl;
    cout << "Enter 3 to add default enterprise" << endl;
    cout << "Enter 4 to copy last enterprise" << endl;

    int input;
    cin >> input;
    switch (input) {
        case 1:
            enterprises->push_back(create_new_enterprise());
            break;
        case 2:
            enterprises->push_back(merge_new_enterprises());
            break;
        case 3:
            enterprises->push_back(new Enterprise());
            break;
        case 4:
            copy_last_enterprise();
            break;
        default:
            cout << "Incorrect input";
    }
}

Enterprise* IOProcessor::create_new_enterprise() {
    EnterpriseType type;
    string name;
    int year;
    int month;
    int day;
    Date* date;
    int workers_count;
    double assets;

    bool type_input_correct = false;
    while (!type_input_correct) {
        cout << "Enter enterprise type:" << endl;
        cout << "1 for PRIVATE" << endl;
        cout << "2 for PUBLIC_STOCK" << endl;
        cout << "3 for PRIVATE_STOCK" << endl;
        cout << "4 for STATE" << endl;
        cout << "5 for LIMITED" << endl;
        int typeInput;
        cin >> typeInput;
        switch (typeInput) {
            case 1:
                type = PRIVATE;
                type_input_correct = true;
                break;
            case 2:
                type = PUBLIC_STOCK;
                type_input_correct = true;
                break;
            case 3:
                type = PRIVATE_STOCK;
                type_input_correct = true;
                break;
            case 4:
                type = STATE;
                type_input_correct = true;
                break;
            case 5:
                type = LIMITED;
                type_input_correct = true;
                break;
            default:
                cout << "Repeat your choice: ";
                break;
        }
    }

    cout << "Enter name" << endl;
    cin >> name;

    cout << "Enter year of creation" << endl;
    cin >> year;

    cout << "Enter month of creation" << endl;
    cin >> month;

    cout << "Enter day of creation" << endl;
    cin >> day;
    date = new Date(year, month, day);

    cout << "Enter workers count" << endl;
    cin >> workers_count;

    cout << "Enter assets" << endl;
    cin >> assets;

    return new Enterprise(type, name, date, workers_count, assets);
}


Enterprise *IOProcessor::merge_new_enterprises() {
    return *create_new_enterprise() + *create_new_enterprise();
}

void IOProcessor::copy_last_enterprise() {
    if (enterprises->empty()) {
        cout << "No enterprises to copy" << endl;
    } else {
        int last = enterprises->size()-1;
        enterprises->push_back(new Enterprise(*enterprises->at(last)));
    }

}

void IOProcessor::add_workers() {
    int number_to_add;
    cout << "Enter number of workers ot add" << endl;
    cin >> number_to_add;


    for (auto enterprise : *enterprises) {
        *enterprise << number_to_add;
    }
}

void IOProcessor::clear_enterprises() {
    for (auto enterprise : *enterprises) {
        delete enterprise;
    }
    delete enterprises;
    enterprises = new vector<Enterprise*>();
    enterprises->reserve(3);
}

void IOProcessor::print_table() {
    string line = string(104, '-');
    printf("%s\n", line.c_str());
    printf("|%-20s|%-30s|%-15s|%-20s|%-13s|\n", "Type", "Name", "Creation date", "Number of workers", "Assets");
    printf("%s\n", line.c_str());
    for (auto enterprise : *enterprises) {
        printf("|%-20s|%-30s|%-15s|%-20d|%-13.2f|\n",
                enterprise->type_to_string().c_str(), enterprise->get_name().c_str(),
                (char *) *enterprise->get_establishing_date(), enterprise->get_workers_count(),
                enterprise->get_assets());
        printf("%s\n", line.c_str());
    }
}

void IOProcessor::quit() {
    for (auto enterprise : *enterprises) {
        delete enterprise;
    }
    delete enterprises;
    exit(0);
}

void operator+=(IOProcessor &processor, Enterprise *enterprise) {
    processor.enterprises->push_back(enterprise);
}

ostream &operator<<(ostream &os, const IOProcessor &processor) {
    for (auto &enterprise : *processor.enterprises) {
        os << *enterprise;
    }
    return os;
}


