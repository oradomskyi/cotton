#include "../../include/masters/ParallelBoostFiber.h"

#include <iostream>
using std::cout;
using std::endl;

void parallelboostfiber::master_fiber_routine(vector<Flood*>* floodsPtr)
{
    //use_scheduling_algorithm< boost::fibers::algo::work_stealing >(thread::hardware_concurrency());
    
    for(Flood* flood : *floodsPtr)
    {
        //(*flood)();
        fiber f(ref(*flood));
        f.detach();
    }
}

ParallelBoostFiber::ParallelBoostFiber(vector<Flood*>* _floodsPtr)
    : ThreadMaster(_floodsPtr)
{}

ParallelBoostFiber::ParallelBoostFiber(vector<Flood*>* _floodsPtr, int _n_threads)
    : ThreadMaster(_floodsPtr, _n_threads)
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

    fiber master_fiber(parallelboostfiber::master_fiber_routine, this->getFloodsPtr());
    master_fiber.join();

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

