#ifndef DRAWERCONSOLE_H
#define DRAWERCONSOLE_H

#include <cstddef>
#include "board.h"
#include "drawer.h"

class DrawerConsole : public Drawer
{
public:
    ~DrawerConsole() override;
    DrawerConsole(Board&);

    void draw() const override;

protected:
    void printRow(const Board::Row &, std::size_t p_rowNo) const;
    void printRow(const Board::Row &) const;
    void printItem(const ItemType) const;

    Board& m_board;
};

#endif // DRAWERCONSOLE_H
