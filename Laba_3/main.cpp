#include "Sorting.h"

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
            if (!shape1) throw 1;  // Генерация исключения для неизвестного типа
            shape1->input();
            shape1->area();
            shape1->center();
            std::cout << "Площадь фигуры равна: " << shape1->getSquare() << std::endl;
            std::cout << "Центр тяжести:\n x = " << shape1->getCenter().x << " y = " << shape1->getCenter().y << std::endl;

            std::cout << "Хотите переместить фигуру? (0 - да, 1 - нет): ";
            std::cin >> continueProgram;
            if (continueProgram == 0) {
                int dx, dy;
                std::cout << "Введите число на которое передвинуть фигуру по оси X: ";
                std::cin >> dx;
                std::cout << "Введите число на которое передвинуть фигуру по оси Y: ";
                std::cin >> dy;
                shape1->move(dx, dy);
            }

            std::cout << "Хотите повернуть фигуру? (0 - да, 1 - нет): ";
            std::cin >> continueProgram;
            if (continueProgram == 0) {
                int angle;
                std::cout << "Введите угол поворота фигуры: ";
                std::cin >> angle;
                shape1->rotate(angle);
            }

            std::cout << "Выберите вторую фигуру (H - Heptagon, O - Octagon): ";
            std::cin >> type;
            shape2 = FactoryShape::createShape(type);
            if (!shape2) throw 2;  // Генерация исключения для неизвестного типа
            shape2->input();
            shape2->area();
            shape2->center();
            std::cout << "Площадь фигуры равна: " << shape2->getSquare() << std::endl;
            std::cout << shape2->getCenter().x << " " << shape2->getCenter().y << std::endl;

            std::cout << "Хотите переместить фигуру? (0 - да, 1 - нет): ";
            std::cin >> continueProgram;
            if (continueProgram == 0) {
                int dx, dy;
                std::cout << "Введите число на которое передвинуть фигуру по оси X: ";
                std::cin >> dx;
                std::cout << "Введите число на которое передвинуть фигуру по оси Y: ";
                std::cin >> dy;
                shape2->move(dx, dy);
            }

            std::cout << "Хотите повернуть фигуру? (0 - да, 1 - нет): ";
            std::cin >> continueProgram;
            if (continueProgram == 0) {
                int angle;
                std::cout << "Введите угол поворота фигуры: ";
                std::cin >> angle;
                shape2->rotate(angle);
            }

            int Tem = Operations::Compare(shape1, shape2);
            if (Tem == 2) {
                std::cout << "Фигуры равны по площади" << std::endl;
            }
            else if(Tem == 1){
                std::cout << "Площадь второй фигуры больше первой" << std::endl;
            }
            else {
                std::cout << "Площадь первой фигуры больше второй" << std::endl;
            }

            bool flag = true;

            if (Operations::isInclude(shape1, shape2)) {
                std::cout << "Одна фигура включена в другую." << std::endl;
            }
            else {
                std::cout << "Фигуры не включены друг в друга." << std::endl;

                if (Operations::isIntersect(shape1, shape2)) {
                    std::cout << "Фигуры пересекаются." << std::endl;
                    flag = false;
                }
            }

            if (flag) {
                std::cout << "Фигуры не пересекаются." << std::endl;
            }

            // Освобождаем память
            delete shape1;
            delete shape2;
        }
        catch (int num) {
            if (num == 1) {
                std::cerr << "Ошибка:Неверный тип первой фигуры!" << std::endl;
            }
            else if (num == 2) {
                std::cerr << "Ошибка:Неверный тип второй фигуры!" << std::endl;
            }
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
Площадь фигуры равна: 74
Центр тяжести:
 x = 5.39416 y = 1.09094

H
2 -1
2 3
5 6
8 3
9 -1
8 -3
4 -3
Площадь фигуры равна: 46
5.33499 0.941767
*/
