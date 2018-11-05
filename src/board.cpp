#include <iostream>
#include "board.h"

enum class SnakeHitAction
{
    SnakeAlive,
    SnakeDead,
    SnakeGrows
};

SnakeHitAction newHeadPositionSnakeIs(ItemType p_itemType)
{
    switch(p_itemType)
    {
    case ItemType::empty : return SnakeHitAction::SnakeAlive;
    case ItemType::wallH : return SnakeHitAction::SnakeDead;
    case ItemType::wallV : return SnakeHitAction::SnakeDead;
    case ItemType::brick : return SnakeHitAction::SnakeDead;
    case ItemType::snake : return SnakeHitAction::SnakeDead;
    case ItemType::food : return SnakeHitAction::SnakeGrows;
    }
    return SnakeHitAction::SnakeAlive;//KAI
}

Board::SnakePart makeNewSnakePart(MoveDir p_dir, const Board::SnakePart& p_oldHead)
{
    switch(p_dir)
    {
    case MoveDir::up : {
        return std::make_pair(p_oldHead.first - 1, p_oldHead.second);
    }
    case MoveDir::down : {
        return std::make_pair(p_oldHead.first + 1, p_oldHead.second);
    }
    case MoveDir::left : {
        return std::make_pair(p_oldHead.first, p_oldHead.second + 1);
    }
    case MoveDir::right : {
        return std::make_pair(p_oldHead.first, p_oldHead.second - 1);
    }
    } // end switch
}

Board::Board(size_t p_width, size_t p_height)
{
    std::cout << "Board constructing" << std::endl;

    m_rows.resize(p_height);
    for (auto& row : m_rows)
    {
        row.resize(p_width, ItemType::empty);
    }
    initFrame();
    initSnakeCenter();
}

void Board::initFrame()
{
    // up wall
    auto l_row = m_rows.begin();
    std::fill((*l_row).begin(), (*l_row).end(), ItemType::wallH);

    // bottom wall
    l_row = (m_rows.end() - 1);
    std::fill((*l_row).begin(), (*l_row).end(), ItemType::wallH);

    // side walls
    for (l_row = m_rows.begin() + 1; l_row != m_rows.end() - 1; l_row++)
    {
        *(*l_row).begin() = ItemType::wallV;
        *((*l_row).end() - 1) = ItemType::wallV;
    }
}

void Board::initSnakeCenter()
{
    m_snakeSeq.clear();
    const auto l_pair = std::make_pair(m_rows.size() / 2, m_rows[0].size() / 2);
    m_snakeSeq.emplace_back(l_pair);
    m_rows[l_pair.first][l_pair.second] = ItemType::snake;
}

bool Board::singleSnakeStepReturnIsAlive()
{
    return singleSnakeStepReturnIsAlive(m_currDir);
}

bool Board::singleSnakeStepReturnIsAlive(MoveDir p_dir)
{
    setNewDir(p_dir);

    const auto & l_oldHead = *(m_snakeSeq.end() - 1);
    SnakePart l_newHead = makeNewSnakePart(m_currDir, l_oldHead);
    switch(newHeadPositionSnakeIs(m_rows[l_newHead.first][l_newHead.second]))
    {
    case SnakeHitAction::SnakeAlive : {
        if (timeToGrowSnake()) {
            growSnake();
        }
        else {
            m_rows[m_snakeSeq[0].first][m_snakeSeq[0].second] = ItemType::empty;
            m_snakeSeq.erase(m_snakeSeq.begin());
        }
        setNewSnakeHead(l_newHead);
        return true;
    }
    case SnakeHitAction::SnakeGrows : {
        growSnake();
        setNewSnakeHead(l_newHead);
        return true;
    }
    case SnakeHitAction::SnakeDead : return false;
    }
}

bool Board::newDirChangeDir180Degree(MoveDir p_dir)
{
    const auto & l_head = *(m_snakeSeq.end() - 1);
    const auto & l_neck = *(m_snakeSeq.end() - 2);
    switch(p_dir)
    {
    case MoveDir::up :
        if (l_neck.first == l_head.first - 1)
            return true;
        break;
    case MoveDir::down :
        if (l_neck.first == l_head.first + 1)
            return true;
        break;
    case MoveDir::left :
        if (l_neck.second == l_head.second + 1)
            return true;
        break;
    case MoveDir::right :
        if (l_neck.second == l_head.second - 1)
            return true;
        break;
    }
    return false;
}

void Board::setNewDir(MoveDir p_dir)
{
    if (m_snakeSeq.size() > 1 && newDirChangeDir180Degree(p_dir))
    {
        return;
    }
    m_currDir = p_dir;
}

void Board::setNewSnakeHead(SnakePart p_newHead)
{
    m_rows[p_newHead.first][p_newHead.second] = ItemType::snake;
    m_snakeSeq.emplace_back(p_newHead);
    ++m_points;
}

bool Board::timeToGrowSnake()
{
    const size_t K_SNAKE_GROW_COUNTER = 20;
    ++m_snakeGrowStep;
    if (m_snakeGrowStep >= K_SNAKE_GROW_COUNTER)
    {
        return true;
    }
    return false;
}

void Board::growSnake()
{
    m_snakeGrowStep = 0;
    m_points += 10;
}
