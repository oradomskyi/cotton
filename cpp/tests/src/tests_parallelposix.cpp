#include "../include/tests_threadmaster.h"

static const string ip1 = "192.168.56.1";

void test_parallelposix_startstop()
{
    cout << "test_parallelposix_startstop" << endl;
    

    unsigned int sleep_delay_us = 10000000;

   

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
    s.start(); usleep(sleep_delay_us);
    cout << "ParallelPosix.stop() = " << endl;
    s.stop(); usleep(sleep_delay_us);

    for(auto flood : v)
        flood->stop();

    cout << "ParallelPosix.start() = " << endl;    
    s.start(); usleep(sleep_delay_us);
    cout << "ParallelPosix.stop() = " << endl;
    s.stop(); usleep(sleep_delay_us);

    for(auto flood : v)
        flood->start();

    cout << "ParallelPosix.start() = " << endl;    
    s.start(); usleep(sleep_delay_us);
    cout << "ParallelPosix.stop() = " << endl;
    s.stop(); usleep(sleep_delay_us);

    cout << "ok"<<endl;
}
