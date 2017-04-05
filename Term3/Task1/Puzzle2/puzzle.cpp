#include "puzzle.h"

void AStar()
{
    // Считаем изначальную позицию и запишем ее.
    std::vector<short> array_start(16);
    short start_position;
    for( int i = 0; i < 16; ++i ) {
        std::cin >> array_start[i];
        if( array_start[i] == 0 ) {
            start_position = i;
        }
    }
    CPuzzleVertex start( array_start, 'S', start_position, 0 );

    if( solved(start.status) == false ) {
        std::cout << -1 << std::endl;
        exit(0);
    }

    std::vector<short> finish = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    if (start.status == finish) {
        std::cout << 0 << std::endl;
        exit(0);
    }

    std::map<std::vector<short>, char> visited;

    std::set<std::pair<int, CPuzzleVertex>> map_vertex; // Контейнер, в котором будем вершины, которые надо посетить.
    map_vertex.insert(std::make_pair(start.dis_heur, start));
    visited.insert(std::make_pair(start.status, start.move));
    std::map<std::vector<short>, int> distanse;
    distanse.insert(std::make_pair(array_start, 0));
    while( true ) {
        std::set<std::pair<int, CPuzzleVertex>>::iterator pair_tmp = map_vertex.begin();
        CPuzzleVertex vertex_tmp = pair_tmp->second;

        if( vertex_tmp.status == finish ) {
            visited.insert(std::make_pair(vertex_tmp.status, vertex_tmp.move));
            getway( visited );
        }

        map_vertex.erase(pair_tmp); // Удаляем из map вершину.
        visited.insert(std::make_pair(vertex_tmp.status, vertex_tmp.move));

        // Если мы можем сделать ход вправо.
        if( vertex_tmp.position % 4 == 0 || vertex_tmp.position % 4 == 1 || vertex_tmp.position % 4 == 2 ) {
            std::vector<short> tmp_status;
            tmp_status = vertex_tmp.status;
            int distanse_vertex = distanse[vertex_tmp.status] + 1;

            std::swap(tmp_status[vertex_tmp.position], tmp_status[vertex_tmp.position + 1]);
            if ( visited.find( tmp_status ) == visited.end() ||  distanse_vertex < distanse[tmp_status] ) {
                CPuzzleVertex new_vertex( tmp_status , 'R' , vertex_tmp.position + 1, vertex_tmp.distance + 1 );
                map_vertex.erase(std::make_pair( heuristic( tmp_status ) + distanse[tmp_status], new_vertex ));
                distanse[tmp_status] = distanse_vertex;
                map_vertex.insert( std::make_pair( heuristic( tmp_status ) + distanse[tmp_status], new_vertex ) );
            }

        }

        // Если ходим влево.
        if( vertex_tmp.position % 4 == 1 || vertex_tmp.position % 4 == 2 || vertex_tmp.position % 4 == 3 ) {
            std::vector<short> tmp_status;
            tmp_status = vertex_tmp.status;
            int distanse_vertex = distanse[vertex_tmp.status] + 1;

            std::swap(tmp_status[vertex_tmp.position], tmp_status[vertex_tmp.position - 1]);
            if ( visited.find( tmp_status ) == visited.end() || distanse_vertex < distanse[tmp_status] ) {
                CPuzzleVertex new_vertex( tmp_status , 'L' , vertex_tmp.position - 1, vertex_tmp.distance + 1 );
                map_vertex.erase( std::make_pair( heuristic( tmp_status ) + distanse[tmp_status], new_vertex ) );
                distanse[tmp_status] = distanse_vertex;
                map_vertex.insert( std::make_pair( heuristic( tmp_status ) + distanse[tmp_status], new_vertex ) );
            }

        }

        // Елсли ходим вниз.
        if( vertex_tmp.position / 4 == 0 || vertex_tmp.position / 4 == 1 || vertex_tmp.position / 4 == 2 ) {
            std::vector<short> tmp_status;
            tmp_status = vertex_tmp.status;
            int distanse_vertex = distanse[vertex_tmp.status] + 1;

            std::swap(tmp_status[vertex_tmp.position], tmp_status[vertex_tmp.position + 4]);
            if ( visited.find( tmp_status ) == visited.end() || distanse_vertex < distanse[tmp_status] ) {
                CPuzzleVertex new_vertex( tmp_status , 'D' , vertex_tmp.position + 4, vertex_tmp.distance + 1 );
                map_vertex.erase( std::make_pair( heuristic( tmp_status ) + distanse[tmp_status], new_vertex ) );
                distanse[tmp_status] = distanse_vertex;
                map_vertex.insert( std::make_pair( heuristic( tmp_status ) + distanse[tmp_status], new_vertex ) );
            }

        }

        // Если ходим вверх.
        if( vertex_tmp.position / 4 == 1 || vertex_tmp.position / 4 == 2 || vertex_tmp.position / 4 == 3 ) {
            std::vector<short> tmp_status;
            tmp_status = vertex_tmp.status;
            int distanse_vertex = distanse[vertex_tmp.status] + 1;

            std::swap(tmp_status[vertex_tmp.position], tmp_status[vertex_tmp.position - 4]);
            if ( visited.find( tmp_status ) == visited.end() || distanse_vertex < distanse[tmp_status] ) {
                CPuzzleVertex new_vertex( tmp_status , 'U' , vertex_tmp.position - 4, vertex_tmp.distance + 1 );
                map_vertex.erase( std::make_pair( heuristic( tmp_status ) + distanse[tmp_status], new_vertex ) );
                distanse[tmp_status] = distanse_vertex;
                map_vertex.insert( std::make_pair( heuristic( tmp_status ) + distanse[tmp_status], new_vertex ) );
            }
        }
    }
}

