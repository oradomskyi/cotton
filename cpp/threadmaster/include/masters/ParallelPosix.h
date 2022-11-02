#ifndef THREADMASTER_PARALLELPOSIX_H
#define THREADMASTER_PARALLELPOSIX_H

#include <pthread.h>
#include "../ThreadMaster.h"

using std::min;

namespace parallelposix
{
    struct thread_args
    { 
        int from;
        int to;
        const vector<Flood*>* pFloods;
        
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
    vector<pthread_t> threads;
    
public:
    ParallelPosix(vector<Flood*>* new_floodsPtr);
    ParallelPosix(vector<Flood*>* new_floodsPtr, int n_threads);
    ~ParallelPosix();

    void start();
    void stop();
    threadmaster::Type getType() { return this->type; };
    
    //vector<pthread_t>* getThreads() {return &this->threads; };
    //int getNThreads() { return this->n_threads; };
    //vector<Flood*>* getFloodsPtr() { return this->floodsPtr; };
};

#endif
