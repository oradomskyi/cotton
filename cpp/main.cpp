#include "tests/include/alltests.h"

int main()
{
	test_init_worker();
	test_memory_create_destroy();

	//test_check_Target_security();
	//test_check_Proxy_security();

	return 0;
}
