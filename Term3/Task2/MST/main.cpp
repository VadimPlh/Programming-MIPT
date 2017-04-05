// Автор - Вадим Плахтинский.
// Описание: Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
// Вариант 3. С помощью алгоритма Борувки.

#include "COrGraph.h"

int main() {
    long long vertex, edge;
    std::cin >> vertex >> edge;
    COrGraph graph( vertex, edge );
    graph.BoruvkaMST();
    return 0;
}