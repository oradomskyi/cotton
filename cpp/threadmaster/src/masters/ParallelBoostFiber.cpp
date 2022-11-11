#include "../../include/masters/ParallelBoostFiber.h"

#include <iostream>
using std::cout;
using std::endl;

ParallelBoostFiber::ParallelBoostFiber(vector<Flood*>* _floodsPtr)
    : ThreadMaster(_floodsPtr)
    , n_fibers(_floodsPtr->size())
{
}

ParallelBoostFiber::ParallelBoostFiber(vector<Flood*>* _floodsPtr, int _n_threads)
    : ThreadMaster(_floodsPtr, _n_threads)
    , n_fibers(_floodsPtr->size())
{
    // by default we will launch each target in its own fiber, so Threads here
    // are the regular threads in their original meaning
}

ParallelBoostFiber::~ParallelBoostFiber()
{}

void ParallelBoostFiber::start()
{
    //if(threadmaster::State::RUNNING == this->getState())
    {
    //    cout << "ParallelBoostFiber already running" <<endl;
    //    return;
    }
    for(Flood* flood : *(this->getFloodsPtr()))
    {
        //(*flood)();
        fiber f(ref(*flood));
        f.detach();
    }

    this->setState(threadmaster::State::RUNNING);
}

void ParallelBoostFiber::stop()
{
    if(threadmaster::State::HALT == this->getState())
    {
        cout << "ParallelBoostFiber is on hold" <<endl;
        return;
    }

    this->setState(threadmaster::State::HALT);
}

