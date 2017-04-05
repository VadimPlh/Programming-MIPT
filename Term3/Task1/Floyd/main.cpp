// Автор - Вадим Плахтинский.
// Описание: Полный ориентированный взвешенный граф задан матрицей смежности. Постройте матрицу кратчайших путей между его вершинами.
// Гарантируется, что в графе нет циклов отрицательного веса.

#include "COrGraph.h"

int main() {
    std::ifstream in("floyd.in");
    int vertexCount;
    in >> vertexCount; // Считываем кол-во вершин.
    COrGraph graph(vertexCount, in);
    in.close();

    graph.Floyd();

    return 0;
}