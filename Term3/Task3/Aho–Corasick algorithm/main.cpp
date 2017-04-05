// Автор: Вадим Плахтинский.
// Описание: Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”.
// Найти позиции всех вхождений шаблона в тексте длины n.

#include "CBor.hpp"

int main() {
    std::string sample, str;
    std::cin >> sample >> str;
    if( sample.length() > str.length() ) {
        return 0;
    }
    CBor bor;
    sample += '?';
    std::vector<std::string> tmp;
    std::string tmpStr = "";
    std::vector<int> pos;
    for( int i = 0; i < sample.length(); ++i ) {
        if( sample[i] == '?' && tmpStr != "" ) {
            tmp.push_back( tmpStr );
            pos.push_back( i - tmpStr.length() );
            tmpStr = "";
        } else {
            if( sample[i] != '?' ) {
                tmpStr += sample[i];
            }
        }
    }
    int number = 0;
    for( auto i : tmp ) {
        bor.AddString( i, number );
        ++number;
    }
    std::vector<int> posString( str.length(), 0 );
    bor.ProcessText( str, posString, pos );
    for( int i = 0; i < str.length() - sample.length() + 2; ++i ) {
        if( posString[i] == tmp.size() ) {
            std::cout << i << ' ';
        }
    }
    return 0;
}