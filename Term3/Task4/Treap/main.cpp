// Автор: Вадим Плахтинский.
// Описание: Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое
// наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.

#include <iostream>
#include <vector>

class CTreap {
public:
    
    CTreap( int size_ );
    
    class CTreapNode {
    public:
        
        CTreapNode( int key_, int priority_ );
        
        // Ключ.
        int Key;
        
        // Приоритет.
        int Priority;
        
        // Левый сын.
        CTreapNode* Left;
        
        // Правый сын.
        CTreapNode* Right;
        
        int Level;
        
    };
    
    // Разрезание по ключу.
    void Split( CTreapNode* currentNode, int key, CTreapNode*& left, CTreapNode*& right );
    
    // Сляние 2-х деревьев.
    void Merge( CTreapNode*& tree, CTreapNode* left, CTreapNode* right );
    
    // Вставка.
    void Insert( CTreapNode*& tree, CTreapNode* node );
    
    // Удаление по ключу.
    void Erase( CTreapNode*& tree, int key );
    
    // Назначение уровней в дереве.
    void TakeLevel(  CTreapNode* node );
    
    // Получение максимального кол-ва узлов в слое.
    int MaxCount();
    
    // Корень.
    CTreapNode* Root;
    
    std::vector<CTreapNode> nodes;
    
private:
    
    int size;
    
    std::vector<int> levels;
};

class CBinaryTree {
public:
    
    CBinaryTree( int size_ );
    
    class CTreeNode {
    public:
        
        CTreeNode( int key_ );
        
        int Key;
        
        CTreeNode* Left;
        
        CTreeNode* Right;
        
        int Level;
    };
    
    void Insert( CTreeNode* node );
    
    void TakeLevel( CTreeNode* node );
    
    int MaxCount();
    
    CTreeNode* Root;
    
    std::vector<CTreeNode> nodes;
    
private:
    
    int size;
    
    std::vector<int> levels;
};

int main() {
    int size;
    std::cin >> size;
    CTreap treap( size );
    CBinaryTree tree( size );
    for( int i = 0; i < size; ++i ) {
        int key, priority;
        std::cin >> key >> priority;
        CTreap::CTreapNode node1( key, priority );
        treap.nodes.push_back( node1 );
        CBinaryTree::CTreeNode node2( key );
        tree.nodes.push_back( node2 );
    }
    for( int i = 0; i < size; ++i ) {
        treap.Insert( treap.Root, &treap.nodes[i] );
        tree.Insert( &tree.nodes[i]);
    }
    std::cout << treap.MaxCount() - tree.MaxCount();
    return 0;
}

CTreap::CTreap( int size_ ):
    size(size_), Root( nullptr ), levels( size, 0 )
{}

CTreap::CTreapNode::CTreapNode( int key_, int priority_ ):
    Key( key_ ), Priority( priority_ ), Left( nullptr ), Right( nullptr ), Level( 0 )
{}

void CTreap::Split( CTreapNode* currentNode, int key, CTreapNode*& left, CTreapNode*& right )
{
    if( !currentNode ) {
        left = NULL;
        right = NULL;
    } else {
        if( key < currentNode->Key ) {
            Split( currentNode->Left, key, left, currentNode->Left );
            right = currentNode;
        } else {
            Split( currentNode->Right, key, currentNode->Right, right);
            left = currentNode;
        }
    }
}

void CTreap::Merge( CTreapNode*& tree, CTreapNode* left, CTreapNode* right )
{
    if( !left || !right ) {
        tree = left ? left : right;
    } else {
        if( left->Priority > right->Priority ) {
            Merge( left->Right, left->Right, right );
            tree = left;
        } else {
            Merge( right->Left, left, right->Left );
            tree = right;
        }
    }
}

void CTreap::Insert( CTreapNode*& tree, CTreapNode* node )
{
    if( !tree ) {
        tree = node;
    } else {
        if( node->Priority > tree->Priority ) {
            Split( tree, node->Key, node->Left, node->Right );
            tree = node;
        } else {
            Insert( ( node->Key < tree->Key ? tree->Left : tree->Right ), node);
        }
    }
}

void CTreap::Erase( CTreapNode*& tree, int key )
{
    if( tree->Key == key ) {
        Merge( tree, tree->Left, tree->Right );
    } else {
        Erase( ( key < tree->Key ? tree->Left : tree->Right ), key );
    }
}

void CTreap::TakeLevel( CTreapNode* node )
{
    if( node->Left ) {
        node->Left->Level = node->Level + 1;
        ++levels[node->Level + 1];
        TakeLevel( node->Left );
    }
    if( node->Right ) {
        node->Right->Level = node->Level + 1;
        ++levels[node->Level + 1];
        TakeLevel( node->Right );
    }
}

int CTreap::MaxCount()
{
    TakeLevel( Root );
    int max = -1;
    for( auto i : levels ) {
        if( max < i ) {
            max = i;
        }
    }
    return max;
}

CBinaryTree::CBinaryTree( int size_ ):
    size(size_), Root( nullptr ), levels( size, 0 )
{}

CBinaryTree::CTreeNode::CTreeNode( int key_ ):
    Key( key_ ), Left( nullptr ), Right( nullptr ), Level( 0 )
{}

void CBinaryTree::Insert( CTreeNode* node )
{
    CTreeNode* y = NULL;
    CTreeNode* x = Root;
    while( x != nullptr ) {
        y = x;
        if( node->Key < x->Key ){
            x = x->Left;
        } else {
            x = x->Right;
        }
    }
    if( y == nullptr ){
        Root = node;
    } else {
        if( node->Key < y->Key ){
            y->Left = node;
        } else {
            y->Right = node;
        }
    }
}

void CBinaryTree::TakeLevel( CTreeNode* node )
{
    if( node->Left ) {
        node->Left->Level = node->Level + 1;
        ++levels[node->Level + 1];
        TakeLevel( node->Left );
    }
    if( node->Right ) {
        node->Right->Level = node->Level + 1;
        ++levels[node->Level + 1];
        TakeLevel( node->Right );
    }
}

int CBinaryTree::MaxCount()
{
    TakeLevel( Root );
    int max = -1;
    for( auto i : levels ) {
        if( max < i ) {
            max = i;
        }
    }
    return max;
}