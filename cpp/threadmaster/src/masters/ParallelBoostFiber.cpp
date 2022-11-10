#include "../../include/masters/ParallelBoostFiber.h"

#include <iostream>
using std::cout;
using std::endl;

ParallelBoostFiber::ParallelBoostFiber(vector<Flood*>* new_floodsPtr)
    : ThreadMaster(new_floodsPtr)
    , n_threads(1)
{
    //this->n_threads = 2; // todo obtain from the system or from the settings
    this->setState(threadmaster::State::READY);
}

ParallelBoostFiber::ParallelBoostFiber(vector<Flood*>* new_floodsPtr, const int& new_n_threads)
    : ThreadMaster(new_floodsPtr)
    , n_threads(new_n_threads)
{
    this->setState(threadmaster::State::READY);
}

ParallelBoostFiber::~ParallelBoostFiber()
{}

void ParallelBoostFiber::start()
{
    if(threadmaster::State::RUNNING == this->getState())
    {
        cout << "ParallelPosix already running" <<endl;
        return;
    }
  	
    this->setState(threadmaster::State::RUNNING);
}

void ParallelBoostFiber::stop()
{
    if(threadmaster::State::HALT == this->getState())
    {
        cout << "ParallelPosix is on hold" <<endl;
        return;
    }

    this->setState(threadmaster::State::HALT);
}

