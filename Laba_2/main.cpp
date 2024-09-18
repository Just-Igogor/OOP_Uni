/*ЮФУ, ИКТИБ, МОП ЭВМ
Объектно-ориентированное программирование
КТбо2-6, Смелов Игорь Александрович
Лабораторная работа 2
19.09.2024*/

#define __CRTDBG_MAP_ALLOC
#include "Sorting.h"

int main() {
    setlocale(LC_ALL, "ru");
    SortManager manager;
    manager.process();
    _CrtDumpMemoryLeaks();
    return 0;
}
