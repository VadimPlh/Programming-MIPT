#include "COrGraph.h"

COrGraph::COrGraph( long long vertexCount_, std::vector<std::pair<double, double>>& points ):
        vertexCount( vertexCount_ )
{
    for( long long i = 0; i < vertexCount; ++i ) {
        for( int j = i + 1; j < vertexCount; ++j ) {
            double x = points[i].first - points[j].first;
            double y = points[i].second - points[j].second;
            double weight = sqrt( x * x + y * y );
            graph.insert( std::make_pair( std::make_pair( i , j ) , weight ) );
        }
    }
}

void COrGraph::BoruvkaMST()
{
    MST.clear();
    DSU com( vertexCount ); // Для каждого ребра будем хранить лидера КС.
    // В самом начале каждая вершина отделая КС.
    for( long long i = 0; i < vertexCount; ++i ) {
        com.parent[i] = i;
        com.size[i] = 1;
    }
    long long size = 0; // Размер MST.
    std::vector<std::pair<std::pair<long long, long long>, double>> component_edge( vertexCount ); // Для каждой компоненты храним вес минимального ребра из нее.

    while( size < vertexCount - 1 ) {
        for( long long i = 0; i < vertexCount; ++i ) {
            component_edge[i].second = INT_MAX;
        }
        for( auto i = graph.begin(); i != graph.end(); ++i ) {
            long long start = i->first.first;
            long long end = i->first.second;
            double weight = i->second;
            // Если вершины лежат в разных компонентах связности.
            if( com.FindSet( start ) != com.FindSet( end ) ) {
                // Ищем минимальное ребро из компоненты связности.
                if( component_edge[com.FindSet( start )].second > weight ) {
                    component_edge[com.FindSet( start )].second = weight;
                    component_edge[com.FindSet( start )].first.first = start;
                    component_edge[com.FindSet( start )].first.second = end;
                }
                // Так как граф ориентированный, то делаем 2 проверки.
                if( component_edge[com.FindSet( end )].second > weight ) {
                    component_edge[com.FindSet( end )].second = weight;
                    component_edge[com.FindSet( end )].first.first = end;
                    component_edge[com.FindSet( end )].first.second = start;
                }
            }
        }
        // Сольем компоненты в одну, где обновились веса.
        for( long long i = 0; i < vertexCount; ++i ) {
            // Если для нашей КС обновился вес минимального ребра.
            if( component_edge[com.FindSet( i )].second < INT_MAX ) {
                long long vertex1 = component_edge[com.FindSet( i )].first.first;
                long long vertex2 = component_edge[com.FindSet( i )].first.second;
                double weight = component_edge[com.FindSet( i )].second;
                MST.insert( std::make_pair( std::make_pair( vertex1, vertex2 ), weight ) );
                com.UnionSets( component_edge[com.FindSet( i )].first.first, component_edge[com.FindSet( i )].first.second );
                component_edge[com.FindSet( i )].second = INT_MAX;
                ++size;
            }
        }
    }
}

void COrGraph::DFS( int vertex, std::vector<std::vector<double>>& graph, std::vector<bool>& used )
{
    answer.push_back( vertex );
    for( auto i = graph[vertex].begin(); i != graph[vertex].end(); ++i ) {
        if( !used[*i] && graph[vertex].size() != 0 ) {
            used[*i] = true;
            DFS( *i, graph, used );
        }
    }
}

double COrGraph::TSP()
{
    this->BoruvkaMST();
    std::vector<std::vector<double>> graphMST( vertexCount );
    // Преобразуем граф к нужному нам виду.
    for( auto i = MST.begin(); i != MST.end(); ++i ) {
        int vertex1 = i->first.first;
        int vertex2 = i->first.second;
        graphMST[vertex1].push_back( vertex2 );
        graphMST[vertex2].push_back( vertex1 );
    }
    // Сделаем DFS по получившимуся графу.
    std::vector<bool> used( vertexCount, false );
    DFS( MST.begin()->first.first, graphMST, used );
    std::set<int> tmp;
    std::vector<int> cycle;
    for( auto i = answer.begin(); i != answer.end(); ++i ) {
        if( tmp.find( *i ) == tmp.end()) {
            cycle.push_back( *i );
            tmp.insert( *i );
        }
    }
    // Пройдемся по получившемуся DFS и запишим неповторяющиеся ребра.
    double lengthCycle = 0;
    int vertex1;
    int vertex2;
    for( int i = 0; i < cycle.size() - 1; ++i ) {
        vertex1 = std::min( cycle[i], cycle[i + 1] );
        vertex2 = std::max( cycle[i], cycle[i + 1] );
        lengthCycle += graph[std::make_pair( vertex1, vertex2 )];
    }
    vertex1 = std::min( cycle[cycle.size() - 1], cycle[0] );
    vertex2 = std::max( cycle[cycle.size() - 1], cycle[0] );
    lengthCycle += graph[std::make_pair( vertex1, vertex2 )];
    return lengthCycle;
}

