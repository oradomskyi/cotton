#include "../../include/masters/ParallelPosix.h"

#include <iostream>
using std::cout;
using std::endl;

// https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
// https://www.thegeekstuff.com/2012/05/c-mutex-examples/

pthread_mutex_t parallelposix_lock;

ParallelPosix::ParallelPosix(vector<Flood*>* new_floodsPtr)
    : ThreadMaster(new_floodsPtr)
    , n_threads(1)
    , sz_floods(new_floodsPtr->size())
    , threads(vector<pthread_t>(n_threads))
{
    this->n_threads = 2; // todo obtain from the system or from the settings
    //this->threads.resize(this->n_threads);
    this->setState(threadmaster::State::READY);
}

ParallelPosix::ParallelPosix(vector<Flood*>* new_floodsPtr, int new_n_threads)
    : ThreadMaster(new_floodsPtr)
    , n_threads(new_n_threads)
    , sz_floods(new_floodsPtr->size())
    , threads(vector<pthread_t>(new_n_threads))
{
    //this->threads.resize(this->n_threads);
    this->setState(threadmaster::State::READY);
}

ParallelPosix::~ParallelPosix()
{}

void* parallelposix::start_n_floods(void* argsPtr)
{ 
    parallelposix::thread_args args(((thread_args*)argsPtr)->from, ((thread_args*)argsPtr)->to, ((thread_args*)argsPtr)->pFloods);
    cout << ((thread_args*)argsPtr)->from << ":" << ((thread_args*)argsPtr)->to <<":"<<((thread_args*)argsPtr)->pFloods<<endl;
    // TODO: keep alive control
    // take control of how many alive targets we have, 
    // allow working if zero and allow stop if non-zero       
    while(true)
    for(int i = args.from; i < args.to; i++)    
    {   
        if(flood::State::READY == args.pFloods->at(i)->getState())
        {
            cout << i << " start()"<<endl;
            args.pFloods->at(i)->start();
        }
        else
        {
            cout << i << " flood is on hold"<<endl;
        }
    }
    
    return 0;
}

void* parallelposix::master_n_floods(void* args)
{
    // TODO: implement case when there less floods than threads.
    ParallelPosix* _this = (ParallelPosix*)args;
    
    int sz_floods = _this->getFloodsPtr()->size();
    int n_threads = _this->getNThreads();
    int n_floods_per_thread = int( sz_floods / n_threads) + 1;
    
    // I want to make these threads detached and keep only their handles
    //pthread_attr_t thread_attrs;
    //pthread_attr_setdetachstate(&thread_attrs, PTHREAD_CREATE_DETACHED);

    vector<parallelposix::thread_args> v_args(n_threads);

    for(int i_flood=0, i_thread=0; i_thread<n_threads; i_flood += n_floods_per_thread, i_thread++)
    {  
        v_args[i_thread].from = i_flood;
        v_args[i_thread].to   = min(i_flood+n_floods_per_thread, sz_floods);
        v_args[i_thread].pFloods = _this->getFloodsPtr();

        cout << i_flood << " " << i_thread << " " << v_args[i_thread].from << " " << v_args[i_thread].to << " " << v_args[i_thread].pFloods << endl;

        pthread_t thread;
        pthread_create(&thread, NULL, &parallelposix::start_n_floods, (void*) &v_args[i_thread]);
        cout << "thr: "<<thread<<endl;
        _this->getThreads()->at(i_thread) = thread;
        cout << "thisthr: "<<_this->getThreads()->at(i_thread)<<endl;
    }
    
    return 0;
}


void ParallelPosix::start()
{
    //pthread_mutex_lock(&parallelposix_lock);
    
    if(threadmaster::State::RUNNING == this->getState())
    {
        cout << "ParallelPosix already running" <<endl;
        return;
    }
    // TODO: implement case when there less floods than threads.
    /*
    
    int n_floods_per_thread = int( sz_floods / n_threads) + 1;
    
    // I want to make these threads detached and keep only their handles
    //pthread_attr_t thread_attrs;
    //pthread_attr_setdetachstate(&thread_attrs, PTHREAD_CREATE_DETACHED);

    vector<parallelposix::thread_args> v_args(n_threads);

    for(int i_flood=0, i_thread=0; i_thread<this->n_threads; i_flood += n_floods_per_thread, i_thread++)
    {  
        v_args[i_thread].from = i_flood;
        v_args[i_thread].to   = min(i_flood+n_floods_per_thread, this->sz_floods);
        v_args[i_thread].pFloods = this->floodsPtr;

        cout << i_flood << " " << i_thread << " " << v_args[i_thread].from << " " << v_args[i_thread].to << " " << v_args[i_thread].pFloods << endl;

        pthread_t thread;
        pthread_create(&thread, NULL, &parallelposix::start_n_floods, (void*) &v_args[i_thread]);
        this->threads[i_thread] = thread;         
    }
    
    // when not attached, works only on last part of Floods, memory seems not been shared
    // figure out how to make them detached and control from outside from master thread
    for(pthread_t thread: this->threads)
        pthread_join(thread, NULL);
    */
    

    //pthread_t thread;
    //pthread_attr_t thread_attrs;
    //pthread_attr_setdetachstate(&thread_attrs, PTHREAD_CREATE_DETACHED);
    //pthread_create(&thread, &thread_attrs, &parallelposix::master_n_floods, (void*) this);
    //pthread_create(&thread, NULL, &parallelposix::master_n_floods, (void*) this);
    //cout << "=== Created! ===" <<endl;
    //pthread_join(thread, NULL);
    
    parallelposix::master_n_floods((void*) this);
    
    for(int i = 0; i < n_threads; i++)
    {
pthread_detach(this->getThreads()->at(i));
        //pthread_join(this->getThreads()->at(i), NULL);
        cout << "dthre: " << this->getThreads()->at(i)<< endl;
         
        //
    }


    //cout << "sz thr"<<this->threads.size() << endl;
    //for(pthread_t thread: this->threads)
    {
      //  cout << "dthre: " << thread<< endl;
        //pthread_join(thread, NULL);
        //pthread_detach(thread);
    }
    

    cout << "----------------------------- JOINED!-------------------------------" <<endl;
    this->setState(threadmaster::State::RUNNING);
    
   // pthread_mutex_unlock(&parallelposix_lock);
}

void ParallelPosix::stop()
{
    //pthread_mutex_lock(&parallelposix_lock);
    if(threadmaster::State::HALT == this->getState())
    {
        cout << "ParallelPosix is on hold" <<endl;
        return;
    }

    for(Flood* flood : *(this->floodsPtr))
    {
        flood->stop();
    }
    
    this->setState(threadmaster::State::HALT);
    //pthread_mutex_unlock(&parallelposix_lock);
}

