#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Date { // клас Дата
private: // приватні методи
    string day;
    string month;
    string year;
public: // публічні методи
    void setDay(string value) {
        day = value;
    }
    void setMonth(string value){
        month = value;
    }
    void setYear(string value){
        year = value;
    }
    string printDate() {
        return day + " " + month + " " + year;
    }
    void setDate() {
        cout << "Enter day: ";
        cin >> day;
        cout << "Enter month: ";
        cin >> month;
        cout << "Enter year: ";
        cin >> year;
    }
    void setDate(ifstream& fin) {
        fin >> day;
        fin >> month;
        fin >> year;
    }
};

class Person { // клас Особа
protected: // захищені методи - доступні з похідних класів
    string lastName;
    string name;
    Date birthday;
public: // публічні методи
    Person() {}
    Person(string tName, string tLastName) {
        name = tName;
        lastName = tLastName;
    }
    void setLastName(string value) {
        lastName = value;
    }
    void setName(string value) {
        name = value;
    }
    void setBirth() {
        birthday.setDate();
    }
    void setBirth(ifstream& fin) {
        birthday.setDate(fin);
    }
    string getLastName() {
        return lastName;
    }
    string getName() {
        return name;
    }
    Date getDate() {
        return birthday;
    }
};

class Artist : public Person {
    string type;
public:
    Artist() {
        type = "0";
    }
    Artist(string tName, string tLastName, string tType) : Person(tName, tLastName) {
        type = tType;
    }
    string getType() {
        return type;
    }
    void setType(string value) {
        type = value;
    }
};

class Performer { // клас Артист
    Person pers; // успадковування класу Особа
    Artist art; // успадковування класу Виконавець
public:
    Person getPerson() {
        return pers;
    }
    Artist getArt() {
        return art;
    }
};

class QuartetOfPerformers { // клас Квартет Виконавців
    Artist art[4];
public:
    Artist getPerformer(int ind) {
        return art[ind];
    }
    void setPerform(int index, Artist tArt) {
        art[index] = tArt;
    }
    string printQuartet() {
        return art[0].getLastName() + ", " + art[1].getLastName() + ", " + art[2].getLastName() + ", " + art[3].getLastName();
    }
    string writeArtist(int ind) {
        return art[ind].getName() + " " + art[ind].getLastName() + " " + art[ind].getType();
    }
};


class Quartet { // клас Квартет (музичний твір)
public:
    Person composer;
    string Opus;
    Date dateCreate;
};

class Performance { // клас Виконання
public:
    //Quartet *composition;
    vector<Quartet> composition;
    QuartetOfPerformers performances;
    Date implemen;
    int time;
    int sizeCopmosit;

    void setSize(int size) {
        composition.reserve(size);
    }

    int getTime() {
        return time;
    }
};

class LibraryOfQuartets { // клас Фонотека Квартетів
public:
    vector<Performance>	impl;
    Quartet quaert;
    QuartetOfPerformers QuartOfPerf;
    int sizeImpl;
    void setSize(int size) {
        impl.reserve(size);
    }
};

