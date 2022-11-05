#include "../../include/masters/ParallelPosix.h"

#include <iostream>
using std::cout;
using std::endl;

// https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
// https://www.thegeekstuff.com/2012/05/c-mutex-examples/

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

ParallelPosix::ParallelPosix(vector<Flood*>* new_floodsPtr, int new_n_threads)
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
	pthread_mutex_t _lock;
    parallelposix::thread_args args(((parallelposix::thread_args*)argsPtr)->from, ((parallelposix::thread_args*)argsPtr)->to, ((parallelposix::thread_args*)argsPtr)->pFloods);
    
    cout << "start_n_floods "<<args.from << ":" << args.to <<":"<<args.pFloods<<endl;
    // TODO: keep alive control
    // take control of how many alive targets we have, 
    // allow working if zero and allow stop if non-zero       
    while(true)
    {
    	for(int i = args.from; i < args.to; i++)    
    	{   
    		pthread_mutex_lock(&_lock);
    		args.pFloods->at(i)->run(); // we have to make sure to have exclusive rights for this
    		pthread_mutex_unlock(&_lock);
    	}
    }
    pthread_exit(NULL);
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
    pthread_exit(NULL);
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
    this->master_thread = master;
    pthread_join(this->master_thread, NULL);
    
    cout << "- master joined -" << this->master_thread <<endl;
    
    for(pthread_t thread: this->threads)
    {
        pthread_detach(thread);
        cout << "- worker detached -"<< thread <<endl;
    }
    
    this->setState(threadmaster::State::RUNNING);
}

void ParallelPosix::stop()
{
    if(threadmaster::State::HALT == this->getState())
    {
        cout << "ParallelPosix is on hold" <<endl;
        return;
    }

    for(pthread_t thread: this->threads)
    {	
    	pthread_cancel(thread);
    	//cout << err << " ParallelPosix::stop() pthread_cancel() worker " << thread <<endl;
    }

    pthread_cancel(this->master_thread);
    //cout << err << " ParallelPosix::stop() pthread_cancel() master " << this->master_thread <<endl;
   
    cout << "end of ParallelPosix::stop()" << endl;
    this->setState(threadmaster::State::HALT);
}

