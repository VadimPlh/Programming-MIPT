// Автор - Вадим Плахтинский.
// Описание: Найдите величину максимального потока в заданном неориентированном графе.

#include <iostream>
#include <climits>
#include <vector>
#include <map>
#include <queue>

// Этот класс будет описывать наш граф.
class COrGraph {
public:
    
    COrGraph( long long vertexCount_, long long edgeCount_, long long s_, long long t_ );
    
    //Заполнение графа.
    void FillGraph();
    
    //Добавление ребер.
    void AddEdge( long long start_, long long end_, long long cap_ );
    
    // ДФС.
    long long DFS( long long vertex, long long flow );
    
    // БФС.
    bool BFS();
    
    //Алгоритм Диница.
    void DinicAlgo();
    
    struct SSEdge {
    public:
        
        long long start;
        
        long long end;
        
        long long cap;
        
        long long flow;
    };
    
private:
    
    // Кол-во узлов в графе.
    const long long vertexCount;
    
    // Кол-во ребер в графе.
    const long long edgeCount;
    
    // Список смежности графа.
    std::vector<SSEdge> graph;
    
    std::vector<std::vector<long long>> graphIndex;
    
    // Сток.
    long long s;
    
    // Исток.
    long long t;
    
    //
    std::vector<long long> ptr;
    
    // Массив расстояние.
    std::vector<long long> distanse;
};

int main()
{
    while( true ) {
        int vertex, s, t, edge;
        std::cin >> vertex;
        if( vertex == 0 ) {
            break;
        }
        std::cin >> s >> t >> edge;
        if( edge == 0 ) {
            std::cout << 0 << std::endl;
        } else {
            --s;
            --t;
            COrGraph graph( vertex, edge, s, t );
            graph.DinicAlgo();
        }
    }
    return 0;
}

// Добавление ребра
void COrGraph::AddEdge( long long start, long long end, long long cap )
{
    SSEdge e1 = {start, end, cap, 0};
    // Добавляем ребро в остаточную сеть.
    SSEdge e2 = {end, start, 0, 0};
    graph.push_back(e1);
    graphIndex[start].push_back(graph.size() - 1);
    graph.push_back(e2);
    graphIndex[end].push_back(graph.size() - 1);
}

// Вычисление слоистой сети.
bool COrGraph::BFS()
{
    std::queue<long long> que;
    for( long long i = 0; i < vertexCount; ++i ) {
        distanse[i] = INT_MAX;
    }
    distanse[s] = 0;
    que.push(s);
    while( que.empty() == false ) {
        long long vertex = que.front();
        que.pop();
        for( long long i = 0; i < graphIndex[vertex].size(); ++i ) {
            long long idEdge = graphIndex[vertex][i];
            long long end_vertex = graph[idEdge].end;
            if( distanse[end_vertex] > distanse[vertex] + 1 && graph[idEdge].flow < graph[idEdge].cap ) {
                que.push(end_vertex);
                distanse[end_vertex] = distanse[vertex] + 1;
            }
        }
    }
    return distanse[t] != INT_MAX;
}

// Вычесление остаточной сети.
long long COrGraph::DFS( long long vertex, long long flow )
{
    if( flow == 0 ) {
        return 0;
    }
    if( vertex == t ) {
        return flow;
    }
    while( ptr[vertex] < graphIndex[vertex].size() ) {
        long long i = graphIndex[vertex][ptr[vertex]];
        long long end = graph[i].end;
        if( distanse[end] != distanse[vertex] + 1 ) {
            // Увеличиваем указатель.
            ++ptr[vertex];
            continue;
        }
        // Либо насыщаем.
        long long pushed = DFS( end, std::min( flow, graph[i].cap - graph[i].flow ) );
        if( pushed > 0 ) {
            graph[i].flow += pushed;
            // Обратное ребро.
            graph[i^1].flow -= pushed;
            return pushed;
        }
        ++ptr[vertex];
    }
    return 0;
}

void COrGraph::DinicAlgo()
{
    long long flow = 0;
    while( BFS() == true ) {
        for( long long i = 0; i < vertexCount; ++i ) {
            ptr[i] = 0;
        }
        while( long long pushed = DFS( s, INT_MAX ) ) {
            flow += pushed;
        }
    }
    std::cout << flow << std::endl;
}

COrGraph::COrGraph( long long vertexCount_, long long edgeCount_, long long s_, long long t_ ):
    vertexCount( vertexCount_ ), edgeCount( edgeCount_ ), s( s_ ), t( t_ ),
    distanse( vertexCount_ ), ptr( vertexCount_ ),
    graphIndex( vertexCount_, std::vector<long long>( vertexCount_ ) )
{
    ptr.clear();
    distanse.clear();
    graph.clear();
    for (long long i = 0; i < vertexCount; ++i) {
        graphIndex[i].clear();
    }
    for (long long i = 0; i < edgeCount; ++i) {
        long long vert1, vert2, vol;
        std::cin >> vert1 >> vert2 >> vol;
        --vert1;
        --vert2;
        AddEdge( vert1, vert2, vol );
        AddEdge( vert2, vert1, vol );
    }
}