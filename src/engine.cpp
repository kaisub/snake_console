//http://www.cplusplus.com/forum/unices/11910/
//http://www.cplusplus.com/forum/articles/7312/#msg33734
// https://stackoverflow.com/questions/16592357/non-blocking-stdgetline-exit-if-no-input
// http://www.flipcode.com/archives/_kbhit_for_Linux.shtml

#include <iostream>
#include <limits>
#include <random>
#include <stdio_ext.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "board.h"
#include "engine.h"

using namespace std;

static mt19937 m_mt;
static uniform_int_distribution<int> uniform_dist_x;
static uniform_int_distribution<int> uniform_dist_y;

const size_t K_ADD_OBSTACLE_COUNT = 25;
const size_t K_ADD_FOOD_COUNT = 15;

enum class KeyAction {
    ActionUp, ActionDown, ActionLeft, ActionRight, ActionQuit, ActionNone
};

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= static_cast<unsigned int>(~ICANON);
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

char readKey()
{
    return static_cast<char>(getchar());
}

Point randomPoint()
{
    return Point {uniform_dist_x(m_mt), uniform_dist_y(m_mt)};
}

KeyAction keyToAction(char p_key)
{
    if (p_key == '\033') // // if the first value is esc
    {
        readKey(); // skip the [
        switch(readKey())
        {
        case 65 : return KeyAction::ActionUp;       // arrow up
        case 66 : return KeyAction::ActionDown;     // arrow down
        case 67 : return KeyAction::ActionLeft;     // arrow left
        case 68 : return KeyAction::ActionRight;    // arrow right
        }
    }
    else {
        switch(p_key)
        {
        case 'w' : return KeyAction::ActionUp;
        case 's' : return KeyAction::ActionDown;
        case 'd' : return KeyAction::ActionLeft;
        case 'a' : return KeyAction::ActionRight;

        case 'q' : return KeyAction::ActionQuit;
        default : return KeyAction::ActionNone;
        } // end switch
    }
    return KeyAction::ActionNone;
}

Engine::Engine(Board & p_board) : m_board(p_board)
{
    random_device rd;
    m_mt = mt19937(rd());
    uniform_dist_x = uniform_int_distribution<int>(1, static_cast<int>(m_board.max_x()));
    uniform_dist_y = uniform_int_distribution<int>(1, static_cast<int>(m_board.max_y()));
}

bool Engine::doStepIsAlive()
{
    if (!_kbhit()) {
        return m_board.singleSnakeStepReturnIsAlive();
    }
    else {
        auto l_action = keyToAction(readKey());
        switch (l_action)
        {
        case KeyAction::ActionUp : return m_board.singleSnakeStepReturnIsAlive(MoveDir::up);
        case KeyAction::ActionDown : return m_board.singleSnakeStepReturnIsAlive(MoveDir::down);
        case KeyAction::ActionLeft : return m_board.singleSnakeStepReturnIsAlive(MoveDir::left);
        case KeyAction::ActionRight : return m_board.singleSnakeStepReturnIsAlive(MoveDir::right);

        case KeyAction::ActionQuit : return false;
        case KeyAction::ActionNone : return true;
        }
    }
    return true;
}

void Engine::addItemIfItsTime(size_t & p_iter, const size_t p_max, ItemType p_item)
{
    ++p_iter;
    if (p_iter > p_max)
    {
        p_iter = 0;
        tryAddingItemToBoard(p_item);
    }
}

void Engine::addObstacleIfItsTime()
{
    addItemIfItsTime(m_addObstacleIter, K_ADD_OBSTACLE_COUNT, ItemType::brick);
}

void Engine::addFoodIfItsTime()
{
    addItemIfItsTime(m_addFoodIter, K_ADD_FOOD_COUNT, ItemType::food);
}

void Engine::tryAddingItemToBoard(ItemType p_item)
{
    const auto & l_rows = m_board.rows();;
    int l_attempt = 0;
    while(l_attempt < 100)
    {
        ++l_attempt;
        Point l_point = randomPoint();
        if (ItemType::empty == l_rows[l_point.first][l_point.second]) {
            m_board.setItemTypeAt(l_point, p_item);
            break;
        }
    }
}
