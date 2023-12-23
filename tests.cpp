#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestReporterStdout.h>

#include <iostream>
#include <string>
#include <vector>

#include "err_writer.h"
#include "communicator.h"
#include "interface.h"

auto RunSuite (const char* SuiteName)
{
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
    return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                             SuiteName,
                             UnitTest::True(),
                             0);
}

struct CalcTest {
    Communicator comm;
};

struct InterfaceTest {
    Interface interface;
};

SUITE( ComLineTests ) {
    TEST_FIXTURE(InterfaceTest, Empty) {
        int test_argc = 1;
        const char* test_argv[test_argc] = {"NAME"};
        CHECK_EQUAL(false,
                    interface.get_options_from_comline(test_argc, (char**)(test_argv)));
    }
    TEST_FIXTURE(InterfaceTest, OnlyHelp) {
        int test_argc = 2;
        const char* test_argv[test_argc] = {"NAME", "-h"};
        CHECK_EQUAL(false,
                    interface.get_options_from_comline(test_argc, (char**)(test_argv)));
    }
    TEST_FIXTURE(InterfaceTest, Help) {
        int test_argc = 8;
        const char* test_argv[test_argc] = {"NAME", "-l", "logpas.txt", "-p", "33333", "-j", "error.txt", "-h"};
        CHECK_EQUAL(false,
                    interface.get_options_from_comline(test_argc, (char**)(test_argv)));
    }
    TEST_FIXTURE(InterfaceTest, UnknownOption) {
        int test_argc = 4;
        const char* test_argv[test_argc] = {"NAME", "-r", "-l", "logpas.txt"};
        CHECK_EQUAL(false,
                    interface.get_options_from_comline(test_argc, (char**)(test_argv)));
    }
}

SUITE(CalculatorTests) {
    TEST_FIXTURE(CalcTest, testZeroVec) {
        std::vector<uint64_t> test_vec{0, 0, 0, 0, 0};
        CHECK_EQUAL(0, comm.calculate(test_vec));
    }
    TEST_FIXTURE(CalcTest, testPositiveVec) {
        std::vector<uint64_t> test_vec{1651, 564, 0, 168, 5476};
        CHECK_EQUAL(1571, comm.calculate(test_vec));
    }
    TEST_FIXTURE(CalcTest, testEmptyVec) {
        std::vector<uint64_t> test_vec{};
        CHECK_EQUAL(0, comm.calculate(test_vec));
    }
    TEST_FIXTURE(CalcTest, testOverflow) {
        std::vector<uint64_t> test_vec{18446744073709551610, 10};
        CHECK(18446744073709551615 == comm.calculate(test_vec));
    }
}

int main() {
    cout << "Calculator Tests" << endl;
    RunSuite("CalculatorTests");
    cout << "Interface Tests" << endl;
    RunSuite("ComLineTests");
    return 0;
}