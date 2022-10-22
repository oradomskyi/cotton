#ifndef TESTS_WORKER_H
#define TESTS_WORKER_H

#include <iostream>

#include "../../worker/include/methods/allmethods.h"

using std::string;
using std::cout;
using std::endl;

void test_check_Proxy_security();
void test_check_Target_security();
void test_memory_create_destroy();
void test_init_worker();
void test_create_worker();

#endif
