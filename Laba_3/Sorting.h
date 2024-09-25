#ifndef SORTING_H
#define SORTING_H
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <exception>

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
    virtual void area() = 0;   // Виртуальный метод для вычисления площади
    virtual void center() = 0;  // Виртуальный метод для вычисления центра тяжести
    virtual void rotate(double angle) = 0;  // Метод вращения
    virtual void move(int dx, int dy) = 0;  // Метод перемещения
    virtual ~Shape() { delete[] vertices; }
};

// Класс Heptagon (Семиугольник)
class Heptagon : public Shape {
public:
    Heptagon();

    void input() override;

    void area() override;

    void center() override;

    void rotate(double angle) override;

    void move(int dx, int dy) override;

};

// Класс Octagon (Восьмиугольник)
class Octagon : public Shape {
public:
    Octagon();

    void input() override;

    void area() override;

    void center() override;

    void rotate(double angle) override;

    void move(int dx, int dy) override;

};

// Фабрика для создания объектов класса Shape
class FactoryShape {
public:
    static Shape* createShape(char ch);
};

// Класс Operations для работы с фигурами
class Operations {
public:
    //Метод для сравнения площадей
    static int Compare(Shape* first, Shape* second);

    //Метод для проверки пересечения фигур
    static bool isIntersect(Shape* first, Shape* second);

    //Метод для проверки включения одной фигуры в другую
    static bool isInclude(Shape* first, Shape* second);

};
#endif // SORTING_H
