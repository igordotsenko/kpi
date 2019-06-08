#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

unsigned int number_of_rounds = 3;
unsigned int number_of_triangles = 3;
unsigned int number_of_rectangles = 2;
unsigned int number_of_ellipses = 2;
unsigned int total_number_of_figures = number_of_rounds + number_of_triangles + number_of_rectangles + number_of_ellipses;


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

//template <class T>
class Serializable {
public:

    Serializable() {}

    virtual void serialize(ofstream &fout) = 0;
    virtual void deserialize(ifstream &fin) = 0;
};

class Point : public Serializable { // клас Точка
private: // приватні поля та методи
    double x;
    double y;

public: // публічні поля та методи
    Point(double x, double y) : x(x), y(y) {}

    Point() {
    }

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

    void serialize(ofstream &fout) override {
        fout.write((char*) this, sizeof(Point));
    }

    void deserialize(ifstream &fin) override {
        fin.read((char*) this, sizeof(Point));
    }

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << "( " << point.x << " , " << point.y << " )";
        return os;
    }

    friend istream &operator>>(istream &is, Point &point) {
        string brace, delim, brace2;
        is >> brace >> point.x >> delim >> point.y >> brace2;
        return is;
    }
};


// TODO add comments
class Figure : public Serializable {
private:
    Point* center; // агрегаця
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
    Figure(Point* center, const string &name) {
        string newName = string(name);
        std::replace(newName.begin(), newName.end(), ' ', '_');
        this->name = newName;
        this->center = center;
    }

    Figure() {}

    virtual ~Figure() {
        delete center;
    }

    virtual bool contains_value(double value) {
        return center->contains_value(value) || getSquare() == value;
    }

    virtual bool contains_string(const string str) {
        return name.find(str) != std::string::npos;
    }

    virtual double getSquare() const = 0;

    virtual void describe_basic_params(ostream &os) const {
        os << "name= " << name << " center= " << *center << " square= " << getSquare() << " ";
    }

    virtual void read_basic_params(istream &is) {
        string name, center, square, squareValue;
        auto newCenter = new Point();
        is >> name >> this->name >> center >> *newCenter >> square >> squareValue;
        this->center = newCenter;
    }

    virtual void read_specific_params(istream &is) = 0;

    virtual void describe_specific_params(ostream &os) const = 0;

    virtual string describe_specific_params() const {
        stringstream ss;
        describe_specific_params(ss);
        return ss.str();
    }

    void serialize(ofstream &fout) override {
        fout.write((char*) &name, sizeof(string));
        center->serialize(fout);
    }

    void deserialize(ifstream &fin) override {
        fin.read((char*) &name, sizeof(string));
        center = new Point();
        center->deserialize(fin);
    }

    const Point &getCenter() const {
        return *center;
    }

    void setCenter(Point* center) {
        Figure::center = center;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Figure::name = name;
    }

    friend ostream &operator<<(ostream &os, const Figure &figure) {
        figure.describe_basic_params(os);
        figure.describe_specific_params(os);
        return os;
    }

    friend istream &operator>>(istream &is, Figure& figure) {
        figure.read_basic_params(is);
        figure.read_specific_params(is);
        return is;
    }
};

class Triangle : public Figure {
private:
    Point* a;
    Point* b;
    Point* c;

    Point* compute_center(const Point &a, const Point &b, const Point &c) {
        double x_center = (a.getX() + b.getX() + c.getX()) / 3;
        double y_center = (a.getY() + b.getY() + c.getY()) / 3;
        return new Point(x_center, y_center);
    }

public:
    Triangle(Point* a, Point* b, Point* c, const string &name) :
        Figure(compute_center(*a, *b, *c), name), a(a), b(b), c(c) {}

    Triangle() {}

//    Triangle(Triangle& anotherTriangle) : Figure(anotherTriangle) {
//            this->a = anotherTriangle.a;
//            this->b = anotherTriangle.b;
//            this->c = anotherTriangle.c;
//    }

    virtual ~Triangle() {
        delete a;
        delete b;
        delete c;
    }

    bool contains_value(double value) override {
        return Figure::contains_value(value) || a->contains_value(value)
        || b->contains_value(value) || c->contains_value(value);
    }

    double getSquare() const override {
        double determinant = (
                (a->getX()-c->getX()) * (b->getY()-c->getY()) -
                (a->getY() - c->getY()) * (b->getX() - c->getX())
                );
        if (determinant < 0) {
            determinant *= -1;
        }
        return determinant / 2;
    }

