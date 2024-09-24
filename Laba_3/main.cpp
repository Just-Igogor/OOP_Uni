#include <iostream>
#include <cmath>
#include <exception>

const double M_PI = 3.1415;

// Класс Point для представления точек
class Point {
public:
    double x = 0, y = 0;
};

// Абстрактный базовый класс Shape
class Shape {
protected:
    int n = 0;                  // Количество вершин
    Point* vertices = nullptr;  // Массив точек
    Point сenter{};             // Центр моногоугольника
    double square = 0;          // Площадь многоугольника
public:
    double getSquare() const {
        return square;
    }
    Point getCenter() {
        return сenter;
    }
    int getN() {
        return n;
    }
    Point* getVertices() {
        return vertices;
    }
    virtual void input() = 0;    // Виртуальный метод для ввода координат
    virtual double area() = 0;   // Виртуальный метод для вычисления площади
    virtual Point center() = 0;  // Виртуальный метод для вычисления центра тяжести
    virtual void rotate(double angle) = 0;  // Метод вращения
    virtual void move(int dx, int dy) = 0;  // Метод перемещения
    virtual ~Shape() { delete[] vertices; }
};

// Класс Heptagon (Семиугольник)
class Heptagon : public Shape {
public:
    Heptagon() {
        n = 7;
        vertices = new Point[n];
    }

    void input() override {
        for (int i = 0; i < n; i++) {
            std::cin >> vertices[i].x >> vertices[i].y;
        }
    }

    double area() override {
        double result = 0.0;
        for (int i = 0; i < n; i++) {
            result += (vertices[i].x * vertices[(i + 1) % n].y) - (vertices[i].y * vertices[(i + 1) % n].x);
        }
        return std::fabs(result) / 2.0;
    }

    Point center() override {
        double P = 0;
        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                double l = sqrt((vertices[i].x - vertices[0].x) * (vertices[i].x - vertices[0].x) + (vertices[i].y - vertices[0].y) * (vertices[i].y - vertices[0].y));
                сenter.x += l * (vertices[i].x + vertices[(0) % n].x) / 2;
                сenter.y += l * (vertices[i].y + vertices[(0) % n].y) / 2;
                P += l;
            }
            else {
                double l = sqrt((vertices[i].x - vertices[i + 1].x) * (vertices[i].x - vertices[i + 1].x) + (vertices[i].y - vertices[i + 1].y) * (vertices[i].y - vertices[i + 1].y));
                сenter.x += l * (vertices[i].x + vertices[(i + 1) % n].x) / 2;
                сenter.y += l * (vertices[i].y + vertices[(i + 1) % n].y) / 2;
                P += l;
            }
        }
        сenter.x /= P;
        сenter.y /= P;
    }

    void rotate(double angle) override {
        double rad = angle * M_PI / 180.0;
        for (int i = 0; i < n; i++) {
            double x = vertices[i].x - сenter.x;
            double y = vertices[i].y - сenter.y;
            vertices[i].x = сenter.x + (x * std::cos(rad) - y * std::sin(rad));
            vertices[i].y = сenter.y + (x * std::sin(rad) + y * std::cos(rad));
        }
    }

    void move(int dx, int dy) override {
        for (int i = 0; i < n; i++) {
            vertices[i].x += dx;
            vertices[i].y += dy;
        }
    }

    ~Heptagon() {
        delete[] vertices;
    }
};

// Класс Octagon (Восьмиугольник)
class Octagon : public Shape {
public:
    Octagon() {
        n = 8;
        vertices = new Point[n];
    }

    void input() override {
        for (int i = 0; i < n; i++) {
            std::cin >> vertices[i].x >> vertices[i].y;
        }
    }

    double area() override {
        double result = 0.0;
        for (int i = 0; i < n; i++) {
            result += (vertices[i].x * vertices[(i + 1) % n].y) - (vertices[i].y * vertices[(i + 1) % n].x);
        }
        return std::fabs(result) / 2.0;
    }

    Point center() override {
        double P = 0;
        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                double l = sqrt((vertices[i].x - vertices[0].x) * (vertices[i].x - vertices[0].x) + (vertices[i].y - vertices[0].y) * (vertices[i].y - vertices[0].y));
                сenter.x += l * (vertices[i].x + vertices[(0) % n].x) / 2;
                сenter.y += l * (vertices[i].y + vertices[(0) % n].y) / 2;
                P += l;
            }
            else {
                double l = sqrt((vertices[i].x - vertices[i + 1].x) * (vertices[i].x - vertices[i + 1].x) + (vertices[i].y - vertices[i + 1].y) * (vertices[i].y - vertices[i + 1].y));
                сenter.x += l * (vertices[i].x + vertices[(i + 1) % n].x) / 2;
                сenter.y += l * (vertices[i].y + vertices[(i + 1) % n].y) / 2;
                P += l;
            }
        }
        сenter.x /= P;
        сenter.y /= P;
    }

    void rotate(double angle) override {
        double rad = angle * M_PI / 180.0;
        for (int i = 0; i < n; i++) {
            double x = vertices[i].x - сenter.x;
            double y = vertices[i].y - сenter.y;
            vertices[i].x = сenter.x + (x * std::cos(rad) - y * std::sin(rad));
            vertices[i].y = сenter.y + (x * std::sin(rad) + y * std::cos(rad));
        }
    }

    void move(int dx, int dy) override {
        for (int i = 0; i < n; i++) {
            vertices[i].x += dx;
            vertices[i].y += dy;
        }
    }

    ~Octagon() {
        delete[] vertices;
    }
};

