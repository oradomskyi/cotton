#include "../include/tests_parallelboostfiber.h"

static const string ip1 = "osboxes";//"192.168.56.1";
static const int port1 = 65123;

void test_parallelboostfiber_include_boost()
{
	//using namespace boost::lambda;
    //typedef std::istream_iterator<int> in;

    //std::for_each(
    //    in(std::cin), in(), std::cout << (_1 * 3) << " " );
}

void test_parallelboostfiber_run()
{

   cout << "test_parallelboostfiber_run" << endl;
    

    unsigned int sleep_delay_5s = 5;

	vector<Flood*> floodsPtrs;
    vector<Flood*>* pFloodsPtrs = &floodsPtrs;
	
    int n = 0;
    //for(int i = 0; i < 5; i++)
	{
		cout << "making " << ip1 << endl;
		Flood* flood0 = new GET(ip1, port1 + n++); 		    floodsPtrs.push_back(std::move(flood0));
        Flood* flood1 = new GET(ip1, port1 + n++);		    floodsPtrs.push_back(std::move(flood1));
		Flood* flood2 = new BYPASS(ip1, port1 + n++);		    floodsPtrs.push_back(std::move(flood2));
		Flood* flood3 = new BYPASS(ip1, port1 + n++);		    floodsPtrs.push_back(std::move(flood3));
		Flood* flood4 = new GET(ip1, port1 + n++);		    floodsPtrs.push_back(std::move(flood4));
				
        //if(flood::State::READY == flood->getState())
		//    floodsPtrs.push_back(std::move(flood));
	}

	cout <<"size floods" << floodsPtrs.size() << endl;
	for(auto f : floodsPtrs)
		cout << f->getTarget()->getAddress() << endl;

    int n_threads = 2;
    ParallelBoostFiber s(pFloodsPtrs, n_threads);
    
    cout << "ParallelPosix.getState() = " << s.getState() << endl;
    cout << "ParallelPosix.getType() = " << s.getType() << endl;
    
    cout << "ParallelPosix.start() = " << endl;    
    s.start();

/*    cout << "test_long_run" << endl;

    for(int i = 0; i < 1000000; i++)
    {
    
    ParallelBoostFiber s(pFloodsPtrs, n_threads);
    s.start();
    s.stop();
    
    }
*/
sleep(sleep_delay_5s);
    sleep(sleep_delay_5s);
    sleep(sleep_delay_5s);
    sleep(sleep_delay_5s);
    s.start();
    sleep(sleep_delay_5s);
    s.start();
    sleep(sleep_delay_5s);
    
}
