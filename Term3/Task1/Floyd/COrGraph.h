// Автор - Вадим Плахтинский.
// Описание: Полный ориентированный взвешенный граф задан матрицей смежности. Постройте матрицу кратчайших путей между его вершинами.
// Гарантируется, что в графе нет циклов отрицательного веса.

#include <iostream>
#include <vector>
#include <fstream>
#pragma once

// Это класс будет описывать граф, в котором мы будем искать длины кратчайших путей.
class COrGraph {
public:

    COrGraph( int vertexCount, std::ifstream& in );

    // Заполение графа.
    void FillGraph( std::ifstream& in );

    // Алгоритм Флойда
    void Floyd();

private:

    // Кол-во узлов в графе.
    const int vertex;
    // Матрица смежности графа.
    std::vector<std::vector<float>> graph;
    // Матрица кратчайших путей.
    std::vector<std::vector<float>> shortWays;
};
