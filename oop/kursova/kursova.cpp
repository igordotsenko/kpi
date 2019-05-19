#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

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
    string file = "figures.txt";
    string binFile = "figures.bin";

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
        system("clear");
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
    // TODO solve
//    system("pause");
}
void clear() {
    system("clear");
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

    Point() {}

    bool contains_value(double value) {
        return x == value || y == value;
    }

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
        os << "(" << point.x << ", " << point.y << ")";
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

    virtual void write_to_stream(ostream &os) const {
        describe_basic_params(os);
        describe_basic_params(os);
    }

public:
    Figure(const Point &center, const string &name) : center(center), name(name) {}

    Figure() {}

    virtual bool contains_value(double value) {
        return center.contains_value(value) || getSquare() == value;
    }

    virtual bool contains_string(const string str) {
        return name.find(str) != std::string::npos;
    }

    virtual double getSquare() const = 0;

    virtual void describe_basic_params(ostream &os) const {
        os << "name: " << name << "; center = " << center << "; square = " << getSquare();
    }

    virtual string describe_basic_params() const {
        stringstream ss;
        describe_basic_params(ss);
        return ss.str();
    }

    virtual void describe_specific_params(ostream &os) const = 0;

    virtual string describe_specific_params() const {
        stringstream ss;
        describe_specific_params(ss);
        return ss.str();
    }

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
//        figure.write_to_stream(os);
        figure.describe_basic_params(os);
        os << "; ";
        figure.describe_specific_params(os);
        return os;
    }
};

// TODO extend Ellipse
class Round : public Figure { // успадкування
private:
    double radius;

protected:
    // TODO remove?
//    void write_to_stream(ostream &os) const override {
//        Figure::write_to_stream(os);
//        os << "Radius: " << radius;
//    }

public:
    Round(const Point &center, const string &name, double radius) : Figure(center, name) {
        validate_positive(radius, "radius");
        this->radius = radius;
    }

    Round(Round& anotherRound) : Figure(anotherRound) {
        this->radius = anotherRound.radius;
        validate_positive(radius, "radius");
    }

    Round() : Figure() {}

    bool contains_value(double value) override {
        return Figure::contains_value(value) || radius == value;
    }

