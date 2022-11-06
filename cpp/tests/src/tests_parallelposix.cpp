#include "../include/tests_threadmaster.h"

static const string ip1 = "192.168.56.1";

void test_parallelposix_startstop()
{
    cout << "test_parallelposix_startstop" << endl;
    

    unsigned int sleep_delay_10s = 10;
	//unsigned int sleep_delay_2s = 2000000;
    //unsigned int sleep_delay_001s = 1;

    vector<Flood*> v = { 
           new GET(ip1, 65123)
          ,new GET(ip1, 65124)
          ,new GET(ip1, 65125)
          ,new GET(ip1, 65126)
          ,new GET(ip1, 65127)
    };
       
    ParallelPosix s(&v, 2);
    
    cout << "ParallelPosix.getState() = " << s.getState() << endl;
    cout << "ParallelPosix.getType() = " << s.getType() << endl;
    
    cout << "ParallelPosix.start() = " << endl;    
    s.start(); sleep(sleep_delay_10s);
    cout << "ParallelPosix.stop() = " << endl;
    s.stop(); sleep(sleep_delay_10s);
        
    cout << "ParallelPosix.start() = " << endl;
    s.start(); sleep(sleep_delay_10s);
    cout << "ParallelPosix.stop() = " << endl;
    s.stop(); sleep(sleep_delay_10s);

    cout << "---- Stopping floods " << endl; 
    for(auto flood : v)
        flood->disable();
 
    cout << "ParallelPosix.start() = " << endl;    
    s.start(); sleep(sleep_delay_10s);
    cout << "ParallelPosix.stop() = " << endl;
    s.stop(); sleep(sleep_delay_10s);

    cout << "++++ Strating floods " << endl; 
    for(auto flood : v)
        flood->enable();

    cout << "ParallelPosix.start() = " << endl;    
    s.start(); sleep(sleep_delay_10s);
    cout << "ParallelPosix.stop() = " << endl;
    s.stop(); sleep(sleep_delay_10s);
    
    cout << "ParallelPosix.start() = " << endl;    
    s.start(); sleep(sleep_delay_10s);
    cout << "ParallelPosix.stop() = " << endl;
    s.stop(); sleep(sleep_delay_10s);
    
    cout << "ok"<<endl;
}
