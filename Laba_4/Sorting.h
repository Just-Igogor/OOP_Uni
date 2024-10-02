#ifndef SORTING_H
#define SORTING_H
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <stdexcept>

// Класс Cinema, представляющий информацию о фильмах в кинотеатре
class Cinema {
public:
    std::string movie_name; // Название фильма
    int total_seats;   // Общее количество мест
    int viewers;       // Количество зрителей
    double ticket_price; // Стоимость билета
    std::string session_time; // Время начала сеанса

    // Конструктор класса
    Cinema(std::string name, int seats, int viewers, double price, std::string time)
        : movie_name(name), total_seats(seats), viewers(viewers), ticket_price(price), session_time(time) {}

    // Метод для вычисления процента заполнения зала
    double getOccupancy() const {
        return (static_cast<double>(viewers) / total_seats) * 100;
    }
};

// Функция для вывода названий фильмов без повторов (пункт a)
void displayUniqueMovieTitles(const std::string& filename);

// Функция для вывода среднего процента заполнения зала для запрашиваемого фильма (пункт b)
void displayMovieOccupancy(const std::vector<Cinema>& cinemas, const std::string& movie_name);

// Функция для чтения данных о киносеансах из файла и создания объектов Cinema
std::vector<Cinema> readCinemaData(const std::string& filename);
#endif // SORTING_H
