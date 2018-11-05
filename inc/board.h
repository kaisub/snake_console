#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <utility>

enum class ItemType {
    empty,  // walks on it
    wallH,   // snake dies on entering
    wallV,   // snake dies on entering
    brick,   // snake dies on entering
    snake,  // snake dies on entering
    food    // on enetering snake consumes (change to empty) and extends itself
};

enum class MoveDir {
    up,
    down,
    left,
    right
};

using Point = std::pair<std::size_t, std::size_t>;

class Board
{
public:
    using Row = std::vector<ItemType>;
    using SnakePart = std::pair<std::size_t, std::size_t>;
    using SnakeSeq = std::vector<SnakePart>;

    ~Board() {}
    Board(std::size_t p_width = 40, std::size_t p_height = 10);

    void setItemTypeAt(Point p_point, ItemType p_item) {
        m_rows[p_point.first][p_point.second] = p_item;
    }

    const std::vector<Row>& rows() const { return m_rows; }

    std::size_t rowsCount() const {
        return m_rows.size();
    }
    std::size_t max_x() const {
        return m_rows.size() - 2;
    }
    std::size_t max_y() const {
        return m_rows[0].size() - 2;
    }

    unsigned int points() const { return m_points; }

    void initFrame();
    void initSnakeCenter();

    bool singleSnakeStepReturnIsAlive();
    bool singleSnakeStepReturnIsAlive(MoveDir);

private:
    bool newDirChangeDir180Degree(MoveDir);
    void setNewDir(MoveDir);
    void setNewSnakeHead(SnakePart);
    bool timeToGrowSnake();
    void growSnake();

    std::vector<Row> m_rows;
    SnakeSeq m_snakeSeq = {};
    MoveDir m_currDir = {MoveDir::left};
    std::size_t m_snakeGrowStep = {0};
    unsigned int m_points = {0};
};

#endif // BOARD_H