    void describe_specific_params(ostream &os) const override {
        os << "Vertex_A= " << *a << " Vertex_B= " << *b << " Vertex_C= " << *c;
    }

    void read_specific_params(istream &is) override {
        string vert_a, vert_b, vert_c;
        auto newA = new Point();
        auto newB = new Point();
        auto newC = new Point();
        is >> vert_a >> *newA >> vert_b >> *newB >> vert_c >> *newC;
        this->a = newA;
        this->b = newB;
        this->c = newC;
    }


    void serialize(ofstream &fout) override {
        Figure::serialize(fout);
        a->serialize(fout);
        b->serialize(fout);
        c->serialize(fout);
    }

    void deserialize(ifstream &fin) override {
        Figure::deserialize(fin);
        a = new Point();
        b = new Point();
        c = new Point();
        a->deserialize(fin);
        b->deserialize(fin);
        c->deserialize(fin);
    }

    const Point &getA() const {
        return *a;
    }

    void setA(Point *a) {
        Triangle::a = a;
    }

    const Point &getB() const {
        return *b;
    }

    void setB(Point *b) {
        Triangle::b = b;
    }

    const Point &getC() const {
        return *c;
    }

    void setC(Point *c) {
        Triangle::c = c;
    }
};

class Rectangle : public Figure {
    double a_length;
    double b_length;

public:
    Rectangle(Point* center, const string &name, double a_length, double b_length) :
    Figure(center, name) {
        validate_positive(a_length, "Rectangle side length");
        validate_positive(b_length, "Rectangle side length");
        this->a_length = a_length;
        this->b_length = b_length;
    }

    Rectangle() {}

//    Rectangle(Rectangle& anotherRectangle) : Figure(anotherRectangle) {
//        validate_positive(anotherRectangle.a_length, "Rectangle side length");
//        validate_positive(anotherRectangle.b_length, "Rectangle side length");
//        this->a_length = anotherRectangle.a_length;
//        this->b_length = anotherRectangle.b_length;
//    }

    bool contains_value(double value) override {
        return Figure::contains_value(value) || a_length == value || b_length == value;
    }

    double getSquare() const override {
        return a_length * b_length;
    }

    void describe_specific_params(ostream &os) const override {
        os << "Side_A_length= " << a_length << " Side_B_length= " << b_length;
    }

    void read_specific_params(istream &is) override {
        string side_a, side_b;
        is >> side_a >> this->a_length >> side_b >> this->b_length;
    }

    void serialize(ofstream &fout) override {
        Figure::serialize(fout);
        fout.write((char*) &a_length, sizeof(double));
        fout.write((char*) &b_length, sizeof(double));
    }

    void deserialize(ifstream &fin) override {
        Figure::deserialize(fin);
        fin.read((char*) &a_length, sizeof(double));
        fin.read((char*) &b_length, sizeof(double));
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
};

class Ellipse : public Figure {
    double radius_1;
    double radius_2;

public:
    Ellipse(Point* center, const string &name, double radius_1, double radius_2) :
    Figure(center, name) {
        validate_positive(radius_1, "radius");
        validate_positive(radius_2, "radius");
        this->radius_1 = radius_1;
        this->radius_2 = radius_2;
    }

    Ellipse() {}

    virtual bool contains_value(double value) {
        return Figure::contains_value(value) || radius_1 == value || radius_2 == value;
    }

    double getSquare() const override {
        return 3.14 * radius_1 * radius_2;
    }

    void describe_specific_params(ostream &os) const override {
        os << "Radius= " << radius_1 << " Radius_2= " << radius_2;
    }

    void read_specific_params(istream &is) override {
        string radius, radius2;
        is >> radius >> this->radius_1 >> radius2 >> this->radius_2;
    }

    void serialize(ofstream &fout) override {
        Figure::serialize(fout);
        fout.write((char*) &radius_1, sizeof(double));
        fout.write((char*) &radius_2, sizeof(double));
    }

    void deserialize(ifstream &fin) override {
        Figure::deserialize(fin);
        fin.read((char*) &radius_1, sizeof(double));
        fin.read((char*) &radius_2, sizeof(double));
    }

    double getRadius_1() const {
        return radius_1;
    }

    virtual void setRadius_1(double radius_1) {
        validate_positive(radius_1, "radius");
        Ellipse::radius_1 = radius_1;
    }

    double getRadius_2() const {
        return radius_2;
    }

