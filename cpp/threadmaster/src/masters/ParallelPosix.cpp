#include "../../include/masters/ParallelPosix.h"

#include <iostream>
using std::cout;
using std::endl;

// https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html


pthread_mutex_t parallelposix_lock;

ParallelPosix::ParallelPosix(vector<Flood*>* new_floodsPtr)
    : ThreadMaster(new_floodsPtr)
    , n_threads(1)
    , sz_floods(new_floodsPtr->size())
    , threads(vector<pthread_t>(n_threads))
{
    this->n_threads = 2; // todo obtain from the system or from the settings
    
    this->threads.resize(this->n_threads);

    this->setState(threadmaster::State::READY);
}

ParallelPosix::~ParallelPosix()
{}

void* parallelposix::start_n_floods(void* args)
{ 
    cout << ((thread_args*)args)->from << ":" << ((thread_args*)args)->to <<":"<<((thread_args*)args)->pFloods<<endl;
    // TODO: keep alive control
    // take control of how many alive targets we have, 
    // allow working if zero and allow stop if non-zero       
    while(true)
    for(int i = ((thread_args*)args)->from; i < ((thread_args*)args)->to; i++)    
    {   
        if(flood::State::READY == ((thread_args*)args)->pFloods->at(i)->getState())
        {
            cout << i << " start()"<<endl;
            ((thread_args*)args)->pFloods->at(i)->start();
        }
        else
        {
            cout << i << " flood is on hold"<<endl;
        }
    }
    
    return 0;
}

void ParallelPosix::start()
{
    if(threadmaster::State::RUNNING == this->getState())
        return;

    int n_floods_per_thread = int(this->floodsPtr->size() / this->n_threads)+1;
    
    vector<parallelposix::thread_args> v_args(this->n_threads);

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

    for(pthread_t thread: this->threads)
        pthread_join(thread, NULL);

    this->setState(threadmaster::State::RUNNING);
}

void ParallelPosix::stop()
{
    if(threadmaster::State::HALT == this->getState())
        return;

    for(Flood* flood : *(this->floodsPtr))
            flood->stop();
    
    this->setState(threadmaster::State::HALT);
}

