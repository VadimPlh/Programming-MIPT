#include "COrGraph.h"

COrGraph::COrGraph( int vertexCount , std::ifstream& in) :
        vertex( vertexCount ), graph( vertexCount, std::vector<float>(vertexCount) ), shortWays( vertexCount, std::vector<float>(vertexCount) )
{
    FillGraph( in ); // Вызов функции заполенния графа
}

void COrGraph::FillGraph( std::ifstream& in )
{
    for( int i = 0; i < vertex; ++i ) {
        for( int j = 0; j < vertex; ++j ) {
            float tmp;
            in >> tmp;
            graph[i][j] = tmp;
            shortWays[i][j] = tmp; // Заполняем массив начальных расстояний, так как граф полный, то из всех вершин есть путь.
        }
    }
}

void COrGraph::Floyd()
{
    // Алгоритм Флойда
    for( int i = 0; i < vertex; ++i ) {
        for( int j = 0; j < vertex; ++j ) {
            for( int k = 0; k < vertex; ++k ) {
                shortWays[j][k] = std::min( shortWays[j][k], shortWays[j][i] + shortWays[i][k] );
            }
        }
    }

    std::ofstream out("floyd.out");
    for( int i = 0; i < vertex; ++i ) {
        for( int j = 0; j < vertex; ++j ) {
            out << shortWays[i][j] << ' ';
        }
        out << std::endl;
    }
    out.close();
}