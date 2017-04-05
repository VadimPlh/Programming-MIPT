// Автор: Вадим Плахтинский.
// «Пятнашки»
// За один ход разрешается передвинуть одну из костяшек, расположенных рядом с пустой ячейкой, на свободное место.
// Цель игры – для заданной начальной конфигурации игровой доски за минимальное число ходов получить выигрышную конфигурацию (пустая ячейка обозначена нулем).

#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <vector>

// Функция для A*
void AStar();

// Подсчет эвристики для текущего сотояния.
int heuristic( std::vector<short>& array );

// Проверка на разрешимость.
bool solved( std::vector<short> array );

//  Нахождение пути.
void getway( std::map<std::vector<short>, char>& visited );

// Нахождение 0 в массиве.
int find_zero( std::vector<short>& array);

// Класс для вершин графа.
class CPuzzleVertex {
public:

    CPuzzleVertex();

    CPuzzleVertex( std::vector<short> status_, char move_, short position_, int distanse_ );

    bool operator<( const CPuzzleVertex& vertex) const;

    // Статус.
    std::vector<short> status;
    // Как пришли к этому стостояния.
    char move;
    // Позиция 0.
    char position;
    // Расстояние до текущего состояния.
    int distance;
    // Дистанция + эвристика.
    int dis_heur;
};