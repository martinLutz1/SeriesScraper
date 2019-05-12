/**
 * BASED ON http://qtcreator.blogspot.de/2009/10/running-multiple-unit-tests.html
 */
#ifndef TESTCOLLECTOR_H
#define TESTCOLLECTOR_H

#include <QtTest>
#include <memory>
#include <map>
#include <string>

namespace TestCollector
{
    using TestList = std::map<std::string, std::shared_ptr<QObject>>;
    inline TestList& GetTestList()
    {
        static TestList list;
        return list;
    }

    inline int RunAllTests(int argc, char **argv)
    {
        int result = 0;
        for (const auto& test: GetTestList())
        {
            result += QTest::qExec(test.second.get(), argc, argv);
        }
        return result;
    }

    template <class T>
    class UnitTestClass
    {
    public:
        UnitTestClass(const std::string& pTestName)
        {
            auto& testList = TestCollector::GetTestList();
            if (0 == testList.count(pTestName))
            {
                testList.insert(std::make_pair(pTestName, std::make_shared<T>()));
            }
        }
    };
}

#define ADD_TEST(className) \
    static TestCollector::UnitTestClass<className> test(#className);

#endif // TESTCOLLECTOR_H