class Files { // клас Файл
    string file = "text.txt";
    string binFile = "binary.txt";
public:
    void write(LibraryOfQuartets lib[]) { // запис даних у текстовий файл
        ofstream fout;
        try
        {
            fout.open("text.txt");
            if (!fout) {
                throw "File cannot be opened.";
            }
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 4; j++) {
                    fout << lib[0].QuartOfPerf.writeArtist(j) << " ";
                    fout << lib[0].QuartOfPerf.getPerformer(j).getDate().printDate() << " ";
                }
                fout << lib[0].sizeImpl << " ";
                for (int j = 0; j < lib[0].sizeImpl; j++) {
                    fout << lib[0].impl[j].time << " ";
                    fout << lib[0].impl[j].implemen.printDate() << " ";
                    fout << lib[0].impl[j].sizeCopmosit << " ";
                    for (int k = 0; k < lib[0].impl[j].sizeCopmosit; k++) {
                        fout << lib[0].impl[j].composition[k].composer.getName() << " ";
                        fout << lib[0].impl[j].composition[k].composer.getLastName() << " ";
                        fout << lib[0].impl[j].composition[k].composer.getDate().printDate() << " ";
                        fout << lib[0].impl[j].composition[k].dateCreate.printDate() << " ";
                        fout << lib[0].impl[j].composition[k].Opus << " ";
                    }
                }
            }
            fout.close();
        }
        catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
        }
    }

    void writeBin(LibraryOfQuartets lib[]) { // запис даних у бінарний файл
        ofstream fout;
        try
        {
            fout.open("textBin.txt", ios::binary | ios::out);
            if (!fout) {
                throw "File cannot be opened.";
            }
            LibraryOfQuartets temp;
            for (int i = 0; i < 10; i++) {
                fout.write((char*)&lib[i], sizeof(temp));
            }

            fout.close();
        }
        catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
        }
    }
    vector<Performance> impls;
    vector <Quartet> compositions;

    void readBin(LibraryOfQuartets lib[]) { // зчитування даних з бінарного файлу
        ifstream fin;
        try
        {
            fin.open("textBin.txt", ios::binary | ios::in);
            if (!fin) {
                throw "File cannot be opened.";
            }
            LibraryOfQuartets temp;
            for (int i = 0; i < 10; i++) {
                fin.read((char*)&lib[i], sizeof(temp));
            }


            fin.close();
        }
        catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
        }
    }

    void read(LibraryOfQuartets lib[]) { // зчитування даних з текстового файлу
        ifstream fin;
        try
        {
            fin.open("text.txt");
            if (!fin) {
                throw "File cannot be opened.";
            }
            string name, lastName, type;
            for (int i = 0; i < 10; i++) {
                QuartetOfPerformers quartet;
                for (int j = 0; j < 4; j++) {
                    fin >> name;
                    fin >> lastName;
                    fin >> type;
                    Artist temp(name, lastName, type);
                    temp.setBirth(fin);
                    quartet.setPerform(j, temp);
                }
                lib[i].QuartOfPerf = quartet;
                int size;
                int sizeComposition;
                fin >> size;
                lib[i].sizeImpl = size;
                lib[i].setSize(size);
                vector<Performance> impl(size);
                for (int j = 0; j < size; j++) {
                    fin >> impl[j].time;
                    impl[j].implemen.setDate(fin);
                    impl[j].performances = lib[i].QuartOfPerf;
                    fin >> sizeComposition;
                    impl[j].sizeCopmosit = sizeComposition;
                    impl[j].setSize(sizeComposition);
                    vector <Quartet> composition(sizeComposition);
                    for (int k = 0; k < sizeComposition; k++) {
                        fin >> name;
                        fin >> lastName;
                        Person temp(name, lastName);
                        composition[k].composer = temp;
                        composition[k].composer.setBirth(fin);
                        composition[k].dateCreate.setDate(fin);
                        fin >> composition[k].Opus;
                        impl[j].composition.emplace_back(composition[k]);
                    }
                    lib[i].impl.emplace_back(impl[j]);
                }
            }
        }
        catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
        }
    }
};

class ListQuart { // агрегація

public:
    Files file;
    LibraryOfQuartets lib[10];
    LibraryOfQuartets operator [] (int i) // перезавантаження оператора []
    {
        if (i < 0 || i> 9) {
            cout << "Boundary Error\n";
            exit(1);
        }
        else {
            return lib[i];
        }
    }

//     template <typename Type> // шаблон фукнції
//     Type avarage(int index, Type a[index]) {
//    	 double result = 0;
//    	 for (int i = 0; i < lib[index].sizeImpl; i++) {
//    	 	result += a[index];
//    	 }
//    	 return result / lib[index].sizeImpl;
//     }

    double averageCountImpl(int index) { // порахувати кількість виконань
        double result = 0;
        for (int i = 0; i < lib[index].sizeImpl; i++) {
            result += lib[index].impl[i].sizeCopmosit;
        }
        return result / lib[index].sizeImpl;
    }
    double timeImpl(int index) {
        double result = 0;
        for (int i = 0; i < lib[index].sizeImpl; i++) {
            result += lib[index].impl[i].time;
        }
        return result / lib[index].sizeImpl;

    }