void getway( std::map<std::vector<short>, char>& visited ) {
    std::string answer; // Сюда пишем ответ.

    // Финишная позиция.
    std::vector<short> finish(16);
    for( int i = 0; i < 15; ++i ) {
        finish[i] = i + 1;
    }
    finish[15] = 0;

    std::map<std::vector<short>, char>::iterator iterator = visited.find( finish ); // Нашли самый последний ход.
    while( iterator->second != 'S' ) {
        std::vector<short> tmp_status(16);
        tmp_status = iterator->first;
        answer += iterator->second;

        // Если ход был вправо, то мы должны сдвинуться влево.
        if( iterator->second == 'R' ) {
            int position = find_zero(tmp_status);
            std::swap( tmp_status[position] , tmp_status[position - 1] );
        }

        // Елси ход был влево, чтобы попасть в предыдущий, то сдвигаем впарво
        if( iterator->second == 'L' ) {
            int position = find_zero(tmp_status);
            std::swap( tmp_status[position] , tmp_status[position + 1] );
        }

        // Аналогично с верхом и низом
        if( iterator->second == 'U' ) {
            int position = find_zero(tmp_status);
            std::swap( tmp_status[position] , tmp_status[position + 4] );
        }

        if( iterator->second == 'D' ) {
            int position = find_zero(tmp_status);
            std::swap( tmp_status[position] , tmp_status[position - 4] );
        }

        iterator = visited.find( tmp_status );
    }

    // Перевернкм строку с ответом
    for( int i = 0; i < answer.length() / 2; ++i ){
        std::swap( answer[i], answer[answer.length() - i - 1] );
    }

    std::cout << answer.length() << std::endl << answer << std::endl;
    exit(0);
}

int find_zero(std::vector<short>& array)
{
    for( int i = 0; i < 16; ++i ) {
        if( array[i] == 0) {
            return i;
        }
    }
    return 0;
}

bool solved( std::vector<short> array )
{
    int inversion = 0;
    for( int i = 0; i < 16; ++i ) {
        if( array[i] ) {
            for( int j = 0; j < i; ++j ) {
                if( array[j] > array[i] ) {
                    ++inversion;
                }
            }
        }
    }

    for( int k = 0; k < 16; ++k ) {
        if( array[k] == 0 ) {
            inversion += 1 + k / 4;
        }
    }
    if( inversion % 2 == 0 ) {
        return true;
    } else {
        return false;
    }
}

CPuzzleVertex::CPuzzleVertex() {}

CPuzzleVertex::CPuzzleVertex( std::vector<short> status_, char move_, short position_ , int distanse_):
        move( move_ ), status(status_), position( position_ ), distance( distanse_ ), dis_heur(distanse_ + heuristic(status_)) // Давайте из подсчета дистанции уберем расстоняие от начальной пятнашки до текущей, даст преимущесвто в скорости.
{}

int heuristic( std::vector<short>& array )
{
    int x, y, manhattan_distance = 0;
    for( int i = 0; i < 4; ++i ) {
        for( int j = 0; j < 4; ++j ) {
            if( array[i * 4 + j] != 0 ) {
                x = (array[i * 4 + j] - 1 ) / 4 - i;
                y = (array[i * 4 + j] - 1 ) % 4 - j;
                if( x > 0 ) {
                    manhattan_distance += x;
                } else {
                    manhattan_distance -= x;
                }
                if( y > 0 ) {
                    manhattan_distance += y;
                } else {
                    manhattan_distance -= y;
                }
            } else {
                x = 4 - 1 - i;
                y = 4 - 1 - j;
                manhattan_distance += x;
                manhattan_distance += y;
            }
        }
    }
    return manhattan_distance;
}

bool CPuzzleVertex::operator<( const CPuzzleVertex& vertex ) const
{
    return this->status < vertex.status;
}