bool Next( std::vector<int>& transposition, int n )
{
    int i, j, k, r;
    // Самое правое место, где transposition[i] < transposition[i+1]
    for( i = n - 2; i >= 0 && transposition[i] > transposition[i + 1]; --i );
    if( i < 0 ) {
        return false;
    }
    // transposition[j] - наименьший элемент справа от transposition[i] и больший его.
    for( j = n - 1; transposition[i] > transposition[j]; --j);
    std::swap( transposition[i], transposition[j] );
    // То, что находится за i-ой позицией нужно перевернуть.
    for( k = i + 1, r = n - 1; r > k; ++k, --r ) {
        std::swap( transposition[k], transposition[r] );
    }
    return true;
}

// Идеальное решение.
double COrGraph::PerfectSolution( int n )
{
    std::vector<std::vector<double>> graph_( vertexCount, std::vector<double>( vertexCount, 0 ) );
    for(auto i = graph.begin(); i != graph.end(); ++i ) {
        long long vertex1 = i->first.first;
        long long vertex2 = i->first.second;
        double weight = i->second;
        graph_[vertex1][vertex2] = weight;
        graph_[vertex2][vertex1] = weight;
    }
    double answer = INT_MAX;
    std::vector<int> transposition(n);
    for( int i = 0; i < n; ++i ) {
        transposition[i] = i;
    }
    while( Next( transposition, n ) ) {
        double tmp = 0;
        for( int i = 0; i < n - 1; ++i ){
            tmp += graph_[transposition[i]][transposition[i + 1]];
        }
        tmp += graph_[n - 1][0];
        if( tmp < answer ) {
            answer = tmp;
        }
    }
    return answer;
}

DSU::DSU( long long vertexCount )
        : parent( vertexCount ), size( vertexCount )
{}

void DSU::UnionSets( long long vertex1, long long vertex2 ) {
    long long leader1 = FindSet( vertex1 );
    long long leader2 = FindSet( vertex2 );
    if( leader1 != leader2 ) {
        // Смторим размер какого множества больше, то и будет родительским и перекидываем родителя для меньшего мн-ва.
        if( size[leader1] > size[leader2] ) {
            parent[leader2] = leader1;
            size[leader1] += size[leader2];
        }
        else {
            parent[leader1] = leader2;
            size[leader2] += size[leader1];
        }
    }
}

long long DSU::FindSet( long long vertex )

{
    long long leader = vertex;
    // Поднимаемся вверх, пока не найдем вершину, которая сама себе родитель.
    while( leader != parent[leader] ) {
        leader = parent[leader];
    }
    return leader;
}

std::vector<std::pair<double, double>> Generation( int count )
{
    std::vector<std::pair<double, double>> points;
    std::srand(unsigned(std::time(0)));
    double x;
    double y;
    for( int i = 0; i < count; ++i ) {
        float s = 0;
        while( s > 1 || s == 0 ) {
            x = -1.0 + static_cast<double>( rand() ) / ( static_cast<double>( RAND_MAX / 2.0 ) );
            y = -1.0 + static_cast<double>( rand() ) / ( static_cast<double>( RAND_MAX / 2.0 ) );
            s = x * x + y * y;
        }
        double x_ = x * sqrt( -2 * log(s) / s );
        double y_ = y * sqrt( -2 * log(s) / s );
        points.push_back( std::make_pair( x_, y_ ) );
    }
    return points;
}