#include "Sorting.h"

// Реализация конструктора базового класса Sorting
Sorting::Sorting(const std::vector<int>& inputArray) {
    arr = inputArray;
}

// Метод для вывода массива
void Sorting::printArray() {
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Конструктор для класса Choice (сортировка выбором)
Choice::Choice(const std::vector<int>& inputArray) : Sorting(inputArray) {}

// Метод сортировки выбором
void Choice::sort() {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

// Конструктор для класса Quick (быстрая сортировка)
Quick::Quick(const std::vector<int>& inputArray) : Sorting(inputArray) {}

// Метод быстрой сортировки
void Quick::sort() {
    quickSort(0, arr.size() - 1);
}

// Вспомогательный метод для быстрой сортировки
void Quick::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

// Метод для разбиения массива в быстрой сортировке
int Quick::partition(int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Метод для управления процессом сортировки
void SortManager::process() {
    while (true) {
        std::vector<int> inputArray;

        int inputChoice;
        std::cout << "\nВыберите способ ввода данных:\n";
        std::cout << "1. Ввод с консоли\n";
        std::cout << "2. Ввод из файла\n";
        std::cout << "3. Завершить программу\n";
        std::cin >> inputChoice;

        if (inputChoice == 3) {
            std::cout << "Программа завершена.\n";
            break;
        }

        if (inputChoice == 1) {
            // Ввод с консоли
            int size;
            std::cout << "Введите количество элементов массива: ";
            std::cin >> size;

            inputArray.resize(size);
            std::cout << "Введите элементы массива: ";
            for (int i = 0; i < size; ++i) {
                std::cin >> inputArray[i];
            }
        }
        else if (inputChoice == 2) {
            // Ввод из файла
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;

            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Не удалось открыть файл\n";
                continue;  // Возвращаемся к выбору
            }

            int size;
            file >> size;  // Чтение первой строки - размера массива
            inputArray.resize(size);  // Устанавливаем размер массива

            for (int i = 0; i < size; ++i) {
                file >> inputArray[i];  // Заполняем массив из файла
            }
        }
        else {
            std::cerr << "Неверный выбор. Попробуйте снова.\n";
            continue;
        }

        // Выбор типа сортировки
        int sortChoice;
        std::cout << "\nВыберите тип сортировки:\n";
        std::cout << "1. Сортировка выбором\n";
        std::cout << "2. Быстрая сортировка\n";
        std::cin >> sortChoice;

        if (sortChoice == 1) {
            // Сортировка выбором
            Choice choiceSort(inputArray);
            std::cout << "Сортировка выбором:\n";
            choiceSort.sort();
            choiceSort.printArray();
        }
        else if (sortChoice == 2) {
            // Быстрая сортировка
            Quick quickSort(inputArray);
            std::cout << "Быстрая сортировка:\n";
            quickSort.sort();
            quickSort.printArray();
        }
        else {
            std::cerr << "Неверный выбор сортировки. Попробуйте снова.\n";
        }

        // Предложить продолжить или завершить работу
        char continueChoice;
        std::cout << "Хотите продолжить? (y/n): ";
        std::cin >> continueChoice;
        if (continueChoice == 'n' || continueChoice == 'N') {
            std::cout << "Программа завершена.\n";
            break;
        }
    }
}