    void describe_specific_params(ostream &os) const override {
        os << "Radius = " << radius;
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

    // TODO remove?
//    friend ostream &operator<<(ostream &os, const Round &figure) {
//        figure.write_to_stream(os);
//        return os;
//    }
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

protected:
//    void write_to_stream(ostream &os) const override {
//        Figure::write_to_stream(os);
//        os << "; a: " << a << "; b: " << b << "; c: " << c;
//    }

public:
    Triangle(const Point &a, const Point &b, const Point &c, const string &name) :
        Figure(compute_center(a, b,c), name), a(a), b(b), c(c) {}

    Triangle() {}

    Triangle(Triangle& anotherTriangle) : Figure(anotherTriangle) {
            this->a = anotherTriangle.a;
            this->b = anotherTriangle.b;
            this->c = anotherTriangle.c;
    }

    bool contains_value(double value) override {
        return Figure::contains_value(value) || a.contains_value(value)
        || b.contains_value(value) || c.contains_value(value);
    }

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

    void describe_specific_params(ostream &os) const override {
        os << "Vertex A = " << a << "; Vertex B = " << b << "; Vertex C = " << c;
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

//    friend ostream &operator<<(ostream &os, const Triangle &triangle) {
//        triangle.write_to_stream(os);
//        return os;
//    }
};

class Rectangle : public Figure {
    double a_length;
    double b_length;

protected:
//    void write_to_stream(ostream &os) const override {
//        Figure::write_to_stream(os);
//        os << "Side A length = " << a_length << "; side B length = " << b_length << ";";
//    }

public:
    Rectangle(const Point &center, const string &name, double a_length, double b_length) :
    Figure(center, name) {
        validate_positive(a_length, "Rectangle side length");
        validate_positive(b_length, "Rectangle side length");
        this->a_length = a_length;
        this->b_length = b_length;
    }

    Rectangle() {}

    Rectangle(Rectangle& anotherRectangle) : Figure(anotherRectangle) {
        validate_positive(anotherRectangle.a_length, "Rectangle side length");
        validate_positive(anotherRectangle.b_length, "Rectangle side length");
        this->a_length = anotherRectangle.a_length;
        this->b_length = anotherRectangle.b_length;
    }

    bool contains_value(double value) override {
        return Figure::contains_value(value) || a_length == value || b_length == value;
    }

    double getSquare() const override {
        return a_length * b_length;
    }

    void describe_specific_params(ostream &os) const override {
        os << "Side A length: " << a_length << "; side B length: " << b_length << ";";
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

//    friend ostream &operator<<(ostream &os, const Rectangle &rectangle) {
//        rectangle.write_to_stream(os);
//        return os;
//    }
};

class Ellipse : public Figure {
    double radius_1;
    double radius_2;

protected:
//    void write_to_stream(ostream &os) const override {
//        Figure::write_to_stream(os);
//        os << "Radius 1 = " << radius_1 << "; Radius 2 = " << radius_2;
//    }

public:
    Ellipse(const Point &center, const string &name, double radius_1, double radius_2) :
    Figure(center, name) {
        validate_positive(radius_1, "radius");
        validate_positive(radius_2, "radius");
        this->radius_1 = radius_1;
        this->radius_2 = radius_2;
    }

    Ellipse() {}

    Ellipse(Ellipse& anotherEllipse) : Figure(anotherEllipse) {
        this->radius_1 = anotherEllipse.radius_1;
        this->radius_2 = anotherEllipse.radius_2;
        validate_positive(radius_1, "radius");
        validate_positive(radius_2, "radius");
    }

    virtual bool contains_value(double value) {
        return Figure::contains_value(value) || radius_1 == value || radius_2 == value;
    }

    double getSquare() const override {
        return 3.14 * radius_1 * radius_2;
    }

    void describe_specific_params(ostream &os) const override {
        os << "Radius = " << radius_1 << "; Radius 2 = " << radius_2;
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

//    friend ostream &operator<<(ostream &os, const Ellipse &ellipse) {
//        ellipse.write_to_stream(os);
//        return os;
//    }
};

// Move to FiguresContainer?
unsigned int number_of_rounds = 2;
unsigned int number_of_triangles = 1;
unsigned int number_of_rectangles = 2;
unsigned int number_of_ellipses = 1;
unsigned int total_number_of_figures = number_of_rounds + number_of_triangles + number_of_rectangles + number_of_ellipses;

class FiguresContainer {
private:
    vector<Figure*> *figures;
    int currentSize = 0;
    int maxSize;

public:
    FiguresContainer(const unsigned int size) {
        // TODO use reserve isntead of passing to constructor
        figures = new vector<Figure*>(size);
        // TODO remove
        cout << "Created vector. Input size = " << size << "; vector size = " << figures -> size() << endl;
        maxSize = size;
    }

    virtual ~FiguresContainer() {
        delete figures;
    }


    void addFigure(Figure *figure) {
        if (currentSize == maxSize) {
            throw ContainerIsFullException("Container is full and cannot accept new elements");
        }
        (*figures)[currentSize] = figure;
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

    // TODO try to implement
//    template <class T>
//    const vector<Figure*> *find_by_value(T value, bool (*search_function)(T)) {
//        auto found = new vector<Figure*>();
//        found->reserve(total_number_of_figures);
//
//        for (int i = 0; i < currentSize; i++) {
//            Figure* figure = (*figures)[i];
//            if (search_function(value)) {
//                found->push_back(figure);
//            }
//        }
//        return found;
//    }

    const vector<Figure*> *find_by_value(double value) {
        auto found = new vector<Figure*>();
        found->reserve(total_number_of_figures);

        for (int i = 0; i < currentSize; i++) {
            Figure* figure = (*figures)[i];
            if (figure -> contains_value(value)) {
                found->push_back(figure);
            }
        }
        return found;
    }

    const vector<Figure*> *find_by_value(const string &value) {
        auto found = new vector<Figure*>();
        found->reserve(total_number_of_figures);

        for (int i = 0; i < currentSize; i++) {
            Figure* figure = (*figures)[i];
            if (figure -> contains_string(value)) {
                found->push_back(figure);
            }
        }
        return found;
    }

    Figure &operator[](unsigned long index) {
        if (index > currentSize) {
            throw "Index is larger than number of existing figures";
        }
        return * (figures->at(index));
    }

    friend ostream &operator<<(ostream &os, FiguresContainer &container) {
        for (int i = 0; i < container.getSize(); i++) {
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

Point* create_point() {
    double x;
    double y;

    cout << "Enter X: ";
    x = read_input<double>();

    cout << "Enter Y: ";
    y = read_input<double>();

    return new Point(x, y);
}

const string create_name() {
    string name;

    cout << "Enter Figure Name: ";
    cin >> name;

    return name;
}

Round* create_round() {
    while (true) {
        try {
            cout << "Enter Round center coordinates:" << endl;
            Point* center = create_point();
            double radius;

            cout << "Enter Round Radius: ";
            radius = read_input<double>();

            return new Round(*center, create_name(), radius);
        } catch (InvalidParamException& e) {
            cout << "Error on data input: " <<  e.getMessage() << ". Try again" << endl;
        }
    }
}

Triangle* create_triangle() {
    while (true) {
        try {
            cout << "Enter Triangle Vertex A coordinates:" << endl;
            Point* a = create_point();

            cout << "Enter Triangle Vertex B coordinates:" << endl;
            Point* b = create_point();

            cout << "Enter Triangle Vertex C coordinates:" << endl;
            Point* c = create_point();

            return new Triangle(*a, *b, *c, create_name());
        } catch (InvalidParamException& e) {
            cout << "Error on data input: " <<  e.getMessage() << ". Try again" << endl;
        }
    }
}

Rectangle* create_rectangle() {
    while (true) {
        try {
            cout << "Enter Rectangle Center coordinates:" << endl;
            Point* center = create_point();

            cout << "Enter Rectangle side A length:" << endl;
            double length_a = read_input<double>();

            cout << "Enter Rectangle side B length:" << endl;
            double length_b = read_input<double>();

            return new Rectangle(*center, create_name(), length_a, length_b);
        } catch (InvalidParamException& e) {
            cout << "Error on data input: " <<  e.getMessage() << ". Try again" << endl;
        }
    }
}

Ellipse* create_ellipse() {
    while (true) {
        try {
            cout << "Enter Ellipse Center coordinates:" << endl;
            Point* center = create_point();

            cout << "Enter Ellipse Radius 1:" << endl;
            double radius_1 = read_input<double>();

            cout << "Enter Ellipse Radius 2:" << endl;
            double radius_2 = read_input<double>();

            return new Ellipse(*center, create_name(), radius_1, radius_2);
        } catch (InvalidParamException& e) {
            cout << "Error on data input: " <<  e.getMessage() << ". Try again" << endl;
        }
    }
}

class FileHandler {
                // TODO avoid usage of linux path
    string file = "/tmp/figures.txt";
    string binFile = "/tmp/figures.bin";

private:
    // Write Operations
    // TODO move to classes
    void write_point(ofstream& fout, const Point& point) {
        fout << point.getX() << endl;
        fout << point.getY() << endl;
    }

    void write_round(ofstream& fout, Round& round) {
        fout << round.getName() << endl;
        write_point(fout, round.getCenter());
        fout << round.getRadius() << endl;
    }

    void write_triangle(ofstream& fout, Triangle& triangle) {
        fout << triangle.getName() << endl;
        write_point(fout, triangle.getA());
        write_point(fout, triangle.getB());
        write_point(fout, triangle.getC());
    }

    void write_rectangle(ofstream& fout, Rectangle& rectangle) {
        fout << rectangle.getName() << endl;
        write_point(fout, rectangle.getCenter());
        fout << rectangle.getA_length() << endl;
        fout << rectangle.getB_length() << endl;
    }

    void write_ellipse(ofstream& fout, Ellipse& ellipse) {
        fout << ellipse.getName() << endl;
        write_point(fout, ellipse.getCenter());
        fout << ellipse.getRadius_1() << endl;
        fout << ellipse.getRadius_2() << endl;
    }

    // Read operations
    // TODO maybe should return reference here?
    Point read_point(ifstream& fin) {
        double x;
        double y;

        fin >> x;
        fin >> y;

        return {x, y};
    }

    Round* read_round(ifstream& fin) {
        string name;
        double radius;

        fin >> name;
        Point center = read_point(fin);
        fin >> radius;

        return new Round(center, name, radius);
    }

    Triangle* read_triangle(ifstream& fin) {
        string name;
        fin >> name;

        Point a = read_point(fin);
        Point b = read_point(fin);
        Point c = read_point(fin);

        return new Triangle(a, b, c, name);
    }

    Rectangle* read_rectangle(ifstream& fin) {
        string name;
        fin >> name;

        Point center = read_point(fin);

        double a_len;
        fin >> a_len;

        double b_len;
        fin >> b_len;

        return new Rectangle(center, name, a_len, b_len);
    }

    Ellipse* read_ellipse(ifstream& fin) {
        string name;
        fin >> name;

        Point center = read_point(fin);

        double rad_1;
        fin >> rad_1;

        double rad_2;
        fin >> rad_2;

        return new Ellipse(center, name, rad_1, rad_2);
    }


public:
    void write_txt(FiguresContainer &container) { // запис даних у текстовий файл
        ofstream fout;
        try {
            fout.open(file);
            if (!fout) {
                // TODO handle
                throw "File cannot be opened.";
            }

            // TODO move to write methods to classes
            int current_index = 0;
            for (int i = 0; i < number_of_rounds; i++) {
                write_round(fout, dynamic_cast<Round&>(container[current_index++]));
            }

            for (int i = 0; i < number_of_triangles; i++) {
                write_triangle(fout, dynamic_cast<Triangle&>(container[current_index++]));
            }

            for (int i = 0; i < number_of_rectangles; i++) {
                write_rectangle(fout, dynamic_cast<Rectangle&>(container[current_index++]));
            }

            for (int i = 0; i < number_of_ellipses; i++) {
                write_ellipse(fout, dynamic_cast<Ellipse&>(container[current_index++]));
            }

            fout.close();
        } catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
        }
    }

    void write_bin(FiguresContainer &container) { // запис даних у бінарний файл
        ofstream fout;
        try
        {
            fout.open(binFile, ios::binary | ios::out);
            if (!fout) {
                throw "File cannot be opened.";
            }
            int index = 0;
            for (int i = 0; i < number_of_rounds; i++) {
                fout.write((char*)&container[index++], sizeof(Round));
            }
            for (int i = 0; i < number_of_triangles; i++) {
                fout.write((char*)&container[index++], sizeof(Triangle));
            }
            for (int i = 0; i < number_of_rectangles; i++) {
                fout.write((char*)&container[index++], sizeof(Rectangle));
            }
            for (int i = 0; i < number_of_ellipses; i++) {
                fout.write((char*)&container[index++], sizeof(Ellipse));
            }

            fout.close();
        }
        catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
        }
    }

    FiguresContainer* read_bin() { // зчитування даних з бінарного файлу
        ifstream fin;
        FiguresContainer* container;

        try {
            fin.open(binFile, ios::binary | ios::in);
            if (!fin) {
                throw "File cannot be opened.";
            }
            container = new FiguresContainer(total_number_of_figures);
            read_bin_object<Round>(fin, number_of_rounds, *container);
            read_bin_object<Triangle>(fin, number_of_triangles, *container);
            read_bin_object<Rectangle>(fin, number_of_rectangles, *container);
            read_bin_object<Ellipse>(fin, number_of_ellipses, *container);

            fin.close();
        } catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
            return nullptr;
        }

        return container;
    }

    template <class T>
    void read_bin_object(ifstream &fin, int numberOfFigures, FiguresContainer &container) {
        for (int i = 0; i < numberOfFigures; i++) {
            T tmp;
            fin.read((char*) &tmp, sizeof(T));
            auto f = new T(tmp);
            container.addFigure(f);
        }
    }

    FiguresContainer* read_txt() { // зчитування даних з текстового файлу
        ifstream fin;
        try {
            fin.open(file);
            if (!fin) {
                throw "File cannot be opened.";
            }
        } catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
        }
        auto * container = new FiguresContainer(total_number_of_figures);
        for (int i = 0; i < number_of_rounds; i++) {
            container->addFigure(read_round(fin));
        }
        for (int i = 0; i < number_of_triangles; i++) {
            container->addFigure(read_triangle(fin));
        }
        for (int i = 0; i < number_of_rectangles; i++) {
            container->addFigure(read_rectangle(fin));
        }
        for (int i = 0; i < number_of_ellipses; i++) {
            container->addFigure(read_ellipse(fin));
        }

        return container;
    }
};

void add_rounds(FiguresContainer* figuresContainer) {
    for (int i = 0; i < number_of_rounds; i++) {
        figuresContainer->addFigure(create_round());
    }
}

void add_triangles(FiguresContainer* figuresContainer) {
    for (int i = 0; i < number_of_triangles; i++) {
        figuresContainer->addFigure(create_triangle());
    }
}

void add_rectangles(FiguresContainer* figuresContainer) {
    for (int i = 0; i < number_of_rectangles; i++) {
        figuresContainer->addFigure(create_rectangle());
    }
}

void add_ellipses(FiguresContainer* figuresContainer) {
    for (int i = 0; i < number_of_triangles; i++) {
        figuresContainer->addFigure(create_ellipse());
    }
}

void dev_main() {
    Point *point = new Point(2, 1.5);
    Round *round = new Round(*point, "my round", 2.5);

    auto a = new Point(40, 20);
    auto b = new Point(60, 40);
    auto c = new Point(80, 20);
    Triangle *triangle = new Triangle(*a, *b, *c, "my triangle");

    Rectangle *rectangle = new Rectangle(*point, "my rectangle", 4, 2.5);
    Ellipse *ellipse = new Ellipse(*point, "my ellipse", 4, 2.5);

    auto * container = new FiguresContainer(4);
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

template <class T>
void find_and_print(FiguresContainer* container) {
    T value;
    cout << "Enter value: ";
    value = read_input<T>();
    auto found = container->find_by_value(value);
    cout << "Found " << found->size() << " figures:" << endl;
    for (auto found_figure : *found) {
        cout << *found_figure << endl;
    }
    delete(found);
}

void write(FileHandler& fileHandler, FiguresContainer& container) {
    cout << "Enter 1 to write data in txt file: " << endl;
    cout << "Enter 2 to write data in binary txt file: " << endl;
    int file_format = read_input<int>();
    try {
        if (file_format == 1) {
            fileHandler.write_txt(container);
        } else {
            fileHandler.write_bin(container);
        }
    } catch (FigureOperationException& e) {
        cout << e.getMessage() << endl;
    } catch (char const* e) {
        cout << e << endl;
    }
}

FiguresContainer* read(FileHandler& fileHandler, FiguresContainer* existingContainer) {
    cout << "Enter 1 to read data from txt file: " << endl;
    cout << "Enter 2 to read data from binary txt file: " << endl;
    int file_format = read_input<int>();
    FiguresContainer* newContainer = nullptr;
    try {
        if (file_format == 1) {
            newContainer = fileHandler.read_txt();
        } else {
            newContainer = fileHandler.read_bin();
        }
        delete existingContainer;
    } catch (FigureOperationException& e) {
        cout << e.getMessage() << endl;
    } catch (char const* e) {
        cout << e << endl;
    }

    return newContainer == nullptr ? existingContainer : newContainer;
}

void search(FiguresContainer* container) {
    cout << "Enter 1 to search by number: " << endl;
    cout << "Enter 2 to search for string: " << endl;
    int key = read_input<int>();
    if (key == 1) {
        find_and_print<double>(container);
    } else {
        find_and_print<string>(container);
    }
}

void print_table(FiguresContainer& container) { // виведення даних у вигляді таблиці
    string line = string(145, '-');
    printf("%s\n", line.c_str());
    printf("|%-20s|%-30s|%-10s|%-80s|\n", "Figure name", "Center", "Square", "Additional params");
    printf("%s\n", line.c_str());

    for (int i = 0; i < container.getSize(); i++) {
        Figure& figure = container[i];
        stringstream center;
        center << figure.getCenter();
        printf("|%-20s|%-30s|%-10.2f|%-80s|\n",
                figure.getName().c_str(),
                center.str().c_str(),
                figure.getSquare(),
                figure.describe_specific_params().c_str());
        printf("%s\n", line.c_str());
    }

    printf("\n\n");
    line = string(94, '-');
    printf("%s\n", line.c_str());
    printf("|%-30s|%-30s|%-30s|\n", "Average square (double)", "Average square (int)", "Average X");
    printf("%s\n", line.c_str());
    printf("|%-30.2f|%-30d|%-30.2f|\n",
            container.getAverageSquare<double>(),
            container.getAverageSquare<int>(),
            container.getAverageX<double>());
    printf("%s\n", line.c_str());
}

void menu() {
    setlocale(LC_ALL, "Russian");
    int key;
    FiguresContainer* container = nullptr;
    FileHandler fileHandler = FileHandler();

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
                container = new FiguresContainer(total_number_of_figures);
                add_rounds(container);
                add_triangles(container);
                add_rectangles(container);
                add_ellipses(container);
                delay();
                break;
            case 2:
                clear();
                if (container == nullptr) {
                    cout << "No figures created yet" << endl;
                    break;
                }
                print_table(*container);
                delay();
                break;
            case 3:
                clear();
                if (container == nullptr) {
                    cout << "No figures created yet" << endl;
                    break;
                }
                write(fileHandler, *container);
                delay();
                break;
            case 4:
                clear();
                container = read(fileHandler, container);
                delay();
                break;
            case 5:
                clear();
                if (container == nullptr) {
                    cout << "No figures created yet" << endl;
                    break;
                }
                search(container);
                delay();
                break;
            case 0:
                break;
            default:
                cout << "Repeat your choice: ";
                break;
        }
    } while (key != 0);

    delete container;
}

int main() {
//    dev_main();
//    marina();
    menu();

    return 0;

}
