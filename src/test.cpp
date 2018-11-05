#include <iostream>

#include "test.h"
#include "klog.h"

using namespace std;

void printInfoNewline(const std::string& a_info, bool a_newline = true)
{
    std::cout << a_info << (a_newline ? "\n" : "");
}

// interface code

void runChecks()
{
    KLog::print_info("Reporting: KLog");
    printInfoNewline("Reporting: test");

    const string K_TestName{"TEST"};
    KLog l_log = KLog(K_TestName);
    l_log.printInfo("named log reporting");
}

