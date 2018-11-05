#include <iostream>
#include <memory>

#include "test.h"
#include "app.h"

using namespace std;


int main()
{
    cout << "Program starting." << endl;
    std::cout << "C++ version: " << __cplusplus << "\n\n";

    App l_app;
    l_app.start();

    return 0;
}