    void show() { // виведення даних у вигляді таблиці
        string temp = string(80, '-');
        printf("%s\n", temp.c_str());
        printf("|%-40s|%-20s|%-20s|\n", "Quartet", "Av. count perfom.", "Av. time of performance");
        printf("%s\n", temp.c_str());
        for (int i = 0; i < 10; i++) {
            double impl = averageCountImpl(i);
            double time = timeImpl(i);
            printf("|%-30s|%-20f|%-20f|\n", lib[i].QuartOfPerf.printQuartet().c_str(), impl, time);
            printf("%s\n", temp.c_str());
        }
    }
    void clear() {
        system("cls");
    }
    void inputPerfomers(ListQuart &list) {
        string name, lastName, type;
        for (int i = 0; i < 1; i++) {
            cout << "Enter quartet of musicians #" << i + 1 << ": " << endl;
            QuartetOfPerformers quartet;
            for (int j = 0; j < 4; j++) {
                cout << "Enter musician #" << j + 1 << ": " << endl;
                cout << "Enter first name: ";
                cin >> name;
                cout << "Enter last name: ";
                cin >> lastName;
                cout << "Enter musical instrument: ";
                cin >> type;
                Artist temp(name,lastName,type);
                temp.setBirth();
                quartet.setPerform(j, temp);
                clear();
            }
            list[i].QuartOfPerf = quartet;
            int size;
            int sizeComposition;
            cout << "Enter number of performances: ";
            cin >> size;
            // list[i].sizeImpl = size;
            list[i].setSize(size);
            vector<Performance> impl(size);
            for (int j = 0; j < size; j++) {
                cout << "Enter performance #" << j + 1 << ": " << endl;
                cout << "Enter the duration of performance: ";
                cin >> impl[j].time;
                impl[j].implemen.setDate();
                impl[j].performances = lib[i].QuartOfPerf;
                cout << "Enter duration of composition: ";
                cin >> sizeComposition;
                impl[j].sizeCopmosit = sizeComposition;
                impl[j].setSize(sizeComposition);
                vector <Quartet> composition(sizeComposition);
                for (int k = 0; k < sizeComposition; k++) {
                    cout << "Enter composition #" << k+1 << ": " << endl;
                    cout << "Enter composer first name: ";
                    cin >> name;
                    cout << "Enter composer last name: ";
                    cin >> lastName;
                    Person temp(name, lastName);
                    composition[k].composer = temp;
                    cout << "Enter composer birthdate:" << endl;
                    composition[k].composer.setBirth();
                    cout << "Enter data of creation of the composition:" << endl;
                    composition[k].dateCreate.setDate();
                    cout << "Enter opus: ";
                    cin >> composition[k].Opus;
                    clear();
                    impl[j].composition.emplace_back(composition[k]);
                }
                list[i].impl.emplace_back(impl[j]);
            }
        }
    }
    void search(int key) { // пошук інформації за числовим полем
        int count = 0;
        string temp = string(60, '-');
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < lib[i].sizeImpl; j++) {
                if (key == lib[i].impl[j].time) {
                    if (count == 0) {
                        printf("%s\n",temp.c_str());
                        printf("|%-7s|%-10s|%-40s|\n", "Time", "Data", "Quartet of performers");
                        printf("%s\n", temp.c_str());
                    }
                    int tTemp = lib[i].impl[j].getTime();
                    string date = lib[i].impl[j].implemen.printDate();
                    string quart = lib[i].impl[j].performances.printQuartet();
                    printf("|%-7d|%-10s|%-40s|\n", tTemp, date.c_str(), quart.c_str());
                    printf("%s\n", temp.c_str());
                    count++;
                }
            }
        }
        cout << "Total number of performances: " << count << endl;
    }

    void search(string key) { // пошук інформації за текстовим полем
        int count = 0;
        string temp = string(60, '-');
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < lib[i].sizeImpl; j++) {
                for (int k = 0; k < lib[i].impl[j].sizeCopmosit; k++) {
                    if (key == lib[i].impl[j].composition[k].Opus) {
                        if (count == 0) {
                            printf("%s\n", temp.c_str());
                            printf("|%-10s|%-10s|%-40s|\n", "Opus", "Data", "Composer");
                            printf("%s\n", temp.c_str());
                        }
                        string opus = lib[i].impl[j].composition[k].Opus;
                        string date = lib[i].impl[j].composition[k].dateCreate.printDate();
                        string composer = lib[i].impl[j].composition[k].composer.getLastName() + " " + lib[i].impl[j].composition[k].composer.getName();
                        printf("|%-10s|%-10s|%-40s|\n", opus.c_str(), date.c_str(), composer.c_str());
                        printf("%s\n", temp.c_str());
                        count++;
                    }
                }
            }
        }
    }

};

