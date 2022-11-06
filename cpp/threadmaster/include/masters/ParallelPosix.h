#ifndef THREADMASTER_PARALLELPOSIX_H
#define THREADMASTER_PARALLELPOSIX_H

#define NANOSLEEP_TIMEOUT_NS 500

#include <time.h>

#include <pthread.h>
#include "../ThreadMaster.h"

using std::min;

namespace parallelposix
{
    struct thread_args
    { 
        int from;
        int to;
        vector<Flood*>* pFloods;
        
        thread_args()
            : from(0)
            , to(0)
            , pFloods(nullptr)
        {};

        thread_args(int _from, int _to, vector<Flood*>* _pFloods)
            : from(_from)
            , to(_to)
            , pFloods(_pFloods)
        {};
    };

    void* start_n_floods(void* args);
    void* master_n_floods(void* args);
}

class ParallelPosix : public ThreadMaster
{
private:
    static const threadmaster::Type type = threadmaster::Type::PARALLEL_TYPE1;
    int n_threads;
    int sz_floods;
    pthread_t master_thread;
    vector<pthread_t> threads;
    vector<parallelposix::thread_args> thread_args;
    
public:
    ParallelPosix(vector<Flood*>* new_floodsPtr);
    ParallelPosix(vector<Flood*>* new_floodsPtr, int n_threads);
    ~ParallelPosix();

    void start();
    void stop();
    threadmaster::Type getType() { return this->type; };
    
    vector<pthread_t>* getThreads() {return &this->threads; };
    vector<parallelposix::thread_args>* getThreadArgs() {return &this->thread_args; };
    int getNThreads() { return this->n_threads; };
    vector<Flood*>* getFloodsPtr() { return this->floodsPtr; };
};

#endif
