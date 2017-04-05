#include "COrGraph.h"

COrGraph::COrGraph( long long vertexCount_, long long edgeCount_ ):
        vertexCount( vertexCount_ ), edgeCount( edgeCount_ )
{
    FillGraph();
}

void COrGraph::FillGraph()
{
    for( long long i = 0; i < edgeCount; ++i ) {
        long long start, end, weight;
        std::cin >> start >> end >> weight;
        // Так-как граф не ориентированный, то добавим ребра в обоих направлениях.
        graph.insert( std::make_pair( std::make_pair( start - 1, end - 1 ), weight ) );
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
    std::vector<std::pair<std::pair<long long, long long>, long long>> component_edge( vertexCount ); // Для каждой компоненты храним вес минимального ребра из нее.

    while( size < vertexCount - 1 ) {
        for( long long i = 0; i < vertexCount; ++i ) {
            component_edge[i].second = INT_MAX;
        }
        for( auto i = graph.begin(); i != graph.end(); ++i ) {
            long long start = i->first.first;
            long long end = i->first.second;
            long long weight = i->second;
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
                long long weight = component_edge[com.FindSet( i )].second;
                MST.insert( std::make_pair( std::make_pair( vertex1, vertex2 ), weight ) );
                com.UnionSets( component_edge[com.FindSet( i )].first.first, component_edge[com.FindSet( i )].first.second );
                component_edge[com.FindSet( i )].second = INT_MAX;
                ++size;
            }
        }
    }
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

long long DSU::FindSet( long long vertex ) {
    long long leader = vertex;
    // Поднимаемся вверх, пока не найдем вершину, которая сама себе родитель.
    while( leader != parent[leader] ) {
        leader = parent[leader];
    }
    return leader;
}