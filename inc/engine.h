#ifndef ENGINE_H
#define ENGINE_H

#include <stddef.h>

class Board;
enum class ItemType;

class Engine
{
public:
    ~Engine() = default;
    Engine(Board &);

    bool doStepIsAlive();
    void addObstacleIfItsTime();
    void addFoodIfItsTime();

private:
    void handleAction();
    void addItemIfItsTime(size_t & p_iter, const size_t p_max, ItemType p_item);
    void tryAddingItemToBoard(ItemType);

    Board & m_board;
    size_t m_addObstacleIter = {0};
    size_t m_addFoodIter = {0};
};

#endif // ifndef ENGINE_H
