#include "../include/ThreadMaster.h"

ThreadMaster::ThreadMaster(vector<Flood*>* new_floodsPtr)
    : state(threadmaster::State::PENDING)
    , floodsPtr(new_floodsPtr)
{}

ThreadMaster::~ThreadMaster()
{}

