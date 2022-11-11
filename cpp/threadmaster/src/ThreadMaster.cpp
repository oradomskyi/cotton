#include "../include/ThreadMaster.h"

ThreadMaster::ThreadMaster(vector<Flood*>* _floodsPtr)
    : state(threadmaster::State::PENDING)
    , floodsPtr(_floodsPtr)
    , n_threads(1)
{
    this->setState(threadmaster::State::READY);
}

ThreadMaster::ThreadMaster(vector<Flood*>* _floodsPtr, int _n_threads)
    : state(threadmaster::State::PENDING)
    , floodsPtr(_floodsPtr)
    , n_threads(_n_threads)
{
    this->setState(threadmaster::State::READY);
}

ThreadMaster::~ThreadMaster()
{}

