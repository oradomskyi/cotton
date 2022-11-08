#include "../../include/masters/ParallelPosix.h"

#include <iostream>
using std::cout;
using std::endl;

// https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
// https://www.thegeekstuff.com/2012/05/c-mutex-examples/

//pthread_mutex_t ParallelPosix_lock = PTHREAD_MUTEX_INITIALIZER;

ParallelPosix::ParallelPosix(vector<Flood*>* new_floodsPtr)
    : ThreadMaster(new_floodsPtr)
    , n_threads(1)
    , sz_floods(new_floodsPtr->size())
    , master_thread(0)
    , threads(vector<pthread_t>(n_threads))
    , thread_args(vector<parallelposix::thread_args>(n_threads))
{
    this->n_threads = 2; // todo obtain from the system or from the settings
    this->setState(threadmaster::State::READY);
}

ParallelPosix::ParallelPosix(vector<Flood*>* new_floodsPtr, const int& new_n_threads)
    : ThreadMaster(new_floodsPtr)
    , n_threads(new_n_threads)
    , sz_floods(new_floodsPtr->size())
    , master_thread(0)
    , threads(vector<pthread_t>(new_n_threads))
    , thread_args(vector<parallelposix::thread_args>(new_n_threads))
{
    this->setState(threadmaster::State::READY);
}

ParallelPosix::~ParallelPosix()
{}

void* parallelposix::start_n_floods(void* argsPtr)
{ 
	pthread_mutex_t _lock = PTHREAD_MUTEX_INITIALIZER;
    parallelposix::thread_args args(((parallelposix::thread_args*)argsPtr)->from, ((parallelposix::thread_args*)argsPtr)->to, ((parallelposix::thread_args*)argsPtr)->pFloods);
    
    cout << "start_n_floods "<<args.from << ":" << args.to <<":"<<args.pFloods<<endl;
    // TODO: keep alive control
    // take control of how many alive targets we have, 
    // allow working if zero and allow stop if non-zero       
    while(true)
    {	
    	// pthread is pretty strange, it have to have cancellation points and rethrow exception,
    	// see this:
    	// 
    	// https://stackoverflow.com/questions/34972909/fatal-exception-not-rethrown-in-c
    	//
    	// pthread cancel points 
    	//
    	// https://man7.org/linux/man-pages/man7/pthreads.7.html
    	nanosleep((const struct timespec[]){{0, NANOSLEEP_TIMEOUT_NS}}, NULL); // sleep for a half of a microsecond
    	
    	try{
    		for(int i = args.from; i < args.to; i++)    
    		{   
    			pthread_mutex_lock(&_lock);
    			args.pFloods->at(i)->run(); // we have to make sure to have exclusive rights for this
    			pthread_mutex_unlock(&_lock);
    		}
    	}
    	// https://forums.opensuse.org/showthread.php/450418-pthread_exit-c-and-FATAL-exception-not-rethrown
    	catch (abi::__forced_unwind&)
        {
            for(int i = args.from; i < args.to; i++)    
    		{  
        		args.pFloods->at(i)->getNetworkPtr()->Shutdown();
         		//printf("%d, start_n_floods forced unwind, calling Shutdown() \n", i);
         	}
        	throw;
        } 
        catch (...)
        {}
    }
    return 0;
}

void* parallelposix::master_n_floods(void* args)
{
	cout << "parallelposix::master_n_floods() " << endl;

    // TODO: implement case when there less floods than threads.
    ParallelPosix* _this = (ParallelPosix*)args;
    
    int sz_floods = _this->getFloodsPtr()->size();
    int n_threads = _this->getNThreads();
    int n_floods_per_thread = int( sz_floods / n_threads) + 1;
    
    for(int i_flood=0, i_thread=0; i_thread<n_threads; i_flood += n_floods_per_thread, i_thread++)
    {  
    	nanosleep((const struct timespec[]){{0, NANOSLEEP_TIMEOUT_NS}}, NULL); // sleep for a half of a microsecond
    	
        _this->getThreadArgs()->at(i_thread).from 	= i_flood;
        _this->getThreadArgs()->at(i_thread).to   	= min(i_flood+n_floods_per_thread, sz_floods);
        _this->getThreadArgs()->at(i_thread).pFloods	= _this->getFloodsPtr();

    	cout << i_thread << "master_n_floods "
    		<< _this->getThreadArgs()->at(i_thread).from << "+"
    		<< _this->getThreadArgs()->at(i_thread).to << "+" 
    		<< _this->getThreadArgs()->at(i_thread).pFloods << endl;
    		
        pthread_t thread;
        pthread_create(&thread, NULL, &parallelposix::start_n_floods, (void*) &_this->getThreadArgs()->at(i_thread));
        _this->getThreads()->at(i_thread) = thread;
        cout << "thread: "<< _this->getThreads()->at(i_thread) << endl;
    }
    return 0;
}


void ParallelPosix::start()
{
    if(threadmaster::State::RUNNING == this->getState())
    {
        cout << "ParallelPosix already running" <<endl;
        return;
    }
  	
  	pthread_t master;
    pthread_create(&master, NULL, &parallelposix::master_n_floods, (void*) this);

    for(pthread_t thread: this->threads)
    {
        pthread_detach(thread);
        cout << "- worker detached -"<< thread <<endl;
    }
    
    this->master_thread = master;
    pthread_detach(this->master_thread);//, NULL);
    cout << "- master detached -" << this->master_thread <<endl;
    
    this->setState(threadmaster::State::RUNNING);
}

void ParallelPosix::stop()
{
    if(threadmaster::State::HALT == this->getState())
    {
        cout << "ParallelPosix is on hold" <<endl;
        return;
    }
    //pthread_mutex_lock(&ParallelPosix_lock);
    for(pthread_t thread: this->threads)
    {	
        
    	pthread_cancel(thread);
        
    	//cout << err << " ParallelPosix::stop() pthread_cancel() worker " << thread <<endl;
    }

    pthread_cancel(this->master_thread);
    //pthread_mutex_unlock(&ParallelPosix_lock);
    //cout << err << " ParallelPosix::stop() pthread_cancel() master " << this->master_thread <<endl;
   
    cout << "end of ParallelPosix::stop()" << endl;
    this->setState(threadmaster::State::HALT);
}