void delay() {
    system("pause");
}
void clear() {
    system("cls");
}


void marina() {
    setlocale(LC_ALL, "Russian");
    int key;
    int temp;
    ListQuart list;
    // меню
    do {
        cout << " -----------------------------------" << endl;
        cout << "| Enter 1 to input data ->          |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 2 to output data ->         |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 3 to write data to file ->  |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 4 to read data from file -> |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 5 to search data ->         |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 0 to exit ->                |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "Make your choice -> ";
        cin >> key;
        switch (key) {
            case 1:
                clear();
                list.inputPerfomers(list);
                delay();
                break;
            case 2:
                clear();
                list.show();
                delay();
                break;
            case 3:
                clear();
                cout << "Enter 1 to write data in txt file: " << endl;
                cout << "Enter 2 to write data in binary txt file: " << endl;
                cin >> temp;
                if (temp == 1) {
                    list.file.write(list.lib);
                }
                else {
                    list.file.writeBin(list.lib);
                }
                delay();
                break;
            case 4:
                clear();
                cout << "Enter 1 to read data from txt file: " << endl;
                cout << "Enter 2 to read data from binary txt file: " << endl;
                cin >> temp;
                if (temp == 1) {
                    list.file.read(list.lib);
                }
                else {
                    list.file.readBin(list.lib);
                }
                delay();
                break;
            case 5:
                clear();
                cout << "Enter 1 to search for performance time: " << endl;
                cout << "Enter 2 to search for opus: " << endl;
                cin >> temp;
                if (temp == 1) {
                    int time;
                    cout << "Enter time: ";
                    cin >> time;
                    list.search(time);
                }
                else {
                    string opus;
                    cout << "Enter opus: ";
                    cin >> opus;
                    list.search(opus);
                }
                delay();
                break;
            case 0:
                break;
            default:
                cout << "Repeat your choice: ";
                break;
        }
    } while (key != 0);
}

/**
 *
 *
 *
 *
 * MARINA BLOCK ENDS HERE
 *
 *
 *
 *
 */

class FigureOperationException {
private:
    string message;

public:
    FigureOperationException(const string &message) : message(message) {}

public:
    const string &getMessage() const {
        return message;
    }
};

class InvalidParamException : public FigureOperationException {
public:
    InvalidParamException(const string &message) : FigureOperationException(message) {}
};

class ContainerIsFullException : public FigureOperationException {
public:
    ContainerIsFullException(const string &message) : FigureOperationException(message) {}
};

class Point { // клас Точка
private: // приватні поля та методи
    double x;
    double y;

public: // публічні поля та методи
    Point(double x, double y) : x(x), y(y) {}

    double getX() const {
        return x;
    }

    void setX(double x) {
        Point::x = x;
    }

    double getY() const {
        return y;
    }

    void setY(double y) {
        Point::y = y;
    }

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }
};


// TODO add comments
class Figure {
private:
    Point center; // агрегаця
    string name;

protected:
    void validate_positive(double param, string param_name) {
        if (param <= 0) {
            std::stringstream message;
            message << param_name << " cannot be negative or zero";
            throw InvalidParamException(message.str());
        }
    }

public:
    Figure(const Point &center, const string &name) : center(center), name(name) {}

