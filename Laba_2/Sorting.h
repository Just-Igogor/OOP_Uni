#ifndef SORTING_H
#define SORTING_H
/*ЮФУ, ИКТИБ, МОП ЭВМ
Объектно-ориентированное программирование
КТбо2-6, Смелов Игорь Александрович
Лабораторная работа 2
19.09.2024*/
#include <vector>
#include <iostream>
#include <fstream>

// Базовый класс для сортировки
class Sorting {
protected:
    std::vector<int> arr;

public:
    Sorting(const std::vector<int>& inputArray);
    virtual void sort() = 0;  // Виртуальный метод сортировки
    void printArray();        // Метод для вывода массива
    virtual ~Sorting() {}     // Виртуальный деструктор
};

// Класс для сортировки выбором
class Choice : public Sorting {
public:
    Choice(const std::vector<int>& inputArray);
    void sort() override;  // Переопределение метода сортировки
};

// Класс для быстрой сортировки
class Quick : public Sorting {
public:
    Quick(const std::vector<int>& inputArray);
    void sort() override;  // Переопределение метода сортировки
private:
    void quickSort(int low, int high);
    int partition(int low, int high);
};

// Класс для управления процессом сортировки
class SortManager {
public:
    void process();
};

#endif // SORTING_H
