/*ЮФУ, ИКТИБ, МОП ЭВМ
Объектно-ориентированное программирование
КТбо2-6, Смелов Игорь Александрович
Лабораторная работа 1
09.09.2024*/

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h> // для обнаружения утечек памяти в Visual Studio
#include <iostream> // ввод/вывод данных (консольное взаимодействие)
#include <fstream> // работа с файлами (чтение данных из файла)
#include <string> // работа со строками
#include <windows.h> // русификатор
#include <cstdlib> // генерация случайных чисел
#include <ctime> // работа с временем для инициализации генератора случайных чисел

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::cerr;
using std::to_string;
using std::runtime_error;
using std::ifstream;
using std::exception;

class Student {
private:
    string fullName; // ФИО
    string birthDate; // Дата рождения
    string address; // Адрес
    bool expelled; // учится или отчислен
    int grade;     // оценка за экзамен

public:
    Student(string _fullName, string _birthDate, string _address)
        : fullName(_fullName), birthDate(_birthDate), address(_address), expelled(false), grade(0) {}

    // Метод сдачи экзамена
    void takeExam() {
        grade = rand() % 4 + 2; // случайное значение от 2 до 5
    }

    // Метод возвращает оценку студента
    int getGrade() const {
        return grade;
    }

    // Метод отчисления студента
    void expel() {
        expelled = true;
    }

    // Проверка отчисления
    bool isExpelled() const {
        return expelled;
    }

    // Вывод информации о студенте
    void printInfo() const {
        cout << "ФИО: " << fullName << endl << "Дата рождения: " << birthDate << endl << "Адрес: " << address
            << endl << "Оценка: " << (grade ? to_string(grade) : "не сдавал") << endl << "Статус: " << (expelled ? "Отчислен" : "Учится") << endl << endl;
    }
};

class Institute {
private:
    Student** students; // Динамический массив указателей на студентов
    int numStudents;

public:
    Institute() : students(nullptr), numStudents(0) {}

    // Метод для загрузки списка студентов из файла
    void loadStudentsFromFile(const string& filename) {
        ifstream file;
        file.open(filename);

        if (!file) {
            cerr << "Ошибка: не удалось открыть файл " << filename << endl;
            throw runtime_error("Файл не найден или не может быть открыт.");
        }

        file >> numStudents;
        file.ignore(); // Игнорируем символ новой строки после ввода числа студентов

        students = new Student * [numStudents]; // Создаем динамический массив указателей на студентов

        for (int i = 0; i < numStudents; ++i) {
            string fullName, birthDate, address;
            getline(file, fullName);   // Читаем ФИО
            getline(file, birthDate);  // Читаем дату рождения
            getline(file, address);    // Читаем адрес

            students[i] = new Student(fullName, birthDate, address); // Создаем объект студента и добавляем в массив
        }

        file.close();
    }

    // Метод для ввода студентов через консоль
    void addStudentsFromConsole() {
        cout << "Введите количество студентов: ";
        cin >> numStudents;
        cin.ignore(); // Игнорируем символ новой строки после ввода числа

        students = new Student * [numStudents]; // Создаем динамический массив указателей на студентов

        for (int i = 0; i < numStudents; ++i) {
            cout << "Введите данные для студента " << i + 1 << ":" << endl;

            string fullName, birthDate, address;
            cout << "ФИО: ";
            getline(cin, fullName);
            cout << "Дата рождения (дд.мм.гггг): ";
            getline(cin, birthDate);
            cout << "Адрес: ";
            getline(cin, address);

            students[i] = new Student(fullName, birthDate, address); // Создаем объект студента и добавляем в массив
        }
    }

    // Метод проведения сессии: сдача экзаменов каждым студентом
    void conductSession() {
        for (int i = 0; i < numStudents; ++i) {
            students[i]->takeExam();
        }
    }

    // Метод для издания приказа об отчислении студентов с оценкой 2
    void issueExpulsionOrder() {
        for (int i = 0; i < numStudents; ++i) {
            if (students[i]->getGrade() == 2) {
                students[i]->expel();
            }
        }
    }

    // Метод для вывода всех студентов
    void printStudents() const {
        for (int i = 0; i < numStudents; ++i) {
            cout << "Студент " << i + 1 << endl;
            students[i]->printInfo();
        }
    }

    // Освобождение памяти при завершении работы
    ~Institute() {
        if (numStudents) {  
            for (int i = 0; i < numStudents; ++i) {
                delete students[i];  // Освобождаем память для каждого объекта Student
            }
            delete[] students;  // Освобождаем память для массива указателей
            numStudents = 0;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleOutputCP(CP_UTF8);
    srand(static_cast<unsigned>(time(0))); // Инициализация генератора случайных чисел

    Institute institute;

    // Выбор способа ввода данных
    int inputChoice;
    cout << "Выберите способ ввода студентов (1 - консоль, 2 - файл): ";
    cin >> inputChoice;
    cin.ignore(); // Игнорируем символ новой строки после ввода числа

    try {
        if (inputChoice == 1) {
            // Ввод студентов через консоль
            institute.addStudentsFromConsole();
        }
        else if (inputChoice == 2) {
            string filename;
            cout << "Введите имя файла(например list.txt): ";
            getline(cin, filename);
            // Загрузка студентов из файла
            institute.loadStudentsFromFile(filename);
        }
        else {
            cerr << "Неверный выбор." << endl;
            return 1;
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    // Проводим сессию (все студенты сдают экзамены)
    institute.conductSession();

    // Издаем приказ об отчислении студентов
    institute.issueExpulsionOrder();

    // Выводим список всех студентов и их статуса
    cout << "Результаты сессии:" << endl;
    institute.printStudents();

    institute.~Institute();
    _CrtDumpMemoryLeaks();
    return 0;
}
