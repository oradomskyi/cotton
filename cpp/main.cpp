#include "tests/include/alltests.h"

int main()
{
	//test_init_worker();
	//test_memory_create_destroy();

	//test_check_Target_security();
	//test_check_Proxy_security();

    //test_threadmaster_init_with_floods();
    //test_threadmaster_run();
    //test_threadmaster_long_run_create_destroy();
    //test_threadmaster_long_run();
    //test_parallelposix_startstop();
	
	test_parallelboostfiber_include_boost();

	return 0;
}