    virtual void setRadius_2(double radius_2) {
        validate_positive(radius_2, "radius");
        Ellipse::radius_2 = radius_2;
    }
};

class Round : public Ellipse { // успадкування

public:
    Round(Point* center, const string &name, double radius) : Ellipse(center, name, radius, radius) {}

//    Round(Round& anotherRound) : Ellipse(anotherRound) {}

    Round() : Ellipse() {}


    void describe_specific_params(ostream &os) const override {
        os << "Radius= " << getRadius_1();
    }

    void read_specific_params(istream &is) override {
        string radius;
        double radius_value;
        is >> radius >> radius_value;
        this->setRadius(radius_value);
    }

    void setRadius(double radius) {
        setRadius_1(radius);
        setRadius_2(radius);
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
        figures->reserve(size);
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

    Figure &operator[](int index) {
        if (index > currentSize || index < 0) {
            throw "Index is larger than number of existing figures or less than 0";
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
    cin.ignore();
    getline(cin, name);
    std::replace(name.begin(), name.end(), ' ', '_');

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

            return new Round(center, create_name(), radius);
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

            return new Triangle(a, b, c, create_name());
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
            auto length_a = read_input<double>();

            cout << "Enter Rectangle side B length:" << endl;
            auto length_b = read_input<double>();

            return new Rectangle(center, create_name(), length_a, length_b);
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
            auto radius_1 = read_input<double>();

            cout << "Enter Ellipse Radius 2:" << endl;
            auto radius_2 = read_input<double>();

            return new Ellipse(center, create_name(), radius_1, radius_2);
        } catch (InvalidParamException& e) {
            cout << "Error on data input: " <<  e.getMessage() << ". Try again" << endl;
        }
    }
}

class FileHandler {
    string file = "figures.txt";
    string binFile = "figures.bin";

private:
        Figure* read_bin_object(ifstream &fin, Figure* figure) {
            figure->deserialize(fin);
            return figure;
        }

