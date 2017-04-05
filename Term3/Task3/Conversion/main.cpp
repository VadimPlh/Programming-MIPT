// Автор: Плахтинский Вадим.
// Описание: Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки ­– n.

#include <iostream>
#include <string>
#include <vector>
#include <set>

// Перевод строки в z - функцию.
std::vector<int> ZFunction( std::string str )
{
    std::vector<int> answer( str.length() );
    int left = 0;
    int right = 0;
    answer[0] = str.length();
    for( int i = 1; i < str.length(); ++i ) {
        answer[i] = std::max( 0, std::min( right - i, answer[i - left] ) );
        while( i + answer[i] < str.length() && str[answer[i]] == str[i + answer[i]] ) {
            ++answer[i];
        }
        if( i + answer[i] >= right ) {
            left = i;
            right = i + answer[i];
        }
    }
    return answer;
}

// Перевод z - функции в p - функцию.
std::vector<int> PFunction( std::vector<int> zFunction )
{
    std::vector<int> answer( zFunction.size(), 0 );
    for( int i = 1; i < answer.size(); ++i ) {
        //if( zFunction[i] == 1 || answer[i] == 0 ) {
        //  answer[i] = 1;
        //}
        if( zFunction[i] > 0 ) {
            for( int j = 0; j < zFunction[i]; ++j ) {
                // Если вышли за границы массива.
                if( j >= answer.size() ) {
                    break;
                }
                if( answer[i + j] < j + 1 ) {
                    answer[i + j] = j + 1;
                }
            }
        }
    }
    return answer;
}

// Перевод префикс функции в строку.
std::string GetString( std::vector<int> pFunction )
{
    std::string answer = "a";
    for( int i = 1; i < pFunction.size(); ++i ) {
        if( pFunction[i] == 0 && pFunction[i - 1] == 0 ) {
            answer += 'b';
        }
        if( pFunction[i] > 0 ) {
            answer += answer[pFunction[i] - 1];
        }
        if( pFunction[i] == 0 && pFunction[i - 1] != 0 ) {
            std::set<char> noCorrect;
            for( int j = pFunction[i - 1] - 1; j >= 0; --j ) {
                bool flag = true;
                for( int k = 0 ; k <= j; ++k ) {
                    if( answer[k] != answer[i - 1 - j + k] ) {
                        flag = false;
                    }
                }
                if( flag ) {
                    noCorrect.insert(answer[j + 1]);
                }
            }
            for( char l = 'b'; l <= 'z'; ++l ) {
                if( noCorrect.find(l) == noCorrect.end() ) {
                    answer += l;
                    break;
                }
            }
        }
    }
    return answer;
}

int main()
{
    std::vector<int> z;
    int i;
    while( std::cin >> i ) {
        z.push_back(i);
    }
    std::cout << GetString(PFunction(z));
    return 0;
}