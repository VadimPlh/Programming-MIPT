#include "COrGraph.h"

int main()
{
    std::string str; // Строка, в которой по которой мы будем двигать шаблон.
    std::string sample; // Шаблон.
    std::cin >> str >> sample;
    COrGraph graph( str, sample );
    graph.Distanse();
    return 0;
}
