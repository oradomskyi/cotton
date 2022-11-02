#ifndef TESTS_THREADMASTER_H
#define TESTS_THREADMASTER_H

#include <iostream>

#include "../../threadmaster/include/masters/threadmasters.h"

using std::string;
using std::cout;
using std::endl;

void test_threadmaster_run();
void test_threadmaster_long_run();
void test_threadmaster_long_run_create_destroy();
void test_threadmaster_init_with_floods();

#endif
