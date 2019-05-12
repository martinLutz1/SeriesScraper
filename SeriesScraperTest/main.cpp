#include <iostream>
#include <QApplication>
#include "TestCollector.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    const auto numberOfFailedTests = TestCollector::RunAllTests(argc, argv);
    std::cout << "Total number of failed tests: "<< numberOfFailedTests << std::endl;
    return numberOfFailedTests;
}
