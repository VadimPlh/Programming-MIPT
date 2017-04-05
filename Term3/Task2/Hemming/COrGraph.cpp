#include "COrGraph.h"

COrGraph::COrGraph( std::string str_, std::string sample_ ):
    str( str_ ), sample( sample_ )
{
    int vertexCount1 = FindVertexCount( str_ );
    int vertexCount2 = FindVertexCount( sample_ );
    vertexCountSample = vertexCount2;
    vertexCountStr = vertexCount1;
    vertexCount = vertexCount1 + vertexCount2 + 2;
    s = 0;
    t = vertexCount - 1;
    distanse.reserve(vertexCount);
    ptr.reserve(vertexCount);
    graphIndex.reserve(vertexCount);
    for( int j = 0; j < vertexCount; ++j ) {
        graphIndex[j].reserve(vertexCount);
    }
    ptr.clear();
    distanse.clear();
    graph.clear();
    for( long long i = 0; i < vertexCount; ++i ) {
        graphIndex[i].clear();
    }
}

// Добавление ребра
void COrGraph::AddEdge(long long start, long long end, long long cap)
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
    for (long long i = 0; i < vertexCount; ++i) {
        distanse[i] = INT_MAX;
    }
    distanse[s] = 0;
    que.push(s);
    while (que.empty() == false) {
        long long vertex = que.front();
        que.pop();
        for (long long i = 0; i < graphIndex[vertex].size(); ++i) {
            long long idEdge = graphIndex[vertex][i];
            long long end_vertex = graph[idEdge].end;
            if ( distanse[end_vertex] > distanse[vertex] + 1 && graph[idEdge].flow < graph[idEdge].cap ) {
                que.push(end_vertex);
                distanse[end_vertex] = distanse[vertex] + 1;
            }
        }
    }
    return distanse[t] != INT_MAX;
}

// Вычесление остаточной сети.
long long COrGraph::DFS(long long vertex, long long flow)
{
    if (flow == 0) {
        return 0;
    }
    if (vertex == t) {
        return flow;
    }
    while ( ptr[vertex] < graphIndex[vertex].size() ) {
        long long i = graphIndex[vertex][ptr[vertex]];
        long long end = graph[i].end;
        if (distanse[end] != distanse[vertex] + 1) {
            // Увеличиваем указатель.
            ++ptr[vertex];
            continue;
        }
        // Либо насыщаем.
        long long pushed = DFS(end, std::min(flow, graph[i].cap - graph[i].flow));
        if (pushed > 0) {
            graph[i].flow += pushed;
            // Обратное ребро.
            graph[i^1].flow -= pushed;
            return pushed;
        }
        ++ptr[vertex];
    }
    return 0;
}

int COrGraph::DinicAlgo()
{
    long long flow = 0;
    while (BFS() == true) {
        for (long long i = 0; i < vertexCount; ++i) {
            ptr[i] = 0;
        }
        while (long long pushed = DFS (s, INT_MAX)) {
            flow += pushed;
        }
    }
    return flow;
}

int COrGraph::FindVertexCount( std::string str ){
    int count = 0;
    for( int i = 0; i < str.size(); ++i ) {
        if( str[i] == '?' ) {
            ++count;
        }
    }
    return count;
}

int COrGraph::MakeEdge( std::string str, std::string sample, int vertexCountSample )
{
    int diff = 0;
    int numberSample; // Символ вопроса в первой строке.
    std::vector<int> array(str.size());
    int position = vertexCountSample + 1;
    for( int j = 0; j < str.size(); ++j ) {
        if( str[j] == '?' ) {
            array[j] = position++;
        }
    }
    for( int i = 0; i <= str.size() - sample.size(); ++i ) {
        numberSample = 1;
        for( int j = 0; j < sample.size(); ++j ) {
            if( sample[j] == '?' ) {
                if( str[i + j] == '1' ) {
                    AddEdge( numberSample++, vertexCount - 1, 1 );
                }
                if( str[i + j] == '0' ) {
                    AddEdge( 0, numberSample++, 1 );
                }
                if( str[i + j] == '?' ) {
                    AddEdge( numberSample, array[i + j], 1 );
                    AddEdge( array[i + j], numberSample++ , 1);
                }
            }

            if( sample[j] == '1' ) {
                if( str[i + j] == '0' ) {
                    ++diff;
                }
                if( str[i + j] == '?' ) {
                    AddEdge( array[i + j], vertexCount - 1, 1 );
                }
            }

            if( sample[j] == '0' ) {
                if( str[i + j] == '1' ) {
                    ++diff;
                }
                if( str[i + j] == '?' ) {
                    AddEdge( 0, array[i + j], 1 );
                }
            }
        }
    }
    return diff;
}

void COrGraph::NormalDFS( int vertex, std::vector<std::vector<int>>& graph_, std::vector<char>& used ) {
    used[vertex] = '0';
    for( int i = 0; i < vertexCount; ++i ) {
        if( used[i] == '1' && graph_[vertex][i] >= 0 ) {
            NormalDFS( i, graph_, used );
        }
    }
}

void COrGraph::Distanse()
{
    std::vector<std::vector<int>> tmpGraph( vertexCount, std::vector<int>(vertexCount) );
    for( int i = 0; i < vertexCount; ++i ) {
        for( int j = 0; j < vertexCount; ++j ) {
            tmpGraph[i][j] = INT_MIN;
        }
    }
    int maxFlow = DinicAlgo();
    int diff = MakeEdge( str, sample, vertexCountSample );
    std::cout << maxFlow + diff << std::endl;
    for( auto i = graph.begin(); i != graph.end(); ++i ) {
        tmpGraph[i->start][i->end] = i->cap - i->flow;
    }
    std::vector<char> used( vertexCount, '1' );
    NormalDFS( 0, tmpGraph, used );
    std::string sampleNew = "";
    std::string strNew = "";
    int index = 1 + sample.size();
    for( int i = 0; i < str.size(); ++i ) {
        if( str[i] == '?') {
            strNew += used[index++];
        } else {
            strNew += str[i];
        }
    }
    index = 1;
    for( int i = 0; i < sample.size(); ++i ) {
        if( sample[i] == '?') {
            sampleNew += used[index++];
        } else {
            sampleNew += sample[i];
        }
    }
    std::cout << strNew << std::endl << sampleNew << std::endl;
}