    virtual double getSquare() const = 0;

    const Point &getCenter() const {
        return center;
    }

    void setCenter(const Point &center) {
        Figure::center = center;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Figure::name = name;
    }

    friend ostream &operator<<(ostream &os, const Figure &figure) {
        os << "name: " << figure.name << "; center: " << figure.center << "; square = " << figure.getSquare();
        return os;
    }
};

class Round : public Figure { // успадкування
private:
    double radius;

public:
    Round(const Point &center, const string &name, double radius) : Figure(center, name) {
        validate_positive(radius, "radius");
        this->radius = radius;
    }

    double getSquare() const override {
        return 3.14 * radius * radius;
    }

    double getRadius() const {
        return radius;
    }

    void setRadius(double radius) {
        validate_positive(radius, "radius");
        Round::radius = radius;
    }

    friend ostream &operator<<(ostream &os, const Round &round) {
        os << static_cast<const Figure &>(round) << " radius: " << round.radius;
        return os;
    }
};

class Triangle : public Figure {
private:
    Point a;
    Point b;
    Point c;

    Point &compute_center(const Point &a, const Point &b, const Point &c) {
        double x_center = (a.getX() + b.getX() + c.getX()) / 3;
        double y_center = (a.getY() + b.getY() + c.getY()) / 3;
        return * new Point(x_center, y_center);
    }


public:
    Triangle(const Point &a, const Point &b, const Point &c, const string &name) :
        Figure(compute_center(a, b,c), name), a(a), b(b), c(c) {}

    double getSquare() const override {
        double determinant = (
                (a.getX()-c.getX()) * (b.getY()-c.getY()) -
                (a.getY() - c.getY()) * (b.getX() - c.getX())
                );
        if (determinant < 0) {
            determinant *= -1;
        }
        return determinant / 2;
    }

    const Point &getA() const {
        return a;
    }

    void setA(const Point &a) {
        Triangle::a = a;
    }

    const Point &getB() const {
        return b;
    }

    void setB(const Point &b) {
        Triangle::b = b;
    }

    const Point &getC() const {
        return c;
    }

    void setC(const Point &c) {
        Triangle::c = c;
    }

    friend ostream &operator<<(ostream &os, const Triangle &triangle) {
        os << static_cast<const Figure &>(triangle) << "; a: " << triangle.a << "; b: " << triangle.b << "; c: "
           << triangle.c;
        return os;
    }
};

class Rectangle : public Figure {
    double a_length;
    double b_length;

public:
    Rectangle(const Point &center, const string &name, double a_length, double b_length) :
    Figure(center, name) {
        validate_positive(a_length, "Rectangle side length");
        validate_positive(b_length, "Rectangle side length");
        this->a_length = a_length;
        this->b_length = b_length;
    }

    double getSquare() const override {
        return a_length * b_length;
    }

    double getA_length() const {
        return a_length;
    }

    void setA_length(double a_length) {
        validate_positive(a_length, "Rectangle side length");
        Rectangle::a_length = a_length;
    }

    double getB_length() const {
        return b_length;
    }

    void setB_length(double b_length) {
        validate_positive(b_length, "Rectangle side length");
        Rectangle::b_length = b_length;
    }

    friend ostream &operator<<(ostream &os, const Rectangle &rectangle) {
        // TODO note: why do we do static_cast here?
        os << static_cast<const Figure &>(rectangle) << " A side length: " << rectangle.a_length << "; B side length: "
           << rectangle.b_length << ";";
        return os;
    }
};

class Ellipse : public Figure {
    double radius_1;
    double radius_2;

public:
    Ellipse(const Point &center, const string &name, double radius_1, double radius_2) :
    Figure(center, name) {
        validate_positive(radius_1, "radius");
        validate_positive(radius_2, "radius");
        this->radius_1 = radius_1;
        this->radius_2 = radius_2;
    }

    double getSquare() const override {
        return 3.14 * radius_1 * radius_2;
    }

