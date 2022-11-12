#include "../include/tests_parallelboostfiber.h"

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
    

    unsigned int sleep_delay_10s = 5;

	vector<Flood*> floodsPtrs;
    vector<Flood*>* pFloodsPtrs = &floodsPtrs;
	
    int n = 0;
    for(int i = 0; i < 5; i++)
	{
		cout << "making " << ip1 << endl;
		Flood* flood = new GET(ip1, port1 + n++);
		if(flood::State::READY == flood->getState())
		    floodsPtrs.push_back(std::move(flood));
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
    sleep(sleep_delay_10s);
    s.start();
    sleep(sleep_delay_10s);
    s.start();
    sleep(sleep_delay_10s);
    
}
