// Автор - Вадим Плахтинский.
// Описание: приблизить задачу коммивыежора.

#include "COrGraph.h"

int main()
{
    std::cout << "Введите диапазон для n: ";
    int n1, n2;
    std::cin >> n1 >> n2;
    std::cout << "Введите кол-во тестов: ";
    int count;
    std::cin >> count;
    for( int n = n1; n < n2; ++n ) {
        double avarege = 0;
        double MSE = 0;
        for( int i = 0; i < count; ++i ) {
            std::vector<std::pair<double, double>> points = Generation( n );
            COrGraph graph( n, points );
            avarege +=  graph.TSP() / graph.PerfectSolution( n );
            MSE += ( graph.TSP() / graph.PerfectSolution( n ) - 1 ) * ( graph.TSP() / graph.PerfectSolution( n ) - 1 );
        }
        std::cout << "N = " << n << " среднее = " << avarege / count
                  << " среднее квадратичное = " << sqrt( MSE / count ) << std::endl;
    }
    return 0;
}