// Фабрика для создания объектов класса Shape
class FactoryShape {
public:
    static Shape* createShape(char ch) {
        switch (ch) {
        case 'H': return new Heptagon();
        case 'O': return new Octagon();
        default: return nullptr; 
        }
    }
};

// Класс Operations для работы с фигурами
class Operations {
public:
    //Метод для сравнения площадей
    static int Compare(Shape* first, Shape* second) {
        if (first->getSquare() > second->getSquare()) {
            return 0;
        }
        else if (first->getSquare() < second->getSquare()) {
            return 1;
        }
        else {
            return 2;
        }
    };

    //Метод для проверки пересечения фигур
    static bool isIntersect(Shape* first, Shape* second) {
        Point temp1, temp2;
        temp1 = first->getCenter();
        temp2 = second->getCenter();
        double d = sqrt((temp1.x - temp2.x) * (temp1.x - temp2.x) + (temp1.y - temp2.y) * (temp1.y - temp2.y));

        double radiusFirst = 0;
        Point* vert = first->getVertices();
        for (int i = 0; i < first->getN(); i++) {
            double dist = sqrt((temp1.x - vert[i].x) * (temp1.x - vert[i].x) + (temp1.y - vert[i].y) * (temp1.y - vert[i].y));
            if (dist > radiusFirst) {
                radiusFirst = dist;
            }
        }

        double radiusSecond = 0;
        vert = second->getVertices();
        for (int i = 0; i < second->getN(); i++) {
            double dist = sqrt((temp2.x - vert[i].x) * (temp2.x - vert[i].x) + (temp2.y - vert[i].y) * (temp2.y - vert[i].y));
            if (dist > radiusSecond) {
                radiusSecond = dist;
            }
        }

        return d <= (radiusFirst + radiusSecond);
    }

    //Метод для проверки включения одной фигуры в другую
    static bool isInclude(Shape* first, Shape* second) {
        Point temp1, temp2;
        temp1 = first->getCenter();
        temp2 = second->getCenter();

        double radiusFirst = 0;
        Point* vert = first->getVertices();
        for (int i = 0; i < first->getN(); i++) {
            double dist = sqrt((temp1.x - vert[i].x) * (temp1.x - vert[i].x) + (temp1.y - vert[i].y) * (temp1.y - vert[i].y));
            if (dist > radiusFirst) {
                radiusFirst = dist;
            }
        }
        double radiusSecond = 0;
        vert = second->getVertices();
        for (int i = 0; i < second->getN(); i++) {
            double dist = sqrt((temp2.x - vert[i].x) * (temp2.x - vert[i].x) + (temp2.y - vert[i].y) * (temp2.y - vert[i].y));
            if (dist > radiusSecond) {
                radiusSecond = dist;
            }
        }


        // Расстояние между центрами двух фигур
        double centerDistance = sqrt((temp1.x - temp2.x) * (temp1.x - temp2.x) + (temp1.y - temp2.y) * (temp1.y - temp2.y));

        // Проверка, включена ли одна окружность в другую
        return centerDistance + radiusFirst <= radiusSecond || centerDistance + radiusSecond <= radiusFirst;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    bool continueProgram = true;

    while (continueProgram) {
        try {
            Shape* shape1 = nullptr;
            Shape* shape2 = nullptr;
            char type;

            std::cout << "Выберите первую фигуру (H - Heptagon, O - Octagon): ";
            std::cin >> type;
            shape1 = FactoryShape::createShape(type);
            if(!shape1) throw std::invalid_argument("Invalid shape type!");  // Генерация исключения для неизвестного типа
            shape1->input();
            std::cout << shape1->area() << std::endl;
            std::cout << shape1->center().x << " " << shape1->center().y << std::endl;

            std::cout << "Выберите вторую фигуру (H - Heptagon, O - Octagon): ";
            std::cin >> type;
            shape2 = FactoryShape::createShape(type);
            if (!shape2) throw std::invalid_argument("Invalid shape type!");  // Генерация исключения для неизвестного типа
            shape2->input();
            std::cout << shape2->area() << std::endl;
            std::cout << shape2->center().x << " " << shape2->center().y << std::endl;

            Operations op;

            if (Operations::Compare(shape1, shape2)) {
                std::cout << "Фигуры равны по площади." << std::endl;
            }
            else {
                std::cout << "Фигуры не равны по площади." << std::endl;
            }

            if (Operations::isIntersect(shape1, shape2)) {
                std::cout << "Фигуры пересекаются." << std::endl;
            }
            else {
                std::cout << "Фигуры не пересекаются." << std::endl;
            }

            if (Operations::isInclude(shape1, shape2)) {
                std::cout << "Одна фигура включена в другую." << std::endl;
            }
            else {
                std::cout << "Фигуры не включены друг в друга." << std::endl;
            }

            // Освобождаем память
            delete shape1;
            delete shape2;

        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Произошла неизвестная ошибка." << std::endl;
        }

        // Спрашиваем у пользователя, хочет ли он продолжить
        std::cout << "Хотите завершить программу? (0 - да, 1 - нет): ";
        std::cin >> continueProgram;
    }

    return 0;
}
/*
H
1 -1
1 4
6 7
9 4
10 -1
8 -4
4 -4
74
5.57143 0.714286
*/
