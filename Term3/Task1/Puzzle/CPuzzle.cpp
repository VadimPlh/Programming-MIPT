#include "CPuzzle.h"

CPuzzleVertex::CPuzzleVertex() {}

CPuzzleVertex::CPuzzleVertex( std::string status_, char move_, int position_ ):
        status(status_), move( move_ ), position( position_ )
{}

CPuzzle::CPuzzle()
{
    std::ifstream in("puzzle.in");
    for( int i = 0; i < 9; ++i ) {
        in >> status[i];
        if( status[i] == 0 ){
            position = i;
        }
    }
    in.close();


    if ( !Solved() ) {
        std::ofstream out("puzzle.out");
        out << -1;
        out.close();
    } else {
        Resolve();
    }
}

bool CPuzzle::Solved()
{
    // Будем считать перестановки в змейке.
    int snack[9];
    for( int i = 0; i < 9; ++i ) {
        snack[i] = status[i];
    }
    // Сделаем саму змейку
    std::swap(snack[3], snack[5]);
    int zero_position;
    for( int i = 0; i < 9; ++i ) {
        if ( snack[i] == 0 ) {
            zero_position = i;
        }
    }
    // Сдвинем элементы, чтобы не считать ноль.
    for( int i = zero_position; i < 8; ++i) {
        snack[i] = snack[i + 1];
    }
    int inversion = 0; // Кол-во инверсий.
    // Посчитаем, сколько инверсий у нас произошло.
    for( int i = 0; i < 8; ++i ) {
        for( int j = i; j < 8; ++j ) {
            if( snack[i] > snack[j] ) {
                inversion++;
            }
        }
    }
    // Чтобы почтитать четность перестановки кол-во инверсий делим на 2.
    if( inversion % 2 == 0 ) {
        return false;
    } else {
        return true;
    }
}

void CPuzzle::GetWay( std::map<std::string, char>& way )
{
    std::ofstream out("puzzle.out");
    std::string answer = ""; // Сюда будем записывать ответ
    std::map<std::string, char>::iterator iterator = way.find("123456780"); // Ищем самый последний ход.
    while( iterator->second != 'S' ) {

        std::string tmp_status = iterator->first;
        answer += iterator->second;

        // Если ход был вправо, то мы должны сдвинуться влево.
        if( iterator->second == 'R' ) {
            int position = tmp_status.find('0');
            std::swap( tmp_status[position], tmp_status[position - 1] );
        }

        // Елси ход был влево, чтобы попасть в предыдущий, то сдвигаем впарво
        if( iterator->second == 'L' ) {
            int position = tmp_status.find('0');
            std::swap( tmp_status[position], tmp_status[position + 1] );
        }

        // Аналогично с верхом и низом
        if( iterator->second == 'U' ) {
            int position = tmp_status.find('0');
            std::swap( tmp_status[position], tmp_status[position + 3] );
        }

        if( iterator->second == 'D' ) {
            int position = tmp_status.find('0');
            std::swap( tmp_status[position], tmp_status[position - 3] );
        }

        iterator = way.find(tmp_status);
    }

    // Перевернкм строку с ответом
    for( int i = 0; i < answer.length() / 2; ++i ){
        std::swap( answer[i], answer[answer.length() - i - 1] );
    }

    out << answer.length() << std::endl << answer;
    out.close();
}

void CPuzzle::Resolve()
{
    std::queue<CPuzzleVertex> puzzles; // Очередь вершин на обработку.
    std::map<std::string, char> visited; // Вершины, которые мы уже обработали.

    // Магия, чтобы добавить стартовую вершину в очередь
    std::string status_str;
    for( int i = 0; i < 9; ++i ) {
        status_str += std::to_string(status[i]);
    }
    CPuzzleVertex start( status_str, 'S', position);
    puzzles.push(start);
    visited.insert(std::make_pair(status_str, 'S'));

    CPuzzleVertex tmp; // В эту переменную будем считывать вершину из очереди

    bool finish = false; // Флаг, чтобы мы закончили искать решение

    // Провери, что нам дали сразу итоговое решение
    if( status_str == "123456780" ) {
        std::ofstream out("puzzle.out");
        out << -1;
        out.close();
    }

    while( !finish ) {

        // Вытаскиваем первый элемент в очереди.
        tmp = puzzles.front();
        puzzles.pop();

        // Проверка на последний ход.
        if( tmp.status == "123456780" ) {
            GetWay( visited );
            break;
        }

        // Смотрим по каким направлениям можем ходить.
        // Если мы можем сделать ход вправо.
        if( tmp.position == 0 || tmp.position == 3 || tmp.position == 6 || tmp.position == 1 || tmp.position == 4 || tmp.position == 7 ) {
            // Строка для нового статуса.
            std::string status_tmp;
            status_tmp = tmp.status;
            std::swap(status_tmp[tmp.position], status_tmp[tmp.position + 1]); // Двигаем 0 на новое место
            if( visited.find(status_tmp) == visited.end() ) {
                CPuzzleVertex vertex( status_tmp, 'R' , tmp.position + 1 );
                puzzles.push( vertex );
                visited.insert(std::make_pair(vertex.status, 'R'));
            }
        }

        // Можем сходить влево.
        if( tmp.position == 2 || tmp.position == 5 || tmp.position == 8 || tmp.position == 1 || tmp.position == 4 || tmp.position == 7 ) {
            // Строка для нового статуса.
            std::string status_tmp;
            status_tmp = tmp.status;
            std::swap(status_tmp[tmp.position], status_tmp[tmp.position - 1]); // Двигаем 0 на новое место.
            if( visited.find(status_tmp) == visited.end() ) {
                CPuzzleVertex vertex( status_tmp, 'L' , tmp.position - 1 );
                puzzles.push( vertex );
                visited.insert(std::make_pair(vertex.status, 'L'));
            }
        }

        //Можем сходить вверх.
        if( tmp.position == 6 || tmp.position == 7 || tmp.position == 8 || tmp.position == 3 || tmp.position == 4 || tmp.position == 5 ) {
            // Строка для нового статуса.
            std::string status_tmp;
            status_tmp = tmp.status;
            std::swap(status_tmp[tmp.position], status_tmp[tmp.position - 3]); // Двигаем 0 на новое место
            if( visited.find(status_tmp) == visited.end() ) {
                CPuzzleVertex vertex( status_tmp, 'U' , tmp.position - 3 );
                puzzles.push( vertex );
                visited.insert(std::make_pair(vertex.status, 'U'));
            }
        }

        // Можем сходить вниз.
        if( tmp.position == 0 || tmp.position == 1 || tmp.position == 2 || tmp.position == 3 || tmp.position == 4 || tmp.position == 5 ) {
            // Строка для нового статуса.
            std::string status_tmp;
            status_tmp = tmp.status;
            std::swap(status_tmp[tmp.position], status_tmp[tmp.position + 3]); // Двигаем 0 на новое место
            if( visited.find(status_tmp) == visited.end() ) {
                CPuzzleVertex vertex( status_tmp, 'D' , tmp.position + 3 );
                puzzles.push( vertex );
                visited.insert(std::make_pair(vertex.status, 'D'));
            }
        }
    }
}