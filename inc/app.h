#ifndef APP_H
#define APP_H

#include <memory>

class App
{
public:
    ~App();
    App();

    void start();

private:
    class AppImpl;
    std::unique_ptr<AppImpl> m_impl;
};

#endif // ifndef APP_H

