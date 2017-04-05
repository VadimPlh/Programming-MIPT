// Автор - Вадим Плахтинский.
// Описание: Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
// Вариант 3. С помощью алгоритма Борувки.

#include <iostream>
#include <climits>
#include <map>
#include <vector>
#include <climits>
#include <set>
#pragma once

// Этот класс будет описывать наш граф.
class COrGraph {
public:

    COrGraph( long long vertexCount_, long long edgeCount_ );

    //Заполнение графа.
    void FillGraph();

    // Алгоритм поиска MST.
    void BoruvkaMST();

    // Нахождение приблежения для задачи коммивояжёра.


private:

    // Кол-во узлов в графе.
    const long long vertexCount;

    // Кол-во ребер в графе.
    const long long edgeCount;

    // Map из веса ребра и пары вершин, которое он соединяет.
    std::map<std::pair<long long, long long>, long long> graph;

    // MST
    std::map<std::pair<long long, long long>, long long> MST;
};

// Класс для непересикающихся множеств.
class DSU {
public:

    DSU( long long vertexCount );

    // Объединение множеств.
    void UnionSets( long long vertex1, long long vertex2 );

    // Нвхождение множества для какой-то вершины.
    long long FindSet( long long vertex );

    // Родители.
    std::vector<long long> parent;

    // Размер множеств.
    std::vector<long long> size;
};