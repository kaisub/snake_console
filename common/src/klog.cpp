#include "klog.h"

using namespace std;

const auto K_EMPTY = std::string("");
const auto K_SPACE = std::string(" ");
const auto K_NEWLINE = std::string("\n");

// static code definition

void KLog::print_info(const std::string& a_info, bool a_newline)
{
    std::cout << a_info << (a_newline ? K_NEWLINE : K_EMPTY);
}

// main code

KLog::KLog(const string& p_name)
    : m_name(p_name)
{
}

void KLog::printInfo(const std::string& a_info, bool a_newline)
{
    std::cout << (m_name.empty() ? K_EMPTY : m_name + ": ")
              << a_info
              << (a_newline ? K_NEWLINE : K_EMPTY);
}