    double getRadius_1() const {
        return radius_1;
    }

    void setRadius_1(double radius_1) {
        validate_positive(radius_1, "radius");
        Ellipse::radius_1 = radius_1;
    }

    double getRadius_2() const {
        return radius_2;
    }

    void setRadius_2(double radius_2) {
        validate_positive(radius_2, "radius");
        Ellipse::radius_2 = radius_2;
    }

    friend ostream &operator<<(ostream &os, const Ellipse &ellipse) {
        os << static_cast<const Figure &>(ellipse) << " radius_1: " << ellipse.radius_1 << "; radius_2: "
           << ellipse.radius_2;
        return os;
    }
};

class FiguresContainer {
private:
    vector<Figure*> *figures;
    int currentSize = 0;
    int maxSize;

public:
    FiguresContainer(const unsigned int size) {
        figures = new vector<Figure*>(size);
        // TODO remove
        cout << "Created vector. Input size = " << size << "; vector size = " << figures -> size() << endl;
        maxSize = size;
    }

    virtual ~FiguresContainer() {
        delete figures;
    }


    void addFigure(Figure *figure) {
        // TODO remove
        if (currentSize == maxSize) {
            throw ContainerIsFullException("Container is full and cannot accept new elements");
        }
        cout << "Current size is = " << currentSize << endl;
        (*figures)[currentSize] = figure;
        cout << "Inserted figure. Vector size = " << figures->size() << endl;
        currentSize++;
    }

    int getSize() const {
        return currentSize;
    }

    template <class T>
    T getAverageSquare() {
        T squareSum = 0;
        for (int i = 0; i < currentSize; i++) {
            squareSum += figures->at(i)->getSquare();
        }
        return squareSum / currentSize;
    }

    template <class T>
    T getAverageX() {
        T xSum = 0;
        for (int i = 0; i < currentSize; i++) {
            xSum += figures->at(i)->getCenter().getX();
        }
        return xSum / currentSize;
    }

    Figure &operator[](unsigned long index) {
        cout << "Figures size = " << figures->size() << "; index = " << index << endl;
        if (index > currentSize) {
            throw "Index is larger than number of existing figures";
        }
        return * (figures->at(index));
    }

    friend ostream &operator<<(ostream &os, FiguresContainer &container) {
        // TODO remove
        cout << "Start printing container" << endl;
        for (int i = 0; i < container.getSize(); i++) {
            cout << "Printing element #" << i << endl;
            os << container[i] << endl;
        }
        return os;
    }
};

template <class T>
T read_input() {
    T input;
    std::cin >> input;

    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
        std::cout << "Incorrect input type. Try again: ";
        std::cin >> input;
    }

    return input;
}

Point* create_center() {
    double x;
    double y;

    cout << "Enter Figure Center X: ";
    x = read_input<double>();

    cout << "Enter Figure Center Y: ";
    y = read_input<double>();

    return new Point(x, y);
}

string& create_name() {
    string name;

    cout << "Enter Figure Name: ";
    cin >> name;

    return name;
}

Round* create_round() {
    while (true) {
        try {
            Point* center = create_center();
            double radius;

            cout << "Enter Round Radius: ";
            radius = read_input<double>();

            return new Round(*center, create_name(), radius);
        } catch (InvalidParamException& e) {
            cout << "Error on data input: " <<  e.getMessage() << ". Try again" << endl;
        }
    }
}

unsigned int number_of_rounds = 2;
void add_rounds(FiguresContainer* figuresContainer) {
    for (int i = 0; i < number_of_rounds; i++) {
        figuresContainer->addFigure(create_round());
    }
}

