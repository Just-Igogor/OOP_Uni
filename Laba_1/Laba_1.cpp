/*���, �����, ��� ���
��������-��������������� ����������������
����2-6, ������ ����� �������������
������������ ������ 1
09.09.2024*/

#include <iostream> // ����/����� ������ (���������� ��������������)
#include <fstream> // ������ � ������� (������ ������ �� �����)
#include <string> // ������ �� ��������
#include <windows.h> // �����������
#include <cstdlib> // ��������� ��������� �����
#include <ctime> // ������ � �������� ��� ������������� ���������� ��������� �����

using namespace std;

class Student {
private:
    string fullName;
    string birthDate;
    string address;
    bool expelled; // ������ ��� ��������
    int grade;     // ������ �� �������

public:
    Student(string fullName, string birthDate, string address)
        : fullName(fullName), birthDate(birthDate), address(address), expelled(false), grade(0) {}

    // ����� ����� ��������
    void takeExam() {
        grade = rand() % 4 + 2; // ��������� �������� �� 2 �� 5
    }

    // ����� ���������� ������ ��������
    int getGrade() const {
        return grade;
    }

    // ����� ���������� ��������
    void expel() {
        expelled = true;
    }

    // �������� ����������
    bool isExpelled() const {
        return expelled;
    }

    // ����� ���������� � ��������
    void printInfo() const {
        cout << "���: " << fullName << endl << "���� ��������: " << birthDate << endl << "�����: " << address
            << endl << "������: " << (grade ? to_string(grade) : "�� ������") << endl << "������: " << (expelled ? "��������" : "������") << endl << endl;
    }
};

class Institute {
private:
    Student** students; // ������������ ������ ���������� �� ���������
    int numStudents;

public:
    Institute() : students(nullptr), numStudents(0) {}

    // ����� ��� �������� ������ ��������� �� �����
    void loadStudentsFromFile(const string& filename) {
        ifstream file;
        file.open(filename);

        if (!file) {
            cerr << "������: �� ������� ������� ���� " << filename << endl;
            throw runtime_error("���� �� ������ ��� �� ����� ���� ������.");
        }

        file >> numStudents;
        file.ignore(); // ���������� ������ ����� ������ ����� ����� ����� ���������

        students = new Student * [numStudents]; // ������� ������������ ������ ���������� �� ���������

        for (int i = 0; i < numStudents; ++i) {
            string fullName, birthDate, address;
            getline(file, fullName);   // ������ ���
            getline(file, birthDate);  // ������ ���� ��������
            getline(file, address);    // ������ �����

            students[i] = new Student(fullName, birthDate, address); // ������� ������ �������� � ��������� � ������
        }

        file.close();
    }

    // ����� ��� ����� ��������� ����� �������
    void addStudentsFromConsole() {
        cout << "������� ���������� ���������: ";
        cin >> numStudents;
        cin.ignore(); // ���������� ������ ����� ������ ����� ����� �����

        students = new Student * [numStudents]; // ������� ������������ ������ ���������� �� ���������

        for (int i = 0; i < numStudents; ++i) {
            cout << "������� ������ ��� �������� " << i + 1 << ":" << endl;

            string fullName, birthDate, address;
            cout << "���: ";
            getline(cin, fullName);
            cout << "���� �������� (��.��.����): ";
            getline(cin, birthDate);
            cout << "�����: ";
            getline(cin, address);

            students[i] = new Student(fullName, birthDate, address); // ������� ������ �������� � ��������� � ������
        }
    }

    // ����� ���������� ������: ����� ��������� ������ ���������
    void conductSession() {
        for (int i = 0; i < numStudents; ++i) {
            students[i]->takeExam();
        }
    }

    // ����� ��� ������� ������� �� ���������� ��������� � ������� 2
    void issueExpulsionOrder() {
        for (int i = 0; i < numStudents; ++i) {
            if (students[i]->getGrade() == 2) {
                students[i]->expel();
            }
        }
    }

    // ����� ��� ������ ���� ���������
    void printStudents() const {
        for (int i = 0; i < numStudents; ++i) {
            cout << "������� " << i + 1 << endl;
            students[i]->printInfo();
        }
    }

    // ������������ ������ ��� ���������� ������
    ~Institute() {
        for (int i = 0; i < numStudents; ++i) {
            delete students[i]; // ������� ������ ������ ��������
        }
        delete[] students; // ������� ������ ����������
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned>(time(0))); // ������������� ���������� ��������� �����

    Institute institute;

    // ����� ������� ����� ������
    int inputChoice;
    cout << "�������� ������ ����� ��������� (1 - �������, 2 - ����): ";
    cin >> inputChoice;
    cin.ignore(); // ���������� ������ ����� ������ ����� ����� �����

    try {
        if (inputChoice == 1) {
            // ���� ��������� ����� �������
            institute.addStudentsFromConsole();
        }
        else if (inputChoice == 2) {
            string filename;
            cout << "������� ��� �����(�������� list.txt): ";
            getline(cin, filename);
            // �������� ��������� �� �����
            institute.loadStudentsFromFile(filename);
        }
        else {
            cerr << "�������� �����." << endl;
            return 1;
        }
    }
    catch (const exception& e) {
        cerr << "������: " << e.what() << endl;
        return 1;
    }
    // �������� ������ (��� �������� ����� ��������)
    institute.conductSession();

    // ������ ������ �� ���������� ���������
    institute.issueExpulsionOrder();

    // ������� ������ ���� ��������� � �� �������
    cout << "���������� ������:" << endl;
    institute.printStudents();

    return 0;
}