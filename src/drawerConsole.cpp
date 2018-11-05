#include <iostream>
#include "drawerConsole.h"
#include "klog.h"

constexpr auto getSign = [](const ItemType p_item) {
    switch (p_item)
    {
    case ItemType::empty : return ' ';
    case ItemType::wallH : return '-';
    case ItemType::wallV : return '|';
    case ItemType::brick : return '#';
    case ItemType::snake : return '*';
    case ItemType::food : return 'o';
    };
};

DrawerConsole::~DrawerConsole()
{
    std::cout << "DrawerConsole BYE" << std::endl;
}

DrawerConsole::DrawerConsole(Board& p_board)
    : m_board(p_board)
{
    std::cout << "DrawerConsole constructing" << std::endl;
}

void DrawerConsole::draw() const
{
    system("clear");
    size_t i = 0;
    for(auto& l_row : m_board.rows())
    {
        printRow(l_row, i++);
        std::cout << std::endl;
    }
}

void DrawerConsole::printRow(const Board::Row& p_rowItems, size_t p_rowNo) const
{
    printRow(p_rowItems);
    switch(p_rowNo)
    {
    case 1 :
        std::cout << "  Points: " << m_board.points();
    }
}

void DrawerConsole::printRow(const Board::Row& p_rowItems) const
{
    for (auto& l_item : p_rowItems)
    {
        printItem(l_item);
    }
}

void DrawerConsole::printItem(const ItemType p_item) const
{
    std::cout << getSign(p_item);
}
