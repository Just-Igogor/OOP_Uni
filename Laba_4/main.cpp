/*ЮФУ, ИКТИБ, МОП ЭВМ
Объектно-ориентированное программирование
КТбо2-6, Смелов Игорь Александрович
Лабораторная работа 4
03.10.2024*/
#include "Sorting.h"

/*ЮФУ, ИКТИБ, МОП ЭВМ
Объектно-ориентированное программирование
КТбо2-6, Смелов Игорь Александрович
Лабораторная работа 4
03.10.2024*/

int main() {
    setlocale(LC_ALL, "ru");
    std::string filename = "cinema.txt";

    try {
        int choice;
        std::cout << "Выберите пункт программы:\n1. Перечень названий фильмов без повторов\n2. Средний процент заполнения зала для фильма\nВаш выбор: ";
        std::cin >> choice;

        if (choice == 1) {
            // Выполнение пункта a)
            displayUniqueMovieTitles(filename);
        }
        else if (choice == 2) {
            // Выполнение пункта b)
            std::vector<Cinema> cinemas = readCinemaData(filename);

            std::string movie_name;
            std::cout << "Введите название фильма: ";
            std::cin >> movie_name;

            displayMovieOccupancy(cinemas, movie_name);
        }
        else {
            std::cout << "Некорректный выбор!" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
