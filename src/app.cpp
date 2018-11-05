#include <iostream>
#include <chrono>
#include <thread>
#include "app.h"
#include "board.h"
#include "drawerConsole.h"
#include "engine.h"
#include "klog.h"

using namespace std;

class App::AppImpl
{
public:
    ~AppImpl() {}
    AppImpl();

    void start();

private:
    Board m_board = {120, 45};
    DrawerConsole m_drawer;
    Engine m_engine;
    bool m_gameOn = false;
};

App::AppImpl::AppImpl()
    : m_drawer(m_board)
    , m_engine(m_board)
{
    LOG_FUNCTION(__PRETTY_FUNCTION__);
}

App::~App()
{
    cout << "App BYE" << endl;
}

App::App() : m_impl(new AppImpl())
{
    cout << "Creating App" << endl;
}

void App::start()
{
    m_impl->start();
}

void App::AppImpl::start()
{
    m_gameOn = true;
    while (m_gameOn)
    {
        auto l_doNextStep = m_engine.doStepIsAlive();
        m_drawer.draw();
        if (!l_doNextStep) {
            break;
        }
        m_engine.addObstacleIfItsTime();
        m_engine.addFoodIfItsTime();
        const int64_t l_timer = 100;
        std::this_thread::sleep_for(std::chrono::milliseconds(l_timer));
    }
}
