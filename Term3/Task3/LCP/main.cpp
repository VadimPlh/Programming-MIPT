// Автор: Вадим Плахтинский.
// Описание:  Дана строка длины n. Найти количество ее различных подстрок.
// Используйте суффиксный массив.Время работы - O(n).

#include <iostream>
#include <vector>
#include <string>

std::vector<int> CreateArray( std::string str )
{
    // Шаг 0.
    int length = str.length();
    std::vector<int> count( 27, 0 );
    std::vector<int> sufArray( length ); // Наш суффиксный массив.
    std::vector<int> class1( length ); // Классы эквивалентности суфф.
    // Подсчет кол-ва суф-ов, начинающихся с определенной буквы.
    for( int i = 0; i < length; ++i ) {
        ++count[str[i] - '`'];
    }
    
    for( int i = 1; i < 27; ++i ) {
        count[i] += count[i - 1];
    }
    
    for( int i = 0; i < length; ++i ) {
        sufArray[--count[str[i] - '`']] = i;
    }
    
    class1[sufArray[0]] = 0;
    int classes = 1;
    for( int i = 1; i < length; ++i ) {
        // Если суфиксы начинаются на разные буквы, то меняем класс эквивалентности.
        if( str[sufArray[i]] != str[sufArray[i - 1]] ) {
            ++classes;
        }
        class1[sufArray[i]] = classes - 1;
    }
    
    // Шаг >=1.
    std::vector<int> classN( length ); // Классы эквивалентности для N-ых иттераций.
    std::vector<int> sufArrayN( length ); // Суф.мас для N-ых иттераций.
    for( int l = 0; ( 1 << l ) < length; ++l ) {
        
        for( int i = 0 ; i < length; ++i ) {
            sufArrayN[i] = sufArray[i] - ( 1 << l );
            if( sufArrayN[i] < 0 ) {
                sufArrayN[i] += length;
            }
        }
        
        for( int i = 0; i < 27; ++i ) {
            count[i] = 0;
        }
        
        for( int i = 0; i < length; ++i ) {
            ++count[class1[sufArrayN[i]]];
        }
        
        for( int i = 1; i < classes; ++i ) {
            count[i] += count[i - 1];
        }
        
        for( int i = length - 1; i >= 0; --i ) {
            sufArray[--count[class1[sufArrayN[i]]]] = sufArrayN[i];
        }
        
        classN[sufArray[0]] = 0;
        classes = 1;
        for( int i = 1; i < length; ++i ) {
            int mid1 = ( sufArray[i] + ( 1 << l ) ) % length;
            int mid2 = ( sufArray[i - 1] + ( 1 << l ) ) % length;
            if( class1[sufArray[i]] != class1[sufArray[i-1]] || class1[mid1] != class1[mid2])
                ++classes;
            classN[sufArray[i]] = classes - 1;
        }
        class1 = classN;
    }
    return sufArray;
}

std::vector<int> BuildLCP( std::string str, std::vector<int> sufArray )
{
    int length = str.length();
    std::vector<int> answer( length );
    std::vector<int> converse( length );
    for( int i = 0; i < length; ++i ) {
        converse[sufArray[i]] = i;
    }
    int pos = 0;
    for( int i = 0; i < length; ++i ) {
        if( pos > 0 ) {
            --pos;
        }
        if( converse[i] == length - 1 ) {
            answer[length - 1] = -1;
            pos = 0;
        } else {
            int next = sufArray[converse[i] + 1];
            while( std::max( i + pos, next + pos ) < length && str[ i + pos] == str[next + pos] ) {
                ++pos;
            }
            answer[converse[i]] = pos;
        }
    }
    return answer;
}

int main() {
    std::string str;
    std::cin >> str;
    // Добавляем символ, который меньше всех.
    str += '`';
    std::vector<int> sufArray = CreateArray( str );
    std::vector<int> LCP = BuildLCP( str, sufArray );
    int sum = 0;
    for( int i = 0; i < str.length(); ++i ) {
        if( i != 0 ) {
            sum += str.length() - sufArray[i] - 1;
        }
        if( i != str.length() - 1 ) {
            sum -= LCP[i];
        }
    }
    std::cout << sum;
    return 0;
}