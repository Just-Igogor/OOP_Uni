#include "Sorting.h"

// Функция для вывода названий фильмов без повторов (пункт a)
void displayUniqueMovieTitles(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл!");
    }

    std::set<std::string> movie_titles; // Контейнер для хранения уникальных названий фильмов
    std::string line;

    while (std::getline(file, line)) {
        // Считываем только название фильма (предполагаем, что это первое слово в строке)
        std::string movie_name = line.substr(0, line.find(' '));
        movie_titles.insert(movie_name);
    }

    file.close();

    std::cout << "Перечень названий фильмов без повторов:" << std::endl;
    for (const auto& title : movie_titles) {
        std::cout << title << std::endl;
    }
}

// Функция для вывода названий фильмов без повторов (пункт a)
void displayUniqueMovieTitles(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл!");
    }

    std::set<std::string> movie_titles; // Контейнер для хранения уникальных названий фильмов
    std::string line;

    while (std::getline(file, line)) {
        // Считываем только название фильма (предполагаем, что это первое слово в строке)
        std::string movie_name = line.substr(0, line.find(' '));
        movie_titles.insert(movie_name);
    }

    file.close();

    std::cout << "Перечень названий фильмов без повторов:" << std::endl;
    for (const auto& title : movie_titles) {
        std::cout << title << std::endl;
    }
}

// Функция для вывода среднего процента заполнения зала для запрашиваемого фильма (пункт b)
void displayMovieOccupancy(const std::vector<Cinema>& cinemas, const std::string& movie_name) {
    // Поиск фильма в векторе
    auto it = std::find_if(cinemas.begin(), cinemas.end(), [&movie_name](const Cinema& cinema) {
        return cinema.movie_name == movie_name;
        });

    if (it != cinemas.end()) {
        std::cout << "Средний процент заполнения зала для фильма \"" << movie_name << "\": "
            << it->getOccupancy() << "%" << std::endl;
    }
    else {
        std::cout << "Фильм \"" << movie_name << "\" не найден." << std::endl;
    }
}

// Функция для чтения данных о киносеансах из файла и создания объектов Cinema
std::vector<Cinema> readCinemaData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл!");
    }

    std::vector<Cinema> cinemas; // Вектор для хранения объектов Cinema
    std::string name, time;
    int seats, viewers;
    double price;

    while (file >> name >> seats >> viewers >> price >> time) {
        // Создаем объект Cinema и добавляем его в вектор
        cinemas.emplace_back(name, seats, viewers, price, time);
    }

    file.close();
    return cinemas;
}
