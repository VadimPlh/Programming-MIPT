#include <iostream>
#include <climits>
#include <vector>
#include <map>
#include <queue>
#include <string>

// Этот класс будет описывать наш граф.
class COrGraph {
public:
    COrGraph( std::string str_, std::string sample_ );

    // Поиск кол-ва вершин.
    int FindVertexCount( std::string str );

    //Добавление ребер.
    void AddEdge( long long start_, long long end_, long long cap_ );

    // ДФС.
    long long DFS( long long vertex, long long flow );

    // БФС.
    bool BFS();

    // Алгоритм Диница.
    int DinicAlgo();

    // Нахождение знаков вопросов.
    void Distanse();

    // Нормальный DFS.
    void NormalDFS( int vertex, std::vector<std::vector<int>>& graph, std::vector<char>& used );

    struct SSEdge {
    public:

        long long start;

        long long end;

        long long cap;

        long long flow;
    };

private:

    // Кол-во узлов в графе.
    long long vertexCount;

    // Кол-во ребер в графе.
    long long edgeCount;

    // Получение ребер.
    int MakeEdge( std::string str, std::string sample, int vertexCountSample );

    // Список смежности графа.
    std::vector<SSEdge> graph;

    std::vector<std::vector<long long>> graphIndex;

    // Сток.
    long long s;

    // Исток.
    long long t;

    // Строка.
    std::string str;

    // Шаблон.
    std::string sample;

    // Кол-во знаков в строке.
    int vertexCountStr;

    // Кол-во знаков в шаблоне.
    int vertexCountSample;

    //
    std::vector<long long> ptr;

    // Массив расстояние.
    std::vector<long long> distanse;
};
