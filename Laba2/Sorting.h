#pragma once
#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

// Базовый класс для сортировки
class Sorting {
protected:
    std::vector<int> arr;  // Динамический массив для сортировки

public:
    // Конструктор для ввода массива вручную
    Sorting(const std::vector<int>& inputArray);

    // Виртуальный метод сортировки
    virtual void sort() = 0;

    // Метод для вывода массива
    void printArray();
};

// Класс для сортировки выбором
class Choice : public Sorting {
public:
    // Конструктор наследует от базового класса
    Choice(const std::vector<int>& inputArray);

    // Переопределение метода сортировки выбором
    void sort() override;
};

// Класс для быстрой сортировки
class Quick : public Sorting {
public:
    // Конструктор наследует от базового класса
    Quick(const std::vector<int>& inputArray);

    // Переопределение метода сортировки (быстрая сортировка)
    void sort() override;

private:
    void quickSort(int low, int high);
    int partition(int low, int high);
};

// Класс для управления сортировками
class SortManager {
public:
    // Метод для выбора источника ввода данных и сортировки
    static void process();
};

#endif  // SORTING_H
