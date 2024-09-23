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
    Point* vertices = nullptr;  // Массив точек
    int n = 0;                  // Количество вершин
public:
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
        double xc = 0, yc = 0;
        double P = 0;
        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                double l = sqrt((vertices[i].x - vertices[0].x) * (vertices[i].x - vertices[0].x) + (vertices[i].y - vertices[0].y) * (vertices[i].y - vertices[0].y));
                xc += l * (vertices[i].x + vertices[(0) % n].x) / 2;
                yc += l * (vertices[i].y + vertices[(0) % n].y) / 2;
                P += l;
            }
            else {
                double l = sqrt((vertices[i].x - vertices[i + 1].x) * (vertices[i].x - vertices[i + 1].x) + (vertices[i].y - vertices[i + 1].y) * (vertices[i].y - vertices[i + 1].y));
                xc += l * (vertices[i].x + vertices[(i + 1) % n].x) / 2;
                yc += l * (vertices[i].y + vertices[(i + 1) % n].y) / 2;
                P += l;
            }
        }
        xc /= P;
        yc /= P;
        return { xc, yc };
    }

    void rotate(double angle) override {
        Point c = center();
        double rad = angle * M_PI / 180.0;
        for (int i = 0; i < n; i++) {
            double x = vertices[i].x - c.x;
            double y = vertices[i].y - c.y;
            vertices[i].x = c.x + (x * std::cos(rad) - y * std::sin(rad));
            vertices[i].y = c.y + (x * std::sin(rad) + y * std::cos(rad));
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
        double xc = 0, yc = 0;
        double P = 0;
        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                double l = sqrt((vertices[i].x - vertices[0].x) * (vertices[i].x - vertices[0].x) + (vertices[i].y - vertices[0].y) * (vertices[i].y - vertices[0].y));
                xc += l * (vertices[i].x + vertices[(0) % n].x) / 2;
                yc += l * (vertices[i].y + vertices[(0) % n].y) / 2;
                P += l;
            }
            else {
                double l = sqrt((vertices[i].x - vertices[i + 1].x) * (vertices[i].x - vertices[i + 1].x) + (vertices[i].y - vertices[i + 1].y) * (vertices[i].y - vertices[i + 1].y));
                xc += l * (vertices[i].x + vertices[(i + 1) % n].x) / 2;
                yc += l * (vertices[i].y + vertices[(i + 1) % n].y) / 2;
                P += l;
            }
        }
        xc /= P;
        yc /= P;
        return { xc, yc };
    }

    void rotate(double angle) override {
        Point c = center();
        double rad = angle * M_PI / 180.0;
        for (int i = 0; i < n; i++) {
            double x = vertices[i].x - c.x;
            double y = vertices[i].y - c.y;
            vertices[i].x = c.x + (x * std::cos(rad) - y * std::sin(rad));
            vertices[i].y = c.y + (x * std::sin(rad) + y * std::cos(rad));
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
    static bool compare(Shape* first, Shape* second) {
        return first->area() == second->area();
    }

    static bool isIntersect(Shape* first, Shape* second) {
        Point c1 = first->center();
        Point c2 = second->center();
        return (c1.x == c2.x && c1.y == c2.y);
    }

    static bool isInclude(Shape* first, Shape* second) {
        Point c1 = first->center();
        Point c2 = second->center();
        return (std::abs(c1.x - c2.x) < 10 && std::abs(c1.y - c2.y) < 10);
    }
};

int main() {
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

            if (Operations::compare(shape1, shape2)) {
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
