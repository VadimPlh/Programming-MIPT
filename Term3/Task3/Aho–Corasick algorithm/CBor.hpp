// Автор: Вадим Плахтинскийю
// Описание: Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”.
// Найти позиции всех вхождений шаблона в тексте длины n.

#ifndef CBor_hpp
#define CBor_hpp

#include <iostream>
#include <vector>
#include <string>

// Класс для вершин бора.
class CBor {
public:
    
    class CNode {
    public:
        CNode();
        
        // Массив сыновей.
        std::vector<int> Son;
        
        // Массив переходов.
        std::vector<int> Go;
        
        // Вершина родитель.
        int Parent;
        
        // Суфиксная ссылка.
        int SuffLink;
        
        // Сжатая суфиксная ссылка.
        int Up;
        
        // Символ, ведущий к родителю.
        char CharToParent;
        
        // Флаг, является ли вершина терминалом.
        bool IsTerminal;
        
        // Номера строк, для которых вершина терминал.
        std::vector<int> StrTerminal;
    };
    
    CBor();
    
    // Функция для вычесления суффиксной ссылки.
    int GetSuffLink( int number );
    
    // Функция для вычесления перехода.
    int GetLink( int number, char symbol );
    
    // Функция для вычесления сжатой суффиксной ссылки.
    int GetUp( int number );
    
    // Добавление строки в бор.
    void AddString( std::string str, int number );
    
    // Проверка находится ли шаблон в тексте.
    void Check( int number, int pos, std::vector<int>& posString, std::vector<int>& posArray );
    
    // Поиск встречается ли строка или нет.
    void ProcessText( std::string str, std::vector<int>& posString, std::vector<int>& pos );
    
    // Вектор вершин.
    std::vector<CNode> nodes;
    
private:
    // Длины шаблонов.
    std::vector<int> length;
};

#endif /* CBor_hpp */
