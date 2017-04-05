#include <iostream>
#include <climits>
#include <map>
#include <vector>
#include <set>
#include <ctime>
#include <cmath>

// Этот класс будет описывать наш граф.
class COrGraph {
public:

    COrGraph( long long vertexCount_, std::vector<std::pair<double, double>>& points );

    // Алгоритм поиска MST.
    void BoruvkaMST();

    // DFS.
    void DFS( int vertex, std::vector<std::vector<double>>& graph, std::vector<bool>& used );

    // Нахождение приблежения для задачи коммивояжёра.
    double TSP();

    double PerfectSolution( int n );

private:

    // Кол-во узлов в графе.
    const long long vertexCount;

    // Map из веса ребра и пары вершин, которое он соединяет.
    std::map<std::pair<long long, long long>, double> graph;

    // MST
    std::map<std::pair<long long, long long>, double> MST;

    // Ответ.
    std::vector<int> answer;
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

std::vector<std::pair<double, double>> Generation( int count );