    Figure* read_txt_figure(ifstream& fin, Figure* figure) {
        fin >> *figure;
        return figure;
    }

public:
    void write_txt(FiguresContainer &container) { // запис даних у текстовий файл
        ofstream fout;
        try {
            fout.open(file);
            if (!fout) {
                throw "File cannot be opened";
            }

            for ( int i = 0; i < container.getSize(); i++) {
                fout << container[i] << endl;
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
            for (int i = 0; i < container.getSize(); i++) {
                container[i].serialize(fout);
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
            for (int i = 0; i < number_of_rounds; i++) {
                container->addFigure(read_bin_object(fin, new Round()));
            }
            for (int i = 0; i < number_of_triangles; i++) {
                container->addFigure(read_bin_object(fin, new Triangle()));
            }
            for (int i = 0; i < number_of_rectangles; i++) {
                container->addFigure(read_bin_object(fin, new Rectangle()));
            }
            for (int i = 0; i < number_of_ellipses; i++) {
                container->addFigure(read_bin_object(fin, new Ellipse()));
            }

            fin.close();
        } catch (char err) { // обробка виключних ситуацій
            cout << err << endl;
            return nullptr;
        }
        return container;
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
            container->addFigure(read_txt_figure(fin, new Round));
        }
        for (int i = 0; i < number_of_triangles; i++) {
            container->addFigure(read_txt_figure(fin, new Triangle()));
        }
        for (int i = 0; i < number_of_rectangles; i++) {
            container->addFigure(read_txt_figure(fin, new Rectangle()));
        }
        for (int i = 0; i < number_of_ellipses; i++) {
            container->addFigure(read_txt_figure(fin, new Ellipse()));
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
    for (int i = 0; i < number_of_ellipses; i++) {
        figuresContainer->addFigure(create_ellipse());
    }
}


// TODO remove
//void dev_main() {
//    auto point = new Point(2, 1.5);
//    auto round = new Round(point, "my round", 2.5);
//
//    // serialize point
//    ofstream fout;
//    fout.open("/tmp/point.bin", ios::binary | ios::out);
//    point->serialize(fout);
//    fout.close();
//
//    ifstream fin;
//    fin.open("/tmp/point.bin", ios::binary | ios::in);
//
//    auto deser_point = new Point();
//    deser_point->deserialize(fin);
//    fin.close();
//
//    cout << "Deser point = " << *deser_point << endl;
//
//    fout.open("/tmp/point.txt");
//    fout << *point;
//    fout.close();
//
//    fin.open("/tmp/point.txt");
//
//    auto txt_point = new Point();
//    fin >> *txt_point;
//    fin.close();
//
//    cout << "TXT Point = " << *txt_point << endl;
//
//
//
//    auto a = new Point(40, 20);
//    auto b = new Point(60, 40);
//    auto c = new Point(80, 20);
//    auto triangle = new Triangle(a, b, c, "my triangle");
//
//
//    Rectangle *rectangle = new Rectangle(point, "my rectangle", 4, 2.5);
//    Ellipse *ellipse = new Ellipse(point, "my ellipse", 4, 2.5);
//
//    // serialize Round
//    fout.open("/tmp/round.bin", ios::binary | ios::out);
//    round->serialize(fout);
//    round = new Round(point, "new round", 42);;
//    round->serialize(fout);
//    fout.close();
//
//    fin.open("/tmp/round.bin", ios::binary | ios::in);
//
//    auto deser_round = new Round();
//    deser_round->deserialize(fin);
//    cout << "Deser round = " << *deser_round << endl;
//    cout << "Deser round square = " << deser_round->getSquare() << endl;
//    deser_round = new Round();
//    deser_round->deserialize(fin);
//    cout << "Deser round = " << *deser_round << endl;
//    cout << "Deser round square = " << deser_round->getSquare() << endl;
//    fin.close();
//
//    fout.open("/tmp/rext.txt");
//    fout << *triangle;
//    fout.close();
//
//    auto txt_triangle = new Triangle();
//    fin.open("/tmp/rext.txt");
//    fin >> *txt_triangle;
//    cout << "TXT Triangle: " << *txt_triangle << endl;
//
//
//
//
//    auto * container = new FiguresContainer(4);
//    container->addFigure(round);
//    container->addFigure(triangle);
//    container->addFigure(rectangle);
//    container->addFigure(ellipse);
//
//
//    cout << "Just figures: " << endl;
//    cout << endl;
//
//    cout << *point << endl;
//    cout << *round << endl;
//    cout << *triangle << endl;
//    cout << *rectangle << endl;
//    cout << *ellipse << endl;
//    cout << endl;
//
//    cout << "Container figures: " << endl;
//    cout << *container << endl;
//    cout << endl;
//
//    cout << "Figure by index: " << endl;
//    cout << (*container)[1] << endl;
//    cout << endl;
//
//    cout << "Average square double " << endl;
//    cout << container->getAverageSquare<double>() << endl;
//    cout << endl;
//
//    cout << "Average square long " << endl;
//    cout << container->getAverageSquare<long>() << endl;
//    cout << endl;
//
//    cout << "Average X double" << endl;
//    cout << container->getAverageX<double>() << endl;
//    cout << endl;
//
//    cout << "Average X int" << endl;
//    cout << container->getAverageX<int>() << endl;
//    cout << endl;
//
//    auto round_copy = new Round(*round);
//    delete round;
//    cout << "Round copy: " << endl;
//
//    cout << *round_copy << endl;
//
//
//
//    try {
//        round->setRadius_1(0);
//    } catch (const InvalidParamException& e) {
//        cout << e.getMessage() << endl;
//    }
//
//    try {
//        (*container)[100];
//    } catch (const char* msg) {
//        cout << msg << endl;
//    }
//
//    try {
//        new Rectangle(point, "my rectangle", -4, 2.5);
//    } catch (const InvalidParamException& e) {
//        cout << e.getMessage() << endl;
//    }
//
//
//    delete(round_copy);
//    delete(point);
//    delete(triangle);
//    delete(a);
//    delete(b);
//    delete(c);
//    delete(rectangle);
//    delete(ellipse);
//    delete(container);
//}

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
    cout << "Enter 2 to search by string: " << endl;
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

void clear() {
    system("clear");
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
        cout << "| Enter 0 to quit ->                |" << endl;
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
                break;
            case 2:
                clear();
                if (container == nullptr) {
                    cout << "No figures created yet" << endl;
                    break;
                }
                print_table(*container);
                break;
            case 3:
                clear();
                if (container == nullptr) {
                    cout << "No figures created yet" << endl;
                    break;
                }
                write(fileHandler, *container);
                break;
            case 4:
                clear();
                container = read(fileHandler, container);
                break;
            case 5:
                clear();
                if (container == nullptr) {
                    cout << "No figures created yet" << endl;
                    break;
                }
                search(container);
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
    menu();

    return 0;

}