void dev_main() {
    Point *point = new Point(2, 1.5);
    Round *round = new Round(*point, "my round", 2.5);

    Point *a = new Point(40, 20);
    Point *b = new Point(60, 40);
    Point *c = new Point(80, 20);
    Triangle *triangle = new Triangle(*a, *b, *c, "my triangle");

    Rectangle *rectangle = new Rectangle(*point, "my rectangle", 4, 2.5);
    Ellipse *ellipse = new Ellipse(*point, "my ellipse", 4, 2.5);

    FiguresContainer* container = new FiguresContainer(4);
    container->addFigure(round);
    container->addFigure(triangle);
    container->addFigure(rectangle);
    container->addFigure(ellipse);


    cout << "Just figures: " << endl;
    cout << endl;

    cout << *point << endl;
    cout << *round << endl;
    cout << *triangle << endl;
    cout << *rectangle << endl;
    cout << *ellipse << endl;
    cout << endl;

    cout << "Container figures: " << endl;
    cout << *container << endl;
    cout << endl;

    cout << "Figure by index: " << endl;
    cout << (*container)[1] << endl;
    cout << endl;

    cout << "Average square double " << endl;
    cout << container->getAverageSquare<double>() << endl;
    cout << endl;

    cout << "Average square long " << endl;
    cout << container->getAverageSquare<long>() << endl;
    cout << endl;

    cout << "Average X double" << endl;
    cout << container->getAverageX<double>() << endl;
    cout << endl;

    cout << "Average X int" << endl;
    cout << container->getAverageX<int>() << endl;
    cout << endl;


    try {
        round->setRadius(0);
    } catch (const InvalidParamException& e) {
        cout << e.getMessage() << endl;
    }

    try {
        (*container)[100];
    } catch (const char* msg) {
        cout << msg << endl;
    }

    try {
        new Rectangle(*point, "my rectangle", -4, 2.5);
    } catch (const InvalidParamException& e) {
        cout << e.getMessage() << endl;
    }


    delete(round);
    delete(point);
    delete(triangle);
    delete(a);
    delete(b);
    delete(c);
    delete(rectangle);
    delete(ellipse);
    delete(container);
}

void menu() {
    setlocale(LC_ALL, "Russian");
    int key;
//    int temp;
//    ListQuart list;
    FiguresContainer* container = nullptr;
    // меню
    do {
        cout << " -----------------------------------" << endl;
        cout << "| Enter 1 to input data ->          |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 2 to output data ->         |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 3 to write data to file ->  |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 4 to read data from file -> |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 5 to search data ->         |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "| Enter 0 to exit ->                |" << endl;
        cout << " -----------------------------------" << endl;
        cout << "Make your choice -> ";
        key = read_input<int>();
        switch (key) {
            case 1:
                clear();
                container = new FiguresContainer(number_of_rounds);
                add_rounds(container);
                // TODO remove
                cout << *container << endl;
//                list.inputPerfomers(list);
                delay();
                break;
//            case 2:
//                clear();
//                list.show();
//                delay();
//                break;
//            case 3:
//                clear();
//                cout << "Enter 1 to write data in txt file: " << endl;
//                cout << "Enter 2 to write data in binary txt file: " << endl;
//                cin >> temp;
//                if (temp == 1) {
//                    list.file.write(list.lib);
//                }
//                else {
//                    list.file.writeBin(list.lib);
//                }
//                delay();
//                break;
//            case 4:
//                clear();
//                cout << "Enter 1 to read data from txt file: " << endl;
//                cout << "Enter 2 to read data from binary txt file: " << endl;
//                cin >> temp;
//                if (temp == 1) {
//                    list.file.read(list.lib);
//                }
//                else {
//                    list.file.readBin(list.lib);
//                }
//                delay();
//                break;
//            case 5:
//                clear();
//                cout << "Enter 1 to search for performance time: " << endl;
//                cout << "Enter 2 to search for opus: " << endl;
//                cin >> temp;
//                if (temp == 1) {
//                    int time;
//                    cout << "Enter time: ";
//                    cin >> time;
//                    list.search(time);
//                }
//                else {
//                    string opus;
//                    cout << "Enter opus: ";
//                    cin >> opus;
//                    list.search(opus);
//                }
//                delay();
//                break;
            case 0:
                break;
            default:
                cout << "Repeat your choice: ";
                break;
        }
    } while (key != 0);
}

int main() {
    dev_main();
//    marina();
    menu();





    return 0;

}
