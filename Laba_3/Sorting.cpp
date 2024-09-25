#include "Sorting.h"

Heptagon::Heptagon() {
    n = 7;
    vertices = new Point[n];
}

void Heptagon::input() {
    for (int i = 0; i < n; i++) {
        std::cin >> vertices[i].x >> vertices[i].y;
    }
}

void Heptagon::area() {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += (vertices[i].x * vertices[(i + 1) % n].y) - (vertices[i].y * vertices[(i + 1) % n].x);
    }
    square = std::fabs(result) / 2.0;
}

void Heptagon::center() {
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

void Heptagon::rotate(double angle) {
    double rad = angle * M_PI / 180.0;
    for (int i = 0; i < n; i++) {
        double x = vertices[i].x - сenter.x;
        double y = vertices[i].y - сenter.y;
        vertices[i].x = сenter.x + (x * std::cos(rad) - y * std::sin(rad));
        vertices[i].y = сenter.y + (x * std::sin(rad) + y * std::cos(rad));
    }
}

void Heptagon::move(int dx, int dy) {
    for (int i = 0; i < n; i++) {
        vertices[i].x += dx;
        vertices[i].y += dy;
    }
}

Octagon::Octagon() {
    n = 8;
    vertices = new Point[n];
}

void Octagon::input() {
    for (int i = 0; i < n; i++) {
        std::cin >> vertices[i].x >> vertices[i].y;
    }
}

void Octagon::area() {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += (vertices[i].x * vertices[(i + 1) % n].y) - (vertices[i].y * vertices[(i + 1) % n].x);
    }
    square = std::fabs(result) / 2.0;
}

void Octagon::center() {
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

void Octagon::rotate(double angle) {
    double rad = angle * M_PI / 180.0;
    for (int i = 0; i < n; i++) {
        double x = vertices[i].x - сenter.x;
        double y = vertices[i].y - сenter.y;
        vertices[i].x = сenter.x + (x * std::cos(rad) - y * std::sin(rad));
        vertices[i].y = сenter.y + (x * std::sin(rad) + y * std::cos(rad));
        std::cout << vertices[i].x << " " << vertices[i].y << std::endl;
    }
}

void Octagon::move(int dx, int dy) {
    for (int i = 0; i < n; i++) {
        vertices[i].x += dx;
        vertices[i].y += dy;
    }
}

Shape* FactoryShape::createShape(char ch) {
    switch (ch) {
    case 'H': return new Heptagon;
    case 'O': return new Octagon;
    default: return nullptr;
    }
}

//Метод для сравнения площадей
int Operations::Compare(Shape* first, Shape* second) {
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
bool Operations::isIntersect(Shape* first, Shape* second) {
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
bool Operations::isInclude(Shape* first, Shape* second) {
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
