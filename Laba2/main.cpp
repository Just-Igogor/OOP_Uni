#define __CRTDBG_MAP_ALLOC
#include "Sorting.h"

int main() {
    setlocale(LC_ALL, "ru");
    // Запуск процесса выбора и сортировки
    SortManager::process();

    _CrtDumpMemoryLeaks();
    return 0;